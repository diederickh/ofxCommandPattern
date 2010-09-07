#ifndef OFXOBSERVERH
#define OFXOBSERVERH

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "ofxObservableEvent.h"
class ofxObservable;


class ofxObserver {
public:
	virtual void update(ofxObservable* pFrom, ofxObservableEvent* pEvent) = 0;
};

class ofxObservable {
protected:
	std::vector<ofxObserver*> observers;

public:

	// Add a *new* observer
	virtual void addObserver(ofxObserver* pObserver) {
		if(pObserver == NULL)
			return;
		if(observers.size() == 0) 
			observers.push_back(pObserver);
		else if(std::find(observers.begin(), observers.end(), pObserver) == observers.end()) {
			observers.push_back(pObserver);
		}
	}
	
	virtual void deleteObserver(const ofxObserver* pObserver) {
		std::vector<ofxObserver*>::iterator i = std::find(observers.begin(), observers.end(), pObserver);
		if(i != observers.end()) {
			observers.erase(i);
		}
		else {
			std::cout << "Cannot delete observer, couldnt find it!\n";
		}
	}
	
	virtual void notifyObservers(ofxObservableEvent* pEvent = NULL) {
		std::cout << "observers: "<< observers.size() << std::endl;
		std::vector<ofxObserver*>::reverse_iterator i = observers.rbegin();
		while(i != observers.rend()) {
			(*i++)->update(this, pEvent);
		}
	}
	
	virtual void deleteObservers() {
		observers.clear();
	}	
	
	virtual int countObservers() const { 
		return (int)observers.size();
	}
};
#endif