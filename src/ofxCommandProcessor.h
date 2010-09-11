#ifndef OFXCOMMANDPROCESSOR
#define OFXCOMMANDPROCESSOR

//#include "ofxThread.h"
#include <deque>
#include <iostream>
#undef check
#include <boost/thread.hpp>

class ofxCommand;
//class ofxCommandProcessor : public ofxThread {
class ofxCommandProcessor  {
public:
	ofxCommandProcessor();
	~ofxCommandProcessor();
	void enqueue(ofxCommand* pCommand);
	void remove(std::string sName);
	void clear();
	bool isReady();
	void update();
/*
	void operator()() {
		std::cout << "ofxCommanProcessor() operator: ()" << std::endl;
		run();
	}
	*/
	//void start();
	//void run();
protected:
	//boost::shared_ptr<boost::thread> thread_;
	//boost::thread thread_;
	std::deque<ofxCommand*>  queue;
	//virtual void threadedFunction();
	ofxCommand* take();
	//boost::mutex mutex;
	//bool is_running;
};
#endif