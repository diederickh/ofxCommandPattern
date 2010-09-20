#ifndef OFXCOMMANDPROCESSORTHREADH
#define OFXCOMMANDPROCESSORTHREADH




class ofxCommandProcessorThread {
protected:
	//HANDLE thread_handle_;
//	bool thread_active_;

public:
	/*
	ofxCommandProcessorThread()
		:thread_handle_()
		,thread_active_(false)
	{
	}
*/
	virtual bool start() = 0;
	/*
		thread_handle_ = (HANDLE)_beginthread(threadProc,0,this);
		return (thread_handle_ != NULL);
	}
*/
	virtual void join() = 0;
//		if(thread_handle_) {
//			::WaitForSingleObject(thread_handle_, INFINITE);
//		}
//	}

	virtual void sleep(int nMillis) = 0;
	//{
//		if(thread_handle_) {
//			Sleep(nMillis);
//		}
//	}

	virtual void run() = 0;

protected:
//	static void threadProc(void* lParam) {
//		ofxCommandProcessorThread* thread = (ofxCommandProcessorThread*)lParam;
//		if(thread != NULL) {
//			thread->thread_active_ = true;
//			thread->run();
//			thread->thread_active_ = false;
//		}
//		_endthread();
//	}
};
#endif
