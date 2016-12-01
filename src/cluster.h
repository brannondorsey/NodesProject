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
    cluster(ofVec3f startTemp, ofVec3f targetTemp, Byte mysNode, Byte mytNode);
    bool update(int maxSpd, int alphaTagetAng);
    void display();
    void setNormals(ofMesh & mesh);
    
    vector<car> cars;
    ofMesh trail;
    
    bool life;
    ofColor col;
    ofVec3f tint;
    ofVec3f start, target, leader;
    Byte ping;
    Byte sNode, tNode;
    
    float frequency;
    float timeFrequency;
    float gridSize;
    
    ofMaterial material;
    

};

#endif /* cluster_h */
