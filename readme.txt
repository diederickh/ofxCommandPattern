ofxCommandPattern
=================
The ofxCommandPattern was created for the ofxSuperCanon. The ofxSuperCanon
addon is a port of the CanonSDK version 2.8.  The ofxCommandPattern is an
implementation of the command pattern with a mix of the model/view 
controller. Though the view and controller are not in the example; the
model/view should be created by yourself.

First it looks a bit cluttered all these classes and separate Commands, though
when you get used to it, it really helps to write clean, nice ordered code.
The ofxCommandPattern let you define custom commands and add these commands
to a ofxCommandProcessor. This processor runs in it's own thread and will
execute the enqueueed commands one afther the other. This is especially 
helpfull when working on multi threaded applications; each command
can run in a separate thread and you can schedule which command should be 
executed before another one.




