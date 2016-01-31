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
    void applyForce(ofVec2f force);
    void arrive();
    void display();
    bool life;
    ofVec2f location;
    int leadVert;
    
private:
    

    ofVec2f velocity;
    ofVec2f acceleration;
    ofVec2f targetRelative;
    ofVec2f targetLoc;
    
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
    
};

#endif // CAR_H