#ifndef OFXOBSERVABLEEVENTH
#define OFXOBSERVABLEEVENTH
class ofxObservableEvent {
private:
	std::string event;
	void* arg;

public:
	const std::string getEvent() const { return event; }
	void* getArg() const { return arg; }
	
	ofxObservableEvent(std::string sEvent, void* pArg = 0)
		:event(sEvent)
		,arg(pArg)
	{
	}
		
};
#endif