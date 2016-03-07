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
    bool update(int maxSpd, int alphaTagetAng);
    void display();
    void setNormals(ofMesh & mesh);
    
    vector<car> cars;
    ofMesh trail;
    
    bool life;
    ofColor col;
    ofVec3f tint;
    
    float frequency;
    float timeFrequency;
    float gridSize;
    
    ofMaterial material;
    

};

#endif /* cluster_h */
