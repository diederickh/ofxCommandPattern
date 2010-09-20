#ifndef OFXCOMMANDPATTERNTHREADSYNCH
#define OFXCOMMANDPATTERNTHREADSYNCH

#include <windows.h>
#include <process.h>

class ofxCommandProcessorThreadSyncWin : public ofxCommandProcessorThreadSync{
protected:
	HANDLE mutex_handle;
	bool acquired;

public:
	ofxCommandProcessorThreadSync()
		:mutex_handle(NULL)
		,acquired(false)
	{
		mutex_handle = CreateMutex(NULL, false, NULL);
		if(mutex_handle == NULL) {
			CloseHandle(mutex_handle);
		}
	}

	virtual ~ofxCommandProcessorThreadSync() {
		unlock();
		CloseHandle(mutex_handle);
	}

	virtual bool lock() {
		if(mutex_handle != NULL) {
			DWORD result = WaitForSingleObject(mutex_handle, INFINITE);
			if(result == WAIT_OBJECT_0 || result == WAIT_ABANDONED) {
				acquired = true;
			}
		}
	}

	virtual void unlock() const {
		if(mutex_handle) {
			ReleaseMutex(mutex_handle);
		}
	}

	virtual void wait(int nMillis) {
		Sleep(nMillis);
		if(isLocked()) {
			unlock();
		}
		lock();
	}

	virtual void notify() {
		if(isLocked()) {
			unlock();
		}
	}

	virtual bool isLocked() const {
		return acquired;
	}

};
#endif

