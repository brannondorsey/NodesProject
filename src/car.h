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
    
    car() {}
    car(ofVec2f start, ofVec2f target);
    
    void update(int maxSpd, int alphaTagetAng);
    void wander(vector<int>* noises);
    void applyForce(ofVec2f force);
    void seek();
    void arrive();
    void display();
    bool life;
    
private:
    
    ofVec2f location;
    ofVec2f velocity;
    ofVec2f acceleration;
    ofVec2f targetRelative;
    ofVec2f targetLoc;
    
    ofMesh trail;
    
    int high;
    float r;
    float maxforce;
    float maxspeed;
    float arriveRadius;
    
    float targetDistance;
    float targetRadius;
    float alphaTargetAngle;
    float currentTargetAngle;
    int age;
    ofColor col;
    
};

#endif // VEHICLE_H_INCLUDED