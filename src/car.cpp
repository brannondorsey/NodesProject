//
//  car.cpp
//  nodes01
//
//  Created by Chris Coleman on 12/14/15.
//
//
#include "ofApp.h"
#include "car.h"

car::car(ofVec3f start, ofVec3f target, ofVec3f newTint, int num) {
    acceleration = ofVec3f(0,0, 0);
    float vel = 2.25;
    velocity = ofVec3f(ofRandom(-vel, vel) ,ofRandom(-vel, vel), ofRandom(-vel, vel));
    location = start;
    targetLoc = target;
    tint = newTint;
    r = 2.0;
    targetDistance = r * 10.0;
    targetRadius = r * 4.0;
    alphaTargetAngle = 25.0;        // maximum change in angle each frame (in + and - direction, so max change actually double this)
    targetRelative = ofVec3f(0,0,0);  // similar to 'desired' vector in other examples, position of target relative to vehicle
    maxspeed = 4.0;
    maxforce = ofRandom(.02,.1);
    arriveRadius = 10.0;

    life = true;
    arrived = false;
    high = ofGetHeight();
    leadVert = (num*2)-1;
    wide = 3;
    
    frequency = .7;
    timeFrequency = .7;
    gridSize = 7.0;
    
    col = ofColor(255*tint.x, 255*tint.y, 255*tint.z, 150);
    trail.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    trail.addColor(col);
    trail.addVertex(start);
    trail.enableNormals();
    trail.enableColors();
}

void car::update(int maxSpd, int alphaTagetAng) {
    
    if(!arrived){
        maxspeed = maxSpd;
        alphaTargetAngle = alphaTagetAng;
        velocity += acceleration;
        velocity.limit(maxspeed);
        location += velocity;
        acceleration *= 0;
        if(trail.getNumVertices()>300) {
            trail.removeVertex(0);
            trail.removeColor(0);
        }
    }else{
        minus();
    }

}

void car::add(){
    trail.addVertex(location);
    //trail.addColor(col2);
    //if(wide<10)wide+=ofRandom(-1, 1);
    //trail.addVertex(location-velocity*velocity*wide);
    ofSeedRandom();
    col.r = col.r+ ofRandom(-20,20);
    col.g = col.g + ofRandom(-15,15);
    col.b = col.b + ofRandom(-5,5);
    ofColor col2 = ofColor(col.r*tint.x,col.g*tint.y, col.b*tint.z, col.a*1.0 );
    trail.addColor(col2);

}

void car::minus(){
    if (trail.getNumVertices()>0) {
        trail.removeVertex(0);
        trail.removeColor(0);
    }else{
        life = false;
    }
}

void car::wander() {

    if(!arrived){
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
        applyForce(steer*1);
    }
}

void car::applyForce(ofVec3f force) {
    // We could add mass here if we want A = F / M
    acceleration+=force;
}

// A method that calculates a steering force towards a target
// STEER = DESIRED MINUS VELOCITY


void car::arrive() {
    
    if(!arrived){
        ofVec3f desired = targetLoc - location;
        float d = desired.length();
        desired.normalize();
        if (d < arriveRadius) {
        //float m = ofMap(d,0,arriveRadius,0,maxspeed);
        //desired *= m;
            arrived = true;
        } else {
            desired *= maxspeed;
        }
        ofVec3f steer = desired - velocity;
        steer.limit(maxforce);
        applyForce(steer);
    }
    
    
    float time = ofGetElapsedTimef();
    float noiseTime = time * timeFrequency;
    
    ofVec3f extentMin( 0, 0, gridSize*-0.5 );
    ofVec3f extentMax( gridSize, gridSize, gridSize *  0.5 );
    
    for (int vert = 5; vert < trail.getNumVertices(); vert++) {
        ofVec3f tempVert = trail.getVertex(vert);
        
        ofVec3f pos;
        
        pos.x = ofMap( tempVert.x,  0, 2000, extentMin.x, extentMax.x );
        pos.y = ofMap( tempVert.y,  0, 2000, extentMin.y, extentMax.y );
        pos.z = ofMap( tempVert.z,  -1000, 1000, extentMin.z, extentMax.z );
        
        ofVec3f noisePos = pos * frequency;
        
        ofVec3f vel;
        vel.x = 2*ofSignedNoise( noisePos.x, noisePos.y, noisePos.z, noiseTime )/2;
        vel.y = 2*ofSignedNoise( noiseTime,  noisePos.z, noisePos.y, noisePos.x )/2;
        vel.z = 2*ofSignedNoise( noisePos.z, noiseTime,  noisePos.y, noisePos.x )/2;
        
        tempVert+=vel;
        
        trail.setVertex(vert, tempVert);
    }
}

void car::display() {
    
    ofSetColor(255);
    trail.draw();
    
    if(!arrived){
    ofNoFill();
    
    float theta = velocity.angle(ofVec3f(1,0,0));
    float theta2 = velocity.angle(ofVec3f(0,1,0));
    //ofFill();
    ofPushMatrix();
    ofTranslate(location.x,location.y, location.z);
    ofRotate(-theta*3, 0, 0, 1);
    ofRotate(theta2*10, 0, 1, 0);
    
    ofPushStyle();
    ofSetColor(250,57,67,120);
    //ofBeginShape();
        ofSetSphereResolution(3);
        ofDrawSphere(ofSignedNoise(location.z/10)*30);

    //ofEndShape();
    ofPopMatrix();
    ofPopStyle();
    
    ofPushStyle();
    ofNoFill();
    ofSetColor(193,222, 232, 50);
    ofDrawLine(location.x-100, location.y, location.z, location.x+100, location.y, location.z);
    ofDrawLine(location.x, location.y-100, location.z,location.x, location.y+100, location.z);
    ofPopStyle();
    }
    
    
}