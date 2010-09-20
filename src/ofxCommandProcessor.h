#ifndef OFXCOMMANDPROCESSOR
#define OFXCOMMANDPROCESSOR

#include <deque>
#include <iostream>

class ofxCommand;
class ofxCommandProcessor  {
public:
	ofxCommandProcessor();
	~ofxCommandProcessor();
	void enqueue(ofxCommand* pCommand);
	void remove(std::string sName);
	void clear();
	bool isReady();
	void update();
	void shutdown();
protected:
	std::deque<ofxCommand*>  queue;
	ofxCommand* take();
};

#endif