#ifndef MYCOMMANDCONTROLLERH
#define MYCOMMANDCONTROLLERH

#include "ofxCommandPattern.h"
#include "ofxCommandTest.h"

class MyCommandController : public ofxActionListener {
public:
	MyCommandController(){}
	
	void init() {
		// start the processor listener (this one is obligatory!)
		processor.startThread(false,false);
		
		// this serves as a demo; we add ourself to the action listener,
		// in a real application this could be i.e. a button press.
		test_action.setActionCommand("test_action");
		test_action.addActionListener(this);
	}
	
	/**
	 * Make sure you implement this method which is called when a 
	 * user-action is executed. The call to this method is instantiated
	 * by a ofxActionSource to which this controller is listening.
	 * 
	 * In here we actually enqueue the command which as to be executed
	 * for the specific ofxActionEvent event. This command is executed by
	 * the processor when it's his turn to be executed. Note, that the 
	 * execution of the commands occurs in a separate thread.
	 *
	 *
	 */	
	void actionPerformed(const ofxActionEvent& rEvent) {
		// this is the heart of the controller, when you call executeTest(), 
		// this method is called as we've been added as a listener. Then
		// we enqueue the ofxCommandTest to the thread which will execute 
		// the command after it finishes the previously added commands.
		printf("Someone performed an action: %s\n", rEvent.getActionCommand().c_str());			
		if(rEvent.getActionCommand() == "test_action") {
			printf("Added the command to the queue.\n");
			string command_name = "Test command " +ofToString(ofGetElapsedTimeMillis());
			processor.enqueue(new ofxCommandTest(command_name));
		}

	}
	
	void executeTest() {
		test_action.fireEvent();
	}

private:
	ofxCommandProcessor processor;
	ofxActionSource test_action;
};
#endif