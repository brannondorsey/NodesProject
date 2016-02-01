//
//  car.h
//  nodes01
//
//  Created by Chris Coleman on 12/14/15.
//
//
#ifndef CAR_H
#define CAR_H

#include "ofMain.h"

class car {
public:
    
    car() {}
    car(ofVec3f start, ofVec3f target, int num);
    
    void update(int maxSpd, int alphaTagetAng);
    void wander();
    void applyForce(ofVec3f force);
    void arrive();
    void display();
    bool life;
    ofVec3f location;
    int leadVert;
    ofVec3f velocity;
    
private:
    


    ofVec3f acceleration;
    ofVec3f targetRelative;
    ofVec3f targetLoc;
    
    int high;
    float r;
    float maxforce;
    float maxspeed;
    float arriveRadius;
    
    float targetDistance;
    float targetRadius;
    float alphaTargetAngle;
    float currentTargetAngle;
    int currentVert;
    
    float frequency;
    float timeFrequency;
    float gridSize;
    
    
};

#endif // CAR_H