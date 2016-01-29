#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for(int i = 0; i<50; i++) {
        ofVec2f newNode = ofVec2f(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));
        nodes.push_back(newNode);
    }
    
//    for(int i = 0; i<500; i++) {
//        car tempV = car(ofGetWidth()/2 + ofRandom(-10,10), ofGetHeight()/2 + ofRandom(-10,10));
//        cars.push_back(tempV);
//    }
    wide = ofGetWidth();
    high = ofGetHeight();
    for (int x=0; x<wide ; x++) {
        for (int y = 0; y<high; y++) {
            noises.push_back(int(255*ofNoise(x, y, ofGetFrameNum())));
        }
    }
    
    gui.setup();
    gui.add(maxSpd.setup("maximum speed", 1.5, .1, 8));
    gui.add(alphaTagetAng.setup("angle change", 30, 3, 40));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    // Call the appropriate steering behaviors for our agents
    for(std::vector<car>::iterator it = cars.begin() ; it != cars.end(); ++it) {
        (*it).wander(&noises);
        (*it).arrive();
        (*it).update(maxSpd, alphaTagetAng);
        if (!(*it).life) {
            cars.erase(it);
            --it;
        }
    }
    int frame = ofGetFrameNum();
    if(frame%10==0){
    for (int x=0; x<wide ; x+=4) {
        for (int y = 0; y<high; y+=4) {
            noises[y+high*x]=int(255*ofNoise(x/500.0, y/500.0, frame/300.0));
        }
    }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
//    int frame = ofGetFrameNum();
//    if(frame%10==0){
//        for (int x=0; x<wide ; x+=4) {
//            for (int y = 0; y<high; y+=4) {
//                ofSetColor(noises[y+high*x]);
//                ofDrawRectangle(x, y, 4, 4);
//            }
//        }
//    }

    // Draw an ellipse at the mouse location
    ofFill();
    ofSetColor(200);
 //   stroke(0);
//    strokeWeight(2);
    //ofDrawCircle(mouseX, mouseY, 48, 48);
    
    for(std::vector<car>::iterator it = cars.begin() ; it != cars.end(); ++it) {
        (*it).display();
    }
    ofFill();
    ofSetColor(200);
    for(std::vector<ofVec2f>::iterator it = nodes.begin() ; it != nodes.end(); ++it) {
        ofDrawCircle((*it).x, (*it).y, 4);
    }
    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 250, 15);

    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key==32 ) {
        spawn();
        //node = ofVec2f(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));
    }
}

//--------------------------------------------------------------
void ofApp::spawn(){
    int traffic = ofRandom(10, 40);
    int startNode = ofRandom(nodes.size());
    int targetNode = ofRandom(nodes.size());
    while (startNode==targetNode) {
        targetNode = ofRandom(nodes.size());
    }
    
    for(int i = 0; i<traffic; i++) {
        car tempV = car(nodes[startNode], nodes[targetNode]);
        cars.push_back(tempV);
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
