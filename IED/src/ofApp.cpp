#include "ofApp.h"
#include "arduino-serial-lib.h"
#include <vector>

#include <stdio.h>    // Standard input/output definitions
#include <unistd.h>   // UNIX standard function definitions
#include <fcntl.h>    // File control definitions
#include <errno.h>    // Error number definitions
#include <termios.h>  // POSIX terminal control definitions
#include <string.h>   // String function definitions
#include <sys/ioctl.h>
int dev;

void data_trasfer(int dev, int val){
    vector<int> vec;
    while (val){
        vec.push_back(val%10);
        val /=10;
    }
    for (int i = vec.size()-1; i >= 0; --i){
        serialport_writebyte(dev, vec[i]+48);
    }
}

//--------------------------------------------------------------
void ofApp::setup(){
    dev = serialport_init("/dev/cu.usbserial-A504ECXV", 38400);
    serialport_flush(dev);
    //Detection
    //////////////////////////////
    threshold = 160;
    vidWidth = 320;
    vidHeight = 200;
    
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(vidWidth, vidHeight);
    
    faceFinder.setup("haarcascade_frontalface_alt2.xml");
    
    font.loadFont("AmericanTypewriter.ttc", 40);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //Detection
    //////////////////////////////
    ofBackground(ofColor::black);
    vidGrabber.update();
    
    if (vidGrabber.isFrameNew()) {
        faceFinder.findHaarObjects(vidGrabber.getPixelsRef());
    }
    
    //Find face position
    headposx = headposy = headposwidth = headposheight = 0;
    for (int i = 0; i < faceFinder.blobs.size(); i++) {
        if (headposwidth*headposheight <
            faceFinder.blobs[i].boundingRect.width*faceFinder.blobs[i].boundingRect.height){
            headposwidth = faceFinder.blobs[i].boundingRect.width;
            headposheight = faceFinder.blobs[i].boundingRect.height;
            headposx = (240 - faceFinder.blobs[i].boundingRect.x)*6;
            headposy = (faceFinder.blobs[i].boundingRect.y+20)*6;
            this_point = i;
        }
    }
    
    //Check whether values stored in headposx and headposy
    //also limit the changes of the positions
    if (headposx>0 && headposy>0){
        posvalid = true;
        if (oldheadposx>0 && oldheadposy>0){
            if (headposx - oldheadposx > 40){
                headposx = oldheadposx + 40;
            }
            if (headposy - oldheadposy > 40){
                headposy = oldheadposy + 40;
            }
            if (oldheadposx - headposx > 40){
                headposx = oldheadposx - 40;
            }
            if (oldheadposy - headposy > 40){
                headposy = oldheadposy - 40;
            }
        }
    }
    else{
        posvalid = false;
    }
    
    
}

//--------------------------------------------------------------
//--------------------------------------------------------------
void ofApp::draw(){
    
    //Detection
    //////////////////////////////
    if (posvalid) {
        
        //Output to files
        
        prox = (int)(faceFinder.blobs[this_point].boundingRect.x+faceFinder.blobs[this_point].boundingRect.width/2);
        ///320;
        proy = (int)(faceFinder.blobs[this_point].boundingRect.y+faceFinder.blobs[this_point].boundingRect.height/2);
        ///200;
        std::cout << "x " << prox << " y " << proy << std::endl;
        data_trasfer(dev, prox);
        serialport_writebyte(dev, ',');
        
        data_trasfer(dev, proy);
        serialport_writebyte(dev, '.');
        
        //Output to screens
        ofSetColor(ofColor::white);
        
        ofNoFill();
        
        ofPushMatrix();
        ofTranslate(20, 20);
        vidGrabber.draw(0, 0);
        
        ofRect(faceFinder.blobs[this_point].boundingRect);
        
        ofPopMatrix();
    }
    else {
        font.drawString("LOADING...", 30, 130);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}



// takes the string name of the serial port (e.g. "/dev/tty.usbserial","COM1")
// and a baud rate (bps) and connects to that port at that speed and 8N1.
// opens the port in fully raw mode so you can send binary data.
// returns valid fd, or -1 on error
int serialport_init(const char* serialport, int baud)
{
    struct termios toptions;
    int fd;
    
    //fd = open(serialport, O_RDWR | O_NOCTTY | O_NDELAY);
    fd = open(serialport, O_RDWR | O_NONBLOCK );
    
    if (fd == -1)  {
        perror("serialport_init: Unable to open port ");
        return -1;
    }
    
    if (tcgetattr(fd, &toptions) < 0) {
        perror("serialport_init: Couldn't get term attributes");
        return -1;
    }
    speed_t brate = baud;
    switch(baud) {
        case 4800:   brate=B4800;   break;
        case 9600:   brate=B9600;   break;
#ifdef B14400
        case 14400:  brate=B14400;  break;
#endif
        case 19200:  brate=B19200;  break;
#ifdef B28800
        case 28800:  brate=B28800;  break;
#endif
        case 38400:  brate=B38400;  break;
        case 57600:  brate=B57600;  break;
        case 115200: brate=B115200; break;
    }
    cfsetispeed(&toptions, brate);
    cfsetospeed(&toptions, brate);
    
    // 8N1
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    // no flow control
    toptions.c_cflag &= ~CRTSCTS;
    
    toptions.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl
    
    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    toptions.c_oflag &= ~OPOST; // make raw
    
    toptions.c_cc[VMIN]  = 0;
    toptions.c_cc[VTIME] = 0;
    
    tcsetattr(fd, TCSANOW, &toptions);
    if( tcsetattr(fd, TCSAFLUSH, &toptions) < 0) {
        perror("init_serialport: Couldn't set term attributes");
        return -1;
    }
    return fd;
}

int serialport_close( int fd )
{
    return close( fd );
}

int serialport_writebyte( int fd, uint8_t b)
{
    int n = write(fd,&b,1);
    if( n!=1)
        return -1;
    return 0;
}

int serialport_write(int fd, const char* str)
{
    int len = strlen(str);
    int n = write(fd, str, len);
    if( n!=len ) {
        perror("serialport_write: couldn't write whole string\n");
        return -1;
    }
    return 0;
}

int serialport_read_until(int fd, char* buf, char until, int buf_max, int timeout)
{
    char b[1];  // read expects an array, so we give it a 1-byte array
    int i=0;
    do {
        int n = read(fd, b, 1);  // read a char at a time
        if( n==-1) return -1;    // couldn't read
        if( n==0 ) {
            usleep( 1 * 1000 );  // wait 1 msec try again
            timeout--;
            continue;
        }
#ifdef SERIALPORTDEBUG
        printf("serialport_read_until: i=%d, n=%d b='%c'\n",i,n,b[0]); // debug
#endif
        buf[i] = b[0];
        i++;
    } while( b[0] != until && i < buf_max && timeout>0 );
    
    buf[i] = 0;  // null terminate the string
    return 0;
}

int serialport_flush(int fd)
{
    sleep(2); //required to make flush work, for some reason
    return tcflush(fd, TCIOFLUSH);
}


