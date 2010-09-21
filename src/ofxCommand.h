#ifndef OFXCOMMANDH
#define OFXCOMMANDH
#include <string>

class ofxCommand {
public:
	ofxCommand(std::string sName):name(sName) {};
	virtual bool execute() = 0;
	std::string name;
};
#endif