#ifndef OFXCOMMANDPROCESSORTHREADH
#define OFXCOMMANDPROCESSORTHREADH

#include <windows.h>
#include <process.h>


class ofxCommandProcessorThread {
protected:
	HANDLE thread_handle_;
	bool thread_active_;

public:
	ofxCommandProcessorThread()
		:thread_handle_()
		,thread_active_(false)
	{
	}

	bool start() {
		thread_handle_ = (HANDLE)_beginthread(threadProc,0,this);
		return (thread_handle_ != NULL);
	}

	void join() {
		if(thread_handle_) {
			::WaitForSingleObject(thread_handle_, INFINITE);
		}
	}

	void sleep(int nMillis) {
		if(thread_handle_) {
			Sleep(nMillis);
		}
	}

	virtual void run() = 0;

protected:
	static void threadProc(void* lParam) {
		ofxCommandProcessorThread* thread = (ofxCommandProcessorThread*)lParam;
		if(thread != NULL) {
			thread->thread_active_ = true;
			thread->run();
			thread->thread_active_ = false;
		}
		_endthread();
	}
};
#endif
