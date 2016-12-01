//
//  car.cpp
//  nodes01
//
//  Created by Chris Coleman on 12/14/15.
//
//
#include "ofApp.h"
#include "car.h"

car::car(ofVec3f start, ofVec3f target, int num) {
    acceleration = ofVec3f(0,0, 0);
    float vel = 1.25;
    velocity = ofVec3f(ofRandom(-vel, vel) ,ofRandom(-vel, vel), ofRandom(-vel, vel));
    location = start;
    targetLoc = target;
    r = 2.0;
    targetDistance = r * 10.0;
    targetRadius = r * 4.0;
    alphaTargetAngle = 25.0;        // maximum change in angle each frame (in + and - direction, so max change actually double this)
    targetRelative = ofVec3f(0,0,0);  // similar to 'desired' vector in other examples, position of target relative to vehicle
    maxspeed = 4.0;
    maxforce = ofRandom(.02,.1);
    arriveRadius = 15.0;

    life = true;
    high = ofGetHeight();
    leadVert = (num*2)-1;
    
    frequency = 0.8;
    timeFrequency = .3;
    gridSize = 7.0;
}

void car::update(int maxSpd, int alphaTagetAng) {
    maxspeed = maxSpd;
    alphaTargetAngle = alphaTagetAng;
    velocity += acceleration;
    velocity.limit(maxspeed);
    location += velocity;
    acceleration *= 0;

}

void car::wander() {

    float time = ofGetElapsedTimef();
    float noiseTime = time * timeFrequency;
    
    ofVec3f extentMin( 0, 0, gridSize*-0.5 );
    ofVec3f extentMax( gridSize, gridSize, gridSize *  0.5 );
    
    ofVec3f pos;
    
    pos.x = ofMap( location.x,  0, 2000, extentMin.x, extentMax.x );
    pos.y = ofMap( location.y,  0, 2000, extentMin.y, extentMax.y );
    pos.z = ofMap( location.z,  -1000, 1000, extentMin.z, extentMax.z );
    
    ofVec3f noisePos = pos * frequency;
    
    ofVec3f vel;
    vel.x = ofSignedNoise( noisePos.x, noisePos.y, noisePos.z, noiseTime );
    vel.y = ofSignedNoise( noiseTime,  noisePos.z, noisePos.y, noisePos.x );
    vel.z = ofSignedNoise( noisePos.z, noiseTime,  noisePos.y, noisePos.x );
    
    ofVec3f desired = vel;
    
    desired.normalize();
    desired *= maxspeed;
    ofVec3f steer = desired - velocity;
    steer.limit(maxforce);
    applyForce(steer*0.9);


}

void car::applyForce(ofVec3f force) {
    // We could add mass here if we want A = F / M
    acceleration+=force;
}

// A method that calculates a steering force towards a target
// STEER = DESIRED MINUS VELOCITY


void car::arrive() {
    ofVec3f desired = targetLoc - location;
    float d = desired.length();
    desired.normalize();
    if (d < arriveRadius) {
        //float m = ofMap(d,0,arriveRadius,0,maxspeed);
        //desired *= m;
        life = false;
    } else {
        desired *= maxspeed;
    }
    ofVec3f steer = desired - velocity;
    steer.limit(maxforce);
    applyForce(steer);
}

void car::display() {
    

    ofNoFill();
    
    float theta = velocity.angle(ofVec3f(1,0,0));
    float theta2 = velocity.angle(ofVec3f(0,1,0));
    //ofFill();
    ofPushMatrix();
    ofTranslate(location.x,location.y, location.z);
    ofRotate(-theta, 0, 0, 1);
    //ofRotate(theta2, 0, 0, 0);
    
    ofPushStyle();
    ofSetColor(250,50,50,75);
    ofBeginShape();
    ofVertex(-15, 0);
    ofVertex(20, 0);
    ofEndShape();
    
    ofBeginShape();
    ofVertex(17, 3);
    ofVertex(20, 0);
    ofEndShape();
    
    ofBeginShape();
    ofVertex(17, -3);
    ofVertex(20, 0);
    ofEndShape();
    
    ofBeginShape();
    ofVertex(0, -15);
    ofVertex(0, 15);
    ofEndShape();
    ofPopMatrix();
    ofPopStyle();
    
    ofPushStyle();
    ofNoFill();
    ofSetColor(255, 50);
    ofDrawLine(location.x-200, location.y, location.z, location.x+200, location.y, location.z);
    ofDrawLine(location.x, location.y-200, location.z,location.x, location.y+200, location.z);
    ofPopStyle();
    
    
}
