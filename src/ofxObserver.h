#ifndef OFXOBSERVERH
#define OFXOBSERVERH

#include <vector>
#include <algorithm>
#include <string>

#include "ofxObservableEvent.h"
class ofxObservable;


class ofxObserver {
public:
	virtual void update(ofxObservable* pFrom, ofxObservableEvent* pEvent) = 0;
};

class ofxObservable {
private:
	std::vector<ofxObserver*> observers;

public:

	// Add a *new* observer
	void addObserver(ofxObserver* pObserver) {
		if(pObserver == NULL)
			return;
		if(observers.size() == 0) 
			observers.push_back(pObserver);
		else if(std::find(observers.begin(), observers.end(), pObserver) == observers.end()) {
			observers.push_back(pObserver);
		}
	}
	
	void deleteObserver(const ofxObserver* pObserver) {
		std::vector<ofxObserver*>::iterator i = std::find(observers.begin(), observers.end(), pObserver);
		if(i != observers.end()) {
			observers.erase(i);
		}
		else {
			cout << "Cannot delete observer, couldnt find it!\n";
		}
	}
	
	void notifyObservers(ofxObservableEvent* pEvent = NULL) {
		std::vector<ofxObserver*>::reverse_iterator i = observers.rbegin();
		while(i != observers.rend()) {
			(*i++)->update(this, pEvent);
		}
	}
	
	void deleteObservers() {
		observers.clear();
	}	
	
	int countObservers() const { 
		return (int)observers.size();
	}
};
#endif