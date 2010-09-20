#ifndef OFXCOMMANDPATTERNTHREADWINH
#define OFXCOMMANDPATTERNTHREADWINH

#include "ofxCommand.h"
#include "ofxCommandProcessor.h"
#include "ofxCommandProcessorThread.h"
#include "ofxCommandProcessorThreadSync.h"

#if defined( __WIN32__ ) || defined( _WIN32 )
	#include <windows.h>
	#include <process.h>
#endif

class ofxCommandProcessorThreadWin : public ofxCommandProcessor, public ofxCommandProcessorThread {
protected:
	bool running_;
	ofxCommandProcessorThreadSync sync_;

public:
	ofxCommandProcessorThreadWin();
	virtual void enqueue(ofxCommand* pCommand);
	virtual void remove(std::string sName);
	virtual void clear();
	virtual bool isReady();
	virtual void update();
	virtual void run();

protected:
	virtual ofxCommand* take();
};
#endif
