#include "ofxCommandProcessorThreadMac.h"

bool ofxCommandProcessorThreadMac::start() {
	thread_ptr = boost::shared_ptr<boost::thread>(new boost::thread(
		boost::bind(&ofxCommandProcessorThreadMac::run, this)
	));
	return true;
}

void ofxCommandProcessorThreadMac::join() {
	thread_ptr->join();
}

void ofxCommandProcessorThreadMac::sleep(int nMillis) {	
	boost::mutex::scoped_lock sl(mutex_);
	ofSleepMillis(nMillis);
	//boost::thread::sleep(nMillis);
}

void ofxCommandProcessorThreadMac::run() {
	while(true) {
		ofxCommandProcessor::update();
	}
}

//--
void ofxCommandProcessorThreadMac::enqueue(ofxCommand* pCommand) {
	boost::mutex::scoped_lock sl(mutex_);
	ofxCommandProcessor::enqueue(pCommand);
}

void ofxCommandProcessorThreadMac::remove(std::string sName) {
	boost::mutex::scoped_lock sl(mutex_);
	ofxCommandProcessor::remove(sName);
}

void ofxCommandProcessorThreadMac::clear() {
	boost::mutex::scoped_lock sl(mutex_);
	ofxCommandProcessor::clear();
}

bool ofxCommandProcessorThreadMac::isReady() {
	boost::mutex::scoped_lock sl(mutex_);
	bool ready = ofxCommandProcessor::isReady();
	return ready;
}

void ofxCommandProcessorThreadMac::update() {
}

ofxCommand* ofxCommandProcessorThreadMac::take() {
	boost::mutex::scoped_lock sl(mutex_);
	ofxCommand* cmd = ofxCommandProcessor::take();
	return cmd;
}