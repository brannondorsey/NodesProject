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
    void setNormals(ofMesh & mesh);
    
    vector<car> cars;
    
    
    bool life;

    
    float frequency;
    float timeFrequency;
    float gridSize;
    int traffic;
    
    ofMaterial material;
};

#endif /* cluster_h */
