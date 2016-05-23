#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0);
    
    state = 1;
    
    font.load("futura_book.otf", 12);
    titleFont.load("futura_book.otf", 12);
    
    XML.load("settings.xml");
    
    portR = XML.getValue("PORTS:NAME:ME", 5000);
    ip1 = XML.getValue("PORTS:NAME:IP1","");
    ip2 = XML.getValue("PORTS:NAME:IP2","");
    ip3 = XML.getValue("PORTS:NAME:IP3","");
    
    portL = XML.getValue("PORTS:NAME:LOCAL", (portR + 1));
    recv.setup(portR);

    local.setup("127.0.0.1",portL);

    gui.setup();
    gui.add(port.set( "port", state, 1, 4 ));
}

//--------------------------------------------------------------
void ofApp::update(){

    state = port;
    while(recv.hasWaitingMessages()){
        
        ofxOscMessage m, s;
        recv.getNextMessage(&m);
        string oldMessages = clientMessages;
        string old1 = msg1;
        string args;
        for(int i = 0; i < m.getNumArgs(); i++) {
            args = args + " " + m.getArgAsString(i);
        }
            
        clientMessages = m.getRemoteIp() + " " + m.getAddress() + " " + args + "\n" +oldMessages;
        if(m.getRemoteIp() == ip1)
            msg1 = m.getAddress() + " " + args + "\n" + msg1;
        if(m.getRemoteIp() == ip2)
            msg2 = m.getAddress() + " " + args + "\n";
        if(m.getRemoteIp() == ip3)
            msg3 = m.getAddress() + " " + args + "\n";
        s.setAddress(m.getAddress());
        s.addStringArg(args);
        local.sendMessage(s);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    string debug = "OSC client\nGetting messages from " + ofToString(portR);
    
    titleFont.drawString(debug, 250, 37);
    if(state == 1)
        font.drawString(clientMessages, 10, 180);
    if(state == 2) {
        titleFont.drawString(clientMessages, 10, 180);
        font.drawString(msg1, 360, 180);
    }
    if(state == 3) {
        titleFont.drawString(clientMessages, 10, 180);
        font.drawString(msg2, 360, 180);
    }
    if(state == 4) {
        titleFont.drawString(clientMessages, 10, 180);
        font.drawString(msg3, 360, 180);
    }
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
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
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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

//--------------------------------------------------------------
string ofApp::getOscMsgAsString(ofxOscMessage m){
    string msg_string;
    msg_string = m.getAddress();
    msg_string += ":";
    for(int i = 0; i < m.getNumArgs(); i++){
        // get the argument type
        msg_string += " " + m.getArgTypeName(i);
        msg_string += ":";
        // display the argument - make sure we get the right type
        if(m.getArgType(i) == OFXOSC_TYPE_INT32){
            msg_string += ofToString(m.getArgAsInt32(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
            msg_string += ofToString(m.getArgAsFloat(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
            msg_string += m.getArgAsString(i);
        }
        else{
            msg_string += "unknown";
        }
    }
    return msg_string;
}
