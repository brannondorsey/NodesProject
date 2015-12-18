#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for(int i = 0; i<500; i++) {
        car tempV = car(ofGetWidth()/2 + ofRandom(-10,10), ofGetHeight()/2 + ofRandom(-10,10));
        cars.push_back(tempV);
    }
    node = ofVec2f(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));
}

//--------------------------------------------------------------
void ofApp::update(){
    ofVec2f mouse = ofVec2f(mouseX, mouseY);
    
    // Call the appropriate steering behaviors for our agents
    for(std::vector<car>::iterator it = cars.begin() ; it != cars.end(); ++it) {
        (*it).wander(node);
        (*it).arrive(node);
        (*it).update();
        if (!(*it).life) {
            cars.erase(it);
            --it;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    // Draw an ellipse at the mouse location
    ofFill();
    ofSetColor(200);
 //   stroke(0);
//    strokeWeight(2);
    //ofDrawCircle(mouseX, mouseY, 48, 48);
    
    for(std::vector<car>::iterator it = cars.begin() ; it != cars.end(); ++it) {
        (*it).display();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key==32 ) {
        for(int i = 0; i<500; i++) {
            car tempV = car(ofGetWidth()/2 + ofRandom(-10,10), ofGetHeight()/2 + ofRandom(-10,10));
            cars.push_back(tempV);
        }
        node = ofVec2f(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));
    }
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
