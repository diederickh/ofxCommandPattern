#ifndef OFXACTIONEVENTH
#define OFXACTIONEVENTH
#include <string>
class ofxActionEvent {
private:	
	std::string command;
	void* arg;
public:

	const std::string getActionCommand() const {
		return command;	
	}
	
	void* getArg() const { 
		return arg; 
	}
	
	ofxActionEvent(std::string sCommand, void* pArg = 0)
		:command(sCommand) 
		,arg(pArg)
	{
	}
};
#endif