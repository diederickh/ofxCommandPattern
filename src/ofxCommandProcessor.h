#ifndef OFXCOMMANDPROCESSOR
#define OFXCOMMANDPROCESSOR

#include <deque>
#include <iostream>

class ofxCommand;
class ofxCommandProcessor  {
public:
	ofxCommandProcessor();
	~ofxCommandProcessor();
	virtual void enqueue(ofxCommand* pCommand);
	virtual void remove(std::string sName);
	virtual void clear();
	virtual bool isReady();
	virtual void update();
/*
	void operator()() {
		std::cout << "ofxCommanProcessor() operator: ()" << std::endl;
		run();
	}
	*/
	//void start();
	//void run();

protected:
	std::deque<ofxCommand*>  queue;
	ofxCommand* take();
};

#endif
