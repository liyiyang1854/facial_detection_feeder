#include "ofMain.h"
#include "ofApp.h"




//========================================================================
int main( ){
    /*
    
     int dev = serialport_init("/dev/cu.usbserial-A504ECXV", 38400);
    serialport_flush(dev);
    */
    ofSetupOpenGL(360,240,OF_WINDOW);			// <-------- setup the GL context
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
    
}
