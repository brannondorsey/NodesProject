//
//  car.cpp
//  nodes01
//
//  Created by Chris Coleman on 12/14/15.
//
//
#include "ofApp.h"
#include "car.h"

car::car(ofVec2f start, ofVec2f target) {
    acceleration = ofVec2f(0,0);
    velocity = ofVec2f(ofRandom(-2, 2) ,ofRandom(-2, 2));
    location = start;
    targetLoc = target;
    r = 2.0;
    targetDistance = r * 10.0;
    targetRadius = r * 4.0;
    currentTargetAngle = ofRandom(360);        // current angle we're heading towards, calculated each frame
    alphaTargetAngle = 25.0;        // maximum change in angle each frame (in + and - direction, so max change actually double this)
    targetRelative = ofVec2f(0,0);  // similar to 'desired' vector in other examples, position of target relative to vehicle
    maxspeed = 4.0;
    maxforce = ofRandom(.02,.1);
    arriveRadius = 10.0;
    col = ofColor(ofRandom(220,250),ofRandom(180,250), ofRandom(180,250));
    life = true;
}

void car::update(int maxSpd, int alphaTagetAng) {
    maxspeed = maxSpd;
    alphaTargetAngle = alphaTagetAng;
    velocity += acceleration;
    velocity.limit(maxspeed);
    location += velocity;
    acceleration *= 0;
    
    history.push_back(location);
    if (history.size() > 200) {
        history.erase(history.begin());
    }
}

void car::wander() {
    // These two lines introduce a slight modification to Daniel Shiffman's example, to alter the radius and
    // distance of the target zone depending on mouse position
    float dist = ofDist(location.x, location.y, targetLoc.x, targetLoc.y);
    targetDistance = ofMap(dist,0,ofGetWidth(),0,30); //vary distance of target wander steering with distance to target
    targetRadius = ofMap(dist,0,ofGetWidth(),100,5);
    
    float angleAdjust = ofRandom(-alphaTargetAngle, alphaTargetAngle); //random new agle change
    currentTargetAngle += angleAdjust; //added to old angle
    
    float xTarget = targetRadius * cos(ofDegToRad(currentTargetAngle));
    float yTarget = targetRadius * sin(ofDegToRad(currentTargetAngle)); //get our wander vector
    
    ofVec2f offset = velocity;
    offset.normalize();
    offset*=targetDistance;
    
    targetRelative = ofVec2f(xTarget,yTarget)+ offset;
    //targetRelative = ofVec2f(xTarget,yTarget);
    
    ofVec2f desired = targetRelative;
    
    desired.normalize();
    desired *= maxspeed;
    ofVec2f steer = desired - velocity;
    steer.limit(maxforce);
    applyForce(steer*1.1);
    
//    if(location.x < 0 ) {
//        location.x = ofGetWidth();
//    } else if(location.x > ofGetWidth() ) {
//        location.x = 0;
//    }
//    if(location.y < 0 ) {
//        location.y = ofGetHeight();
//    } else if(location.y > ofGetHeight() ) {
//        location.y = 0;
//    }
}

void car::applyForce(ofVec2f force) {
    // We could add mass here if we want A = F / M
    acceleration+=force;
}

// A method that calculates a steering force towards a target
// STEER = DESIRED MINUS VELOCITY
void car::seek() {
    ofVec2f desired = targetLoc - location;
    desired.normalize();
    desired *= maxspeed;
    ofVec2f steer = desired - velocity;
    steer.limit(maxforce);
    applyForce(steer);
}

// A method that calculates a steering force towards a target
// STEER = DESIRED MINUS VELOCITY
void car::arrive() {
    ofVec2f desired = targetLoc - location;
    float d = desired.length();
    desired.normalize();
    if (d < arriveRadius) {
        //float m = ofMap(d,0,arriveRadius,0,maxspeed);
        //desired *= m;
        life = false;
    } else {
        desired *= maxspeed;
    }
    ofVec2f steer = desired - velocity;
    steer.limit(maxforce);
    applyForce(steer);
}

void car::display() {
    ofBeginShape();
    ofSetColor(col, 75);
    //strokeWeight(1);
    ofNoFill();

    for(ofVec2f v: history) {
        ofVertex(v.x,v.y);
    }
    ofEndShape();
    
    float theta = velocity.angle(ofVec2f(0,1));
    ofFill();
    ofPushMatrix();
    ofTranslate(location.x,location.y);
    ofRotate(-theta);
    
    ofSetColor(80,80,80,175);
    ofBeginShape();
    ofVertex(0, r*2);
    ofVertex(-r, -r*2);
    ofVertex(r, -r*2);
    ofEndShape();
    
//    ofLine(0.0, 0.0, 0.0, targetDistance);
//    ofSetCircleResolution(50);
//    ofSetColor(0,0,0,75);
//    ofCircle(0.0, targetDistance, targetRadius);
//    
//    ofSetColor(0,0,0,200);
//    ofCircle(targetRelative.x, targetRelative.y, 10);
    
    ofPopMatrix();
    
    
}