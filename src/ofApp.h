#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#include "ofxGui.h"

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofxXmlSettings XML;

    ofTrueTypeFont font;
    ofTrueTypeFont titleFont;

    ofxOscReceiver recv;
    ofxOscSender local;
    int portR, portL;
    string ip1, ip2, ip3;
    string clientMessages; // string containing the received messages for display
    string msg1, msg2, msg3;
    
    // Parse an OscMessage into a string for easy logging
    string getOscMsgAsString(ofxOscMessage m);
    
    ofxPanel gui;
    ofParameter<int> port;
    ofxVec2Slider slider;
    
    int state;
};
