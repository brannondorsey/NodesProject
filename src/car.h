//
//  car.hpp
//  nodes01
//
//  Created by Chris Coleman on 12/14/15.
//
//
#ifndef VEHICLE_H_INCLUDED
#define VEHICLE_H_INCLUDED

#include "ofMain.h"

class car {
public:
    
    vector<ofVec2f> history;
    
    car() {}
    car(float x, float y);
    
    void update();
    void wander(ofVec2f mousePos);
    void applyForce(ofVec2f force);
    void seek(ofVec2f target);
    void arrive(ofVec2f target);
    void display();
    
private:
    
    ofVec2f location;
    ofVec2f velocity;
    ofVec2f acceleration;
    ofVec2f targetRelative;
    
    float r;
    float maxforce;
    float maxspeed;
    float arriveRadius;
    
    float targetDistance;
    float targetRadius;
    float alphaTargetAngle;
    float currentTargetAngle;
    ofColor col;
    
};

#endif // VEHICLE_H_INCLUDED