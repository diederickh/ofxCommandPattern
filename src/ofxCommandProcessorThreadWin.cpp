#include "ofxCommandProcessorThreadWin.h"
#include "ofxLog.h"
#if defined( __WIN32__ ) || defined( _WIN32 )
	ofxCommandProcessorThreadWin::ofxCommandProcessorThreadWin()
	:running_(false)
	,thread_handle_()
	,thread_active_(false)
	{

	}

	void ofxCommandProcessorThreadWin::join() {
		if(thread_handle_) {
			::WaitForSingleObject(thread_handle_, INFINITE);
		}
	}

	void ofxCommandProcessorThreadWin::sleep(int nMillis) {
		if(thread_handle_) {
			Sleep(nMillis);
		}
	}

	//void ofxCommandProcessorThreadWin::enqueue(ofxCommand* pCommand) {
	void ofxCommandProcessorThreadWin::enqueue(boost::shared_ptr<ofxCommand> pCommand) {
		sync_.lock();
		OFXLOG("ofxCommandProcessorThreadWin: enqueue.")
		ofxCommandProcessor::enqueue(pCommand);
		sync_.notify();
		sync_.unlock();
	}

	void ofxCommandProcessorThreadWin::remove(std::string sName) {
		sync_.lock();
		ofxCommandProcessor::remove(sName);
		sync_.unlock();
	}

	void ofxCommandProcessorThreadWin::clear() {
		sync_.lock();
		ofxCommandProcessor::clear();
		sync_.unlock();
	}

	bool ofxCommandProcessorThreadWin::isReady() {
		sync_.lock();
		bool ready = ofxCommandProcessor::isReady();
		sync_.unlock();
		return ready;
	}

	void ofxCommandProcessorThreadWin::update() {

	}

	//ofxCommand* ofxCommandProcessorThreadWin::take() {
	boost::shared_ptr<ofxCommand> ofxCommandProcessorThreadWin::take() {
	    boost::shared_ptr<ofxCommand>command;
		//ofxCommand* command = NULL;
		sync_.lock();
		while(queue.empty() && running_) {
			sync_.wait(10);
		}
		if(running_) {
			command = queue.front();
			queue.pop_front();
		}
		sync_.unlock();
		return command;
	}

	void ofxCommandProcessorThreadWin::run() {
		CoInitializeEx(NULL, COINIT_MULTITHREADED);
		running_ = true;
		while(running_) {
			sleep(1);
			//ofxCommand* command = take();
			boost::shared_ptr<ofxCommand> command = take();
			if(command) {
			//if(command != NULL) {
				bool complete = command->execute();
				//std::cout << "Running: " << command->name << std::endl;
				if(complete == false) {
					sleep(500);
					sync_.lock();
					queue.push_front(command); // we want to repeat it directly! (not at the end)
					sync_.unlock();
					//enqueue(command);
				}
				else {
				    OFXLOG("ofxCommandProcessorThreadWin::run() delete command:" << command->name);
					//delete command; // not necessary with shared_ptr
				}
			}
		}
	}

#endif
