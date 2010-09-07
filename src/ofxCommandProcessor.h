#ifndef OFXCOMMANDPROCESSOR
#define OFXCOMMANDPROCESSOR

#include "ofxThread.h"
#include <deque>
class ofxCommand;
class ofxCommandProcessor : public ofxThread {
public:
	void enqueue(ofxCommand* pCommand);
	void clear();
	bool isReady();
protected:
	std::deque<ofxCommand*>  queue;
	virtual void threadedFunction();
	ofxCommand* take();
};
#endif