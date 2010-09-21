#ifndef OFXCOMMANDTESTH
#define OFXCOMMANDTESTH

#include "ofxCommand.h"
#include <string>

class ofxCommandTest : public ofxCommand {
	public:
		ofxCommandTest(std::string sName):name(sName){}
		
		virtual bool execute() {
			printf(">> Executing command: %s\n", name.c_str());
			sleep(3);
			return true;
		}
		
	private:
		std::string name;
};

#endif