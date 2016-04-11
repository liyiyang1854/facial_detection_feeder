#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

#include <stdint.h>   // Standard types 

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofVideoGrabber vidGrabber;
    ofxCvHaarFinder faceFinder;
    
    int threshold, vidWidth, vidHeight, this_point;
    float headposx, headposy, headposwidth, headposheight, oldheadposx, oldheadposy, prox, proy;
    
    bool posvalid = false;
    
    ofTrueTypeFont font;
    
};


#ifndef __ARDUINO_SERIAL_LIB_H__
#define __ARDUINO_SERIAL_LIB_H__

#include <stdint.h>   // Standard types

int serialport_init(const char* serialport, int baud);
int serialport_close(int fd);
int serialport_writebyte( int fd, uint8_t b);
int serialport_write(int fd, const char* str);
int serialport_read_until(int fd, char* buf, char until, int buf_max,int timeout);
int serialport_flush(int fd);

#endif


