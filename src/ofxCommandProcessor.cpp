#include "ofxCommandProcessor.h"
#include "ofxCommand.h"
#include "ofMain.h"

void ofxCommandProcessor::enqueue(ofxCommand* pCommand) {
	lock();
	queue.push_back(pCommand);
	unlock();
}

void ofxCommandProcessor::clear() {
	lock();
	std::deque<ofxCommand*>::iterator it = queue.begin();
	while (it != queue.end()) {
			delete (*it);
			++it;
	}
	queue.clear();
	unlock();
}

bool ofxCommandProcessor::isReady() {
	lock();
	bool ready = queue.empty();
	unlock();
	return ready;
}


ofxCommand* ofxCommandProcessor::take() {
	ofxCommand* command = NULL;
	lock();
		while (queue.empty() && threadRunning) {
			ofSleepMillis(10);
		}

		if (threadRunning){
			command = queue.front();
			queue.pop_front();
		}
	unlock();
	return command;
}


void ofxCommandProcessor::threadedFunction() {
	while(1) {
		ofSleepMillis(1);
		ofxCommand* command = take();
		if(command != NULL) {
			bool complete = command->execute();
			if(!complete) {
				ofSleepMillis(500);
				enqueue(command);
			}
			else {	
				delete command;
			}
		}
	}
}




