#include "ofxCommandProcessor.h"
#include "ofxCommand.h"
#include "ofMain.h"
#include "ofxLog.h"

ofxCommandProcessor::ofxCommandProcessor()
{
}

ofxCommandProcessor::~ofxCommandProcessor() {
	std::cout << ">>>> ~ofxCommandProcessor" << std::endl;
}

//void ofxCommandProcessor::enqueue(ofxCommand* pCommand) {
void ofxCommandProcessor::enqueue(boost::shared_ptr<ofxCommand> pCommand) {
    OFXLOG("ofxCommandProcessor::enqueue() command:" << pCommand->name);
	queue.push_back(pCommand);
}

void ofxCommandProcessor::clear() {
	//std::deque<ofxCommand*>::iterator it = queue.begin();
	//boost::ptr_deque<ofxCommand>::iterator it = queue.begin();

	/*
	while (it != queue.end()) {
		delete (*it);
		++it;
	}
	*/
	queue.clear();
}

void ofxCommandProcessor::remove(std::string sName) {
    OFXLOG("ofxCommandProcessor::remove() command:" << sName);
	//boost::ptr_deque<ofxCommand>::iterator it =  queue.begin();
	std::deque<boost::shared_ptr<ofxCommand> >::iterator it = queue.begin();
	while(it != queue.end()) {
		//std::cout << ">> In queue: " << (*it++)->name << std::endl;
		//if( (*it)->name == sName) { // for boost
		if( (*it)->name == sName) {
		    OFXLOG("ofxCommandProcessor::remove() - delete pointer:" << sName);
			//delete (*it); // for boost
			it = queue.erase(it);
		}
		else
			++it;

	}
}

bool ofxCommandProcessor::isReady() {
	bool ready = queue.empty();
	//boost::ptr_deque<ofxCommand>::iterator it =  queue.begin();


	#ifdef LOG_OFXCOMMANDPATTERN
	std::deque<boost::shared_ptr<ofxCommand> >::iterator it = queue.begin()
	while(it != queue.end()) {
		std::cout << ">> In queue: " << (*it++)->name << std::endl;
	}
	#endif
	return ready;
}


//ofxCommand* ofxCommandProcessor::take() {
boost::shared_ptr<ofxCommand> ofxCommandProcessor::take() {
	boost::shared_ptr<ofxCommand> command;
	if(queue.empty())
        return command;
	//if(queue.empty())
	//	return NULL; // what should I return here?
	command = queue.front();
	//boost::shared_ptr<ofxCommand> command = queue.front();
	queue.pop_front();
	return command;
}

void ofxCommandProcessor::update() {
	boost::shared_ptr<ofxCommand> command = take();
	//ofxCommand* command = take();
	if(command != NULL) {
		bool complete = command->execute();
		if(!complete) {
			queue.push_front(command); // we want to repeat it directly! (not at the end)
		}
		else {
			// @todo something wrong here! we need to use a boost::ptr_deque
            OFXLOG("ofxCommandProcessor::update() delete:" << command->name);
			//delete command;
		}
	}
}



