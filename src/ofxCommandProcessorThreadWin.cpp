#include "ofxCommandProcessorThreadWin.h"
ofxCommandProcessorThreadWin::ofxCommandProcessorThreadWin()
:running_(false)
,ofxCommandProcessorThread()
{

}

void ofxCommandProcessorThreadWin::enqueue(ofxCommand* pCommand) {
	sync_.lock();
	ofxCommandProcessor::enqueue(pCommand);
	sync_.notify();
	sync_.unlock();
}

void ofxCommandProcessorThreadWin::remove(std::string sName) {
	sync_.lock();
	ofxCommandProcessor::remove(sName);
	sync_.unlock();
}

void ofxCommandProcessorThreadWin::clear() {
	sync_.lock();
	ofxCommandProcessor::clear();
	sync_.unlock();
}

bool ofxCommandProcessorThreadWin::isReady() {
	sync_.lock();
	bool ready = ofxCommandProcessor::isReady();
	sync_.unlock();
	return ready;
}

void ofxCommandProcessorThreadWin::update() {

}

ofxCommand* ofxCommandProcessorThreadWin::take() {
	ofxCommand* command = NULL;
	sync_.lock();
	while(queue.empty() && running_) {
		sync_.wait(10);
	}
	if(running_) {
		command = queue.front();
		queue.pop_front();
	}
	sync_.unlock();
	return command;
}

void ofxCommandProcessorThreadWin::run() {
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	running_ = true;
	while(running_) {
		sleep(1);
		ofxCommand* command = take();
		if(command != NULL) {
			bool complete = command->execute();
			//std::cout << "Running: " << command->name << std::endl;
			if(complete == false) {
				sleep(500);
				sync_.lock();
				queue.push_front(command); // we want to repeat it directly! (not at the end)
				sync_.unlock();
				//enqueue(command);
			}
			else {
				delete command;
			}
		}
	}
}
