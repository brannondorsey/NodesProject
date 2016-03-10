#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofHideCursor();
//--------------------setup nodes
    ofSeedRandom(70);
    for(int i = 0; i<50; i++) {
        ofVec3f newNode = ofVec3f(50+ofRandom(ofGetWidth()-100),ofRandom(ofGetHeight()-200), 0);
        nodes.push_back(newNode);
    }
//--------------------setup lighting
    ofColor color;
    color.setBrightness(150);
    ofSetSmoothLighting(true);
    light1.setDiffuseColor( ofFloatColor(.85, .85, .75) );
    light1.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    light1.setGlobalPosition(0, 0, 600);
    light1.enable();
    
    light2.setDiffuseColor( ofFloatColor(.75, .75, .85) );
    light2.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    light2.setGlobalPosition(2000, 1080, 600);
    light2.enable();
    
//--------------------setup GL stuff
    ofEnableDepthTest();
    ofEnableAlphaBlending();
    //glShadeModel(GL_FLAT);
    
//--------------------setup GUI
    gui.setup();
    gui.add(maxSpd.setup("maximum speed", 2.1, .1, 8));
    gui.add(alphaTagetAng.setup("angle change", 30, 3, 40));
//--------------------setup blur
    blur.setup(ofGetWidth()/2, ofGetHeight()/2, 10, .9, 10, 0.9);
    
//--------------------setup FBO
    myFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    myFbo.begin();
    ofClear(255,255,255, 0);
    myFbo.end();
    
//---------------------setup sound
    string myPath = "launcher";
    ofDirectory launcher (myPath);
    launcher.listDir();
    for (int i=0; i<launcher.size(); ++i) {
        ofSoundPlayer launch;
        launch.load(launcher.getPath(i));
        launch.setMultiPlay(true);
        launch.setVolume(.8);
        launches.push_back(launch);
    }
    myPath = "lander";
    ofDirectory lander (myPath);
    lander.listDir();
    for (int i=0; i<lander.size(); ++i) {
        ofSoundPlayer land;
        land.load(lander.getPath(i));
        land.setMultiPlay(true);
        land.setVolume(.8);
        landings.push_back(land);
    }
    
    for(int i = 0; i<50; i++) {
        pings[i] = 0;
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    // Call the appropriate steering behaviors for our agents
    bool giveBack = false;
    ofVec3f myTarg;
    ofVec3f myStart;
    Byte theTarg, theStart;
    for(std::vector<cluster>::iterator it = clusters.begin() ; it != clusters.end(); ++it) {
        if((*it).update(maxSpd, alphaTagetAng)) {
            //landings[(*it).ping].play();
            if(pings[(*it).tNode] == 0) pings[(*it).tNode] = 6;
            if(ofRandom(100)>95){
                giveBack = true;
                myTarg = (*it).target;
                myStart = (*it).start;
                theTarg = (*it).tNode;
                theStart = (*it).sNode;
            }
        }
        if (!(*it).life) {
            clusters.erase(it);
            --it;
        }
    }
    
    if(giveBack) respawn(myTarg, myStart, theTarg, theStart);
    
    myFbo.begin();
    
    ofBackground(0);
    ofEnableDepthTest();
    ofEnableAlphaBlending();
    
    
    ofEnableLighting();
    light1.enable();
    light2.enable();
    ofSetColor(255);
    
    for(std::vector<cluster>::iterator it = clusters.begin() ; it != clusters.end(); ++it) {
        (*it).display();
    }
    
    ofDisableLighting();
    ofDisableDepthTest();
    ofDisableAlphaBlending();

    myFbo.end();
    
    //ofSoundUpdate();
    
    float currentTime = ofGetElapsedTimeMillis();
    if( currentTime-lastTime>65){
        dotUpdates();
        lastTime = ofGetElapsedTimeMillis();
    }
    
    if (ofRandom(30000)>29970) {
        spawn();
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofRectangle myBlur = ofRectangle(0, 0, 1920, 1200);
    ofBackground(0);
    ofSetColor(255);
    ofDisableAlphaBlending();
    blur.begin();
    myFbo.draw(0, 0, 960, 600);
    blur.end();
    
    ofSetColor(255, 255);
    myFbo.draw(0,0);
    ofEnableBlendMode(OF_BLENDMODE_SCREEN);
    blur.draw(myBlur);
    blur.draw(myBlur);
    //blur.draw();
    ofDisableBlendMode();

    
    ofFill();
    
    for(std::vector<ofVec3f>::iterator it = nodes.begin() ; it != nodes.end(); ++it) {
        if((*it).z == 1){
            ofSetColor(250);
            ofDrawCircle((*it).x, (*it).y, 5);
        }else{
            ofSetColor(0);
            ofDrawCircle((*it).x, (*it).y, 10);
        }
        
    }
    ofSetColor(255);
    //ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 250, 15);
    //gui.draw();
    
    
    
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

    int num = int(ofRandom(1, 5));
    int startNode = ofRandom(nodes.size());
    for(int i = 0;i<num;i++){
        int targetNode = ofRandom(nodes.size());
        while (startNode==targetNode) {
            targetNode = ofRandom(nodes.size());
        }
        cluster newCluster(nodes[startNode], nodes[targetNode], startNode,targetNode);
        clusters.push_back(newCluster);
        int whichLaunch = ofRandom(launches.size());
        //launches[whichLaunch].play();
        pings[startNode] = 4;
    }
}


//--------------------------------------------------------------
void ofApp::respawn(ofVec3f target, ofVec3f start, Byte tempTarg, Byte tempStart){

        cluster newCluster(target, start, tempTarg, tempStart);
        clusters.push_back(newCluster);
        //launches[int(ofRandom(launches.size()))].play();
}

//--------------------------------------------------------------
void ofApp::dotUpdates(){
    int myIter = 0;
    for(std::vector<ofVec3f>::iterator it = nodes.begin() ; it != nodes.end(); ++it) {
        if (pings[myIter]>0) {
            if((*it).z == 0){
                (*it).z = 1;
            }else if ((*it).z == 1){
                (*it).z = 0;
            }
            pings[myIter]--;
        }else{ (*it).z = 0;}
        myIter++;
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
