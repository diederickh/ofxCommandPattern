#ifndef OFXCOMMANDPROCESSORTHREADMACH
#define OFXCOMMANDPROCESSORTHREADMACH

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "ofxCommand.h"
#include "ofxCommandProcessor.h"
#include "ofxCommandProcessorThread.h"

#include "ofMain.h"

class ofxCommandProcessorThreadMac : public ofxCommandProcessor, public ofxCommandProcessorThread {
public:
	virtual bool start();
	virtual void join();
	virtual void sleep(int nMillis);
	virtual void run();
	
	virtual void enqueue(ofxCommand* pCommand);
	virtual void remove(std::string sName);
	virtual void clear();
	virtual bool isReady();
	virtual void update();
	
protected:	
	virtual ofxCommand* take();

private:
	boost::mutex mutex_;
	boost::shared_ptr<boost::thread> thread_ptr;
	
};
#endif