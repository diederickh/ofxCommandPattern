#ifndef OFXACTIONLISTENERH
#define OFXACTIONLISTENERH
class ofxActionEvent;
class ofxActionListener {
public:
	virtual void actionPerformed(const ofxActionEvent& rEvent) = 0;
};
#endif