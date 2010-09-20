#ifndef OFXCOMMANDPROCESSORTHREADSYNCMACH
#define OFXCOMMANDPROCESSORTHREADSYNCMACH

#include <boost/thread.hpp>

class ofxCommandProcessorThreadSyncWin : public ofxCommandProcessorThreadSync{
protected:
	boost::mutext mutex_;


public:
	
	virtual ~ofxCommandProcessorThreadSync() {
		mutex_.unlock();
	}

	virtual bool lock() {
		mutex_.lock();
	}

	virtual void unlock() const {
		mutex_.unlock();
	}

	virtual void wait(int nMillis) {
		ofSleepMillis(nMillis);
	}


	virtual void notify() {	}
	virtual bool isLocked() const {	return false; }

};
#endif




#endif