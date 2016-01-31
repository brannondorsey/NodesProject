//
//  cluster.h
//  nodes01
//
//  Created by Chris Coleman on 1/28/16.
//
//

#ifndef cluster_h
#define cluster_h

#include "ofMain.h"
#include "car.h"

class cluster {
public:
    
    cluster() {}
    cluster(ofVec3f start, ofVec3f target);
    void update(int maxSpd, int alphaTagetAng);
    void display();
    
    vector<car> cars;
    ofMesh trail;
    bool life;
    ofColor col;
    
    
};

#endif /* cluster_h */
