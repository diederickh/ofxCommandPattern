#ifndef OFXCOMMANDPATTERNTHREADSYNCH
#define OFXCOMMANDPATTERNTHREADSYNCH

class ofxCommandProcessorThreadSync {
public:
	virtual bool lock() = 0;
	virtual void unlock() const = 0;
	virtual void wait(int nMillis) = 0;
	virtual void notify() = 0;
	virtual bool isLocked() const = 0;
};
#endif

