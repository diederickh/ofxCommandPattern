#ifndef OFXOBSERVERH
#define OFXOBSERVERH

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <boost/thread.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "ofxObservableEvent.h"
class ofxObservable;


class ofxObserver {
public:
	//virtual void update(ofxObservable* pFrom, ofxObservableEvent* pEvent) = 0;
	virtual void update(boost::shared_ptr<ofxObservable> pFrom, boost::shared_ptr<ofxObservableEvent> pEvent) = 0;
};

class ofxObservable : public boost::enable_shared_from_this<ofxObservable> {
protected:
	//std::vector<ofxObserver*> observers;
	std::vector<boost::shared_ptr<ofxObserver> > observers;

public:

	// Add a *new* observer
	//virtual void addObserver(ofxObserver* pObserver) {
	virtual void addObserver(boost::shared_ptr<ofxObserver> pObserver) {
		if(pObserver == NULL)
			return;
		if(observers.size() == 0)
			observers.push_back(pObserver);
		else if(std::find(observers.begin(), observers.end(), pObserver) == observers.end()) {
			observers.push_back(pObserver);
		}
	}

	//virtual void deleteObserver(const ofxObserver* pObserver) {
	virtual void deleteObserver(boost::shared_ptr<ofxObserver> pObserver) {
		//std::vector<ofxObserver*>::iterator i = std::find(observers.begin(), observers.end(), pObserver);
		std::vector<boost::shared_ptr<ofxObserver> >::iterator i = std::find(observers.begin(), observers.end(), pObserver);
		if(i != observers.end()) {
			observers.erase(i);
		}
		else {
			std::cout << "Cannot delete observer, couldnt find it!\n";
		}
	}

	//void notifyObservers(ofxObservableEvent* pEvent = NULL) {
	void notifyObservers(boost::shared_ptr<ofxObservableEvent> pEvent) {
		//std::cout << "notify observers in ofxObservable: " << boost::this_thread::get_id() << std::endl;
		//std::cout << "observers: "<< observers.size() << std::endl;
		//std::vector<ofxObserver*>::reverse_iterator i = observers.rbegin();
		std::vector<boost::shared_ptr<ofxObserver> >::reverse_iterator i = observers.rbegin();
		while(i != observers.rend()) {
			//ofxObserver* observer = (*i);
			boost::shared_ptr<ofxObserver> observer = (*i);
			boost::shared_ptr<ofxObservable> me(shared_from_this());
			observer->update(me, pEvent);
			++i;
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
