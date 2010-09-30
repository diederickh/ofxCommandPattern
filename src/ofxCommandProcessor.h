#ifndef OFXCOMMANDPROCESSOR
#define OFXCOMMANDPROCESSOR

#include <deque>
#include <iostream>
//#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/shared_ptr.hpp>
class ofxCommand;
class ofxCommandProcessor  {
public:
	ofxCommandProcessor();
	~ofxCommandProcessor();
	//virtual void enqueue(boost::shared_ptr<ofxCommand> pCommand);
	virtual void enqueue(boost::shared_ptr<ofxCommand> pCommand);
	virtual void remove(std::string sName);
	virtual void clear();
	virtual bool isReady();
	virtual void update();

protected:
	//std::deque<ofxCommand*>  queue;
	std::deque<boost::shared_ptr<ofxCommand> > queue;
	//boost::ptr_deque<ofxCommand> queue;
	//virtual ofxCommand* take();
	virtual boost::shared_ptr<ofxCommand> take();
};

#endif
