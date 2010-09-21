#ifndef OFXACTIONSOURCEH
#define OFXACTIONSOURCEH
#include <vector>
#include <algorithm>
#include "ofxActionEvent.h"
#include "ofxActionListener.h"

/**
 * Definition for a ActionSource. 
 *
 * After an action source if fired the listeners will be notified that a 
 * request is made to execute the action source. The controller will be called
 * which will handle the action source on it's own way. 
 *
 * i.e. [button press] --> [action: Print clicked] --> [action:fireEvent()] 
 * -> [controller:onActionPerformed(), print!]
 *
 */
 
class ofxActionSource {
private:
	std::vector<ofxActionListener*> listeners;
	std::string command;
	
public:
	// Add a new listener for this action, only when not added yet.
	void addActionListener(ofxActionListener* pListener) {
		if(std::find(listeners.begin(), listeners.end(), pListener) == listeners.end()) {
			listeners.push_back(pListener);
		}
	}
	
	void setActionCommand(std::string sCommand) { command = sCommand; }
	
	void fireEvent(void* pArg = 0) {
		ofxActionEvent event(command, pArg);
		std::vector<ofxActionListener*>::iterator i = listeners.begin();
		while(i != listeners.end()) {
			(*i++)->actionPerformed(event);
		}
	}
	
	void fireEvent(std::string sCommand, void* pArg = 0) {
		setActionCommand(sCommand);
		fireEvent(pArg);
	}
	
	ofxActionSource() : listeners(0){}
	virtual ~ofxActionSource(){}
};
#endif