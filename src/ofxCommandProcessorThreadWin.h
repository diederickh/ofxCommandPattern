#ifndef OFXCOMMANDPATTERNTHREADWINH
#define OFXCOMMANDPATTERNTHREADWINH

#include "ofxCommand.h"
#include "ofxCommandProcessor.h"
#include "ofxCommandProcessorThread.h"
#include "ofxCommandProcessorThreadSync.h"

#if defined( __WIN32__ ) || defined( _WIN32 )
	#include <windows.h>
	#include <process.h>


	class ofxCommandProcessorThreadWin : public ofxCommandProcessor, public ofxCommandProcessorThread {
	protected:
		HANDLE thread_handle_;
		bool thread_active_;
		bool running_;
		ofxCommandProcessorThreadSyncWin sync_;

	public:
		ofxCommandProcessorThreadWin();
		virtual bool start() {
			thread_handle_ = (HANDLE)_beginthread(threadProc,0,this);
			return (thread_handle_ != NULL);
		}

		virtual void sleep(int nMillis);
		virtual void join();
		virtual void enqueue(ofxCommand* pCommand);
		virtual void remove(std::string sName);
		virtual void clear();
		virtual bool isReady();
		virtual void update();
		virtual void run();

	protected:
		static void threadProc(void* lParam) {
			ofxCommandProcessorThreadWin* thread = (ofxCommandProcessorThreadWin*)lParam;
			if(thread != NULL) {
				thread->thread_active_ = true;
				thread->run();
				thread->thread_active_ = false;
			}
			_endthread();
		}

		virtual ofxCommand* take();
	};
	#endif
#endif
