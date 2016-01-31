//
//  cluster.cpp
//  nodes01
//
//  Created by Chris Coleman on 1/28/16.
//
//

#include "cluster.h"
#include "ofApp.h"

cluster::cluster(ofVec3f start, ofVec3f target) {
    life = true;
    int traffic = ofRandom(40, 100);
    for(int i = 1; i<traffic; i++) {
        car tempV = car(start, target, i);
        cars.push_back(tempV);
        trail.addVertex(start);
        trail.addVertex(start);
        trail.getNumVertices();
    }
    
    trail.setMode(OF_PRIMITIVE_LINES);
    col = ofColor(ofRandom(220,250),ofRandom(180,250), ofRandom(180,250));
    

}

void cluster::update(int maxSpd, int alphaTagetAng) {
    int frame = ofGetFrameNum();
    
    for(std::vector<car>::iterator it = cars.begin() ; it != cars.end(); ++it) {
        (*it).wander();
        (*it).arrive();
        (*it).update(maxSpd, alphaTagetAng);
        
        trail.setVertex((*it).leadVert, (*it).location);
        
        if(frame%30==0){
            trail.addVertex((*it).location);
            (*it).leadVert = trail.getNumVertices()-1;
        }
        
        if (!(*it).life) {
            cars.erase(it);
            --it;
        }
    }
    if (cars.size()<1) {
        life = false;
    }
}

void cluster::display(){
    
    
    for(std::vector<car>::iterator it = cars.begin() ; it != cars.end(); ++it) {
        (*it).display();
    }
    ofSetColor(col, 30);
    trail.draw();
}