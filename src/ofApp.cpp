#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for(int i = 0; i<50; i++) {
        ofVec3f newNode = ofVec3f(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()), 0);
        nodes.push_back(newNode);
    }
    
//    for(int i = 0; i<500; i++) {
//        car tempV = car(ofGetWidth()/2 + ofRandom(-10,10), ofGetHeight()/2 + ofRandom(-10,10));
//        cars.push_back(tempV);
//    }

    
    gui.setup();
    gui.add(maxSpd.setup("maximum speed", 1.5, .1, 8));
    gui.add(alphaTagetAng.setup("angle change", 30, 3, 40));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    // Call the appropriate steering behaviors for our agents
    for(std::vector<cluster>::iterator it = clusters.begin() ; it != clusters.end(); ++it) {
        (*it).update(maxSpd, alphaTagetAng);
        if (!(*it).life) {
            clusters.erase(it);
            --it;
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


    
    
    for(std::vector<cluster>::iterator it = clusters.begin() ; it != clusters.end(); ++it) {
        (*it).display();
    }
    ofFill();
    ofSetColor(200);
    for(std::vector<ofVec3f>::iterator it = nodes.begin() ; it != nodes.end(); ++it) {
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

    int startNode = ofRandom(nodes.size());
    int targetNode = ofRandom(nodes.size());
    while (startNode==targetNode) {
        targetNode = ofRandom(nodes.size());
    }
    cluster newCluster(nodes[startNode], nodes[targetNode]);
    clusters.push_back(newCluster);
    
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
