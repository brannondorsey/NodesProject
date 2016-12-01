#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofHideCursor();
    wide = ofGetWidth();
    high = ofGetHeight();

//--------------------setup nodes
    //ofSeedRandom(70);
    for(int i = 0; i<30; i++) {
        ofVec3f newNode = ofVec3f(ofRandom(wide),ofRandom(high), 0);
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
    light2.setGlobalPosition(1080, 2000, 600);
    light2.enable();
    
//--------------------setup GL stuff
    ofEnableDepthTest();
    ofEnableAlphaBlending();
    //glShadeModel(GL_FLAT);
    
//--------------------setup GUI
   // gui.setup();
   // gui.add(maxSpd.setup("maximum speed", 2.1, .1, 8));
   // gui.add(alphaTagetAng.setup("angle change", 30, 3, 40));
//--------------------setup blur
    blur.setup(wide/2, high/2, 10, .9, 10, 0.9);
    
//--------------------setup FBO
    myFbo.allocate(wide, high, GL_RGBA);
    myFbo.begin();
    ofClear(255,255,255, 0);
    myFbo.end();
    targetPos = ofVec3f(wide/2, high/2, 1800);
    startPos = targetPos;
    cam.setGlobalPosition(targetPos);
    cam.lookAt(ofVec3f(wide/2, high/2, 0));
    
    camMove = false;
    
//---------------------setup sound
/*    string myPath = "launcher";
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
    */
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // Call the appropriate steering behaviors for our agents
    bool giveBack = false;
    ofVec3f myTarg;
    ofVec3f myStart;
    BYTE theTarg, theStart;
    //for(std::vector<Cluster>::iterator it = clusters.begin() ; it != clusters.end(); ++it) {
    clusters.erase(std::remove_if(clusters.begin(),clusters.end(), [&](Cluster & cluster){
		if(cluster.update(2.1, 30)) {
            //landings[(*it).ping].play();
            if(pings[cluster.tNode] == 0) pings[cluster.tNode] = 6;
            if(ofRandom(100)>95){
                giveBack = true;
                myTarg = cluster.target;
                myStart = cluster.start;
                theTarg = cluster.tNode;
                theStart = cluster.sNode;
            }
        }
		return !cluster.life;
	}), clusters.end());
    
    if(giveBack) respawn(myTarg, myStart, theTarg, theStart);
    

    
    //ofSoundUpdate();
    
    float currentTime = ofGetElapsedTimeMillis();
    if( currentTime-lastTime>45){
        dotUpdates();
        lastTime = ofGetElapsedTimeMillis();
    }
    
    if (ofRandom(30000)>29970) {
        spawn();
    }
    
    bool found = false;
    if(clusters.size()>0){
        for(int i = 0; i<clusters.size(); i++){
            if(clusters.at(i).cars.size()>0){
                ofVec3f camPos = clusters.at(i).leader;
                camPos += ofVec3f(0,0,700);
                targetPos = camPos;
                found = true;
                break;
            }
        }
        
        if(!found){
            startPos = cam.getGlobalPosition();
            targetPos = ofVec3f(wide/2, high/2, 1700);
        }
    }
    
    if(startPos.distance(targetPos)>2) camMove = true;
    
    if(camMove){
        ofVec3f interPos;					//this will hold our tweened position.
        // calculate the interpolated values.
        interPos = startPos.interpolate(targetPos, .01);
        cam.setGlobalPosition(interPos);
        //startPos = targetPos;
    }else{
        cam.setGlobalPosition(targetPos);
        startPos = targetPos;
        camMove = false;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //ofRectangle myBlur = ofRectangle(0, 0, wide/2, high/2);
    //ofBackground(0);
    //ofSetColor(255);
    ofDisableAlphaBlending();
    //blur.begin();
    //myFbo.draw(0, 0, wide/2, high/2);
    //blur.end();
    
    //myBlur.scale(2, 2);
    
//    cout<<myBlur.width<<endl;
//    cout<<myBlur.height<<endl;
    
    ofSetColor(255, 255);
	// myFbo.begin();
	cam.begin();
	ofBackground(0);
	ofEnableDepthTest();
	ofEnableAlphaBlending();


	ofEnableLighting();
	light1.enable();
	light2.enable();
	ofSetColor(255);

	for (std::vector<Cluster>::iterator it = clusters.begin(); it != clusters.end(); ++it) {
		(*it).display();
	}
	for (std::vector<ofVec3f>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
		//if((*it).z == 1){
		ofNoFill();
		ofSetColor(250, 255);
		ofDrawCircle((*it).x, (*it).y, 5);
		// }else{
		//   ofSetColor(100, 255);
		// ofDrawCircle((*it).x, (*it).y, 10);
		//}

	}
	ofSetColor(180);
	//ofBoxPrimitive(200, 200, 200);
	ofDisableLighting();
	ofDisableDepthTest();
	ofDisableAlphaBlending();
	cam.end();
	//myFbo.end();
    //myFbo.draw(0,0);
   // ofEnableBlendMode(OF_BLENDMODE_SCREEN);
   // blur.draw(myBlur);
   // blur.draw(myBlur);
    //blur.draw();
    ofDisableBlendMode();

    
    ofFill();
    
// flash the city
    
//    ofSetColor(255);
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

    int num = int(ofRandom(1, 3));
    int startNode = ofRandom(nodes.size());
    for(int i = 0;i<num;i++){
        int targetNode = ofRandom(nodes.size());
        while (startNode==targetNode) {
            targetNode = ofRandom(nodes.size());
        }
        Cluster newCluster(nodes[startNode], nodes[targetNode], startNode,targetNode);
        clusters.push_back(newCluster);
        //int whichLaunch = ofRandom(launches.size());
        //launches[whichLaunch].play();
        pings[startNode] = 4;
    }
}


//--------------------------------------------------------------
void ofApp::respawn(ofVec3f target, ofVec3f start, BYTE tempTarg, BYTE tempStart){

        Cluster newCluster(target, start, tempTarg, tempStart);
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
