//
//  cluster.cpp
//  nodes01
//
//  Created by Chris Coleman on 1/28/16.
//
//

#include "cluster.h"
#include "ofApp.h"

cluster::cluster(ofVec3f startTemp, ofVec3f targetTemp) {
    life = true;
    ping = Byte(ofRandom(4));
    start = startTemp;
    target = targetTemp;
    tint = ofVec3f(ofRandom(.8,1.0),ofRandom(.8,1.0), ofRandom(.8, 1.0));
    int traffic = ofRandom(7, 15);
    for(int i = 1; i<traffic; i++) {
        car tempV = car(start, target, i);
        cars.push_back(tempV);
        trail.addVertex(start);
        trail.addColor(ofColor(255*tint.x, 255*tint.y, 255*tint.z, 20));
        trail.addVertex(start);
        trail.addColor(ofColor(255*tint.x, 255*tint.y, 255*tint.z, 20));
        trail.getNumVertices();
    }
    
    trail.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    tint = ofVec3f(ofRandom(.8,1.0),ofRandom(.8,1.0), ofRandom(.8, 1.0));
    
    frequency = 0.8;
    timeFrequency = .3;
    gridSize = 7.0;
    trail.enableNormals();
    trail.enableColors();

}

bool cluster::update(int maxSpd, int alphaTagetAng) {
    int frame = ofGetFrameNum();
    bool playMe = false;
    for(std::vector<car>::iterator it = cars.begin() ; it != cars.end(); ++it) {
        (*it).wander();
        (*it).arrive();
        (*it).update(maxSpd, alphaTagetAng);
        
        trail.setVertex((*it).leadVert, (*it).location);
        
        if(frame%2==0){
            trail.addVertex((*it).location);
            col = ofColor(ofRandom(100,255),ofRandom(100,255), ofRandom(100,255), 20);
            col = ofColor(col.r*tint.x,col.g*tint.y, col.b*tint.z, col.a*1.0 );
            trail.addColor(col);
            (*it).leadVert = trail.getNumVertices()-1;
        }
        if(trail.getNumVertices()>2500) {
            trail.removeVertex(0);
            trail.removeColor(0);
        }
        
        
        if (!(*it).life) {
            cars.erase(it);
            playMe = true;
            --it;
        }
    }
    if (cars.size()<1) {
        if (trail.getNumVertices()>0) {
            trail.removeVertex(0);
            trail.removeColor(0);
        } else {
            life = false;
        }
        if (trail.getNumVertices()>0) {
            trail.removeVertex(0);
            trail.removeColor(0);
        }
    }
    
    float time = ofGetElapsedTimef();
    float noiseTime = time * timeFrequency;
    
    ofVec3f extentMin( 0, 0, gridSize*-0.5 );
    ofVec3f extentMax( gridSize, gridSize, gridSize *  0.5 );
    
    
    for (int vert = 100; vert < trail.getNumVertices(); vert++) {
        ofVec3f tempVert = trail.getVertex(vert);
        
        ofVec3f pos;
        
        pos.x = ofMap( tempVert.x,  0, 2000, extentMin.x, extentMax.x );
        pos.y = ofMap( tempVert.y,  0, 2000, extentMin.y, extentMax.y );
        pos.z = ofMap( tempVert.z,  -1000, 1000, extentMin.z, extentMax.z );
        
        ofVec3f noisePos = pos * frequency;
        
        ofVec3f vel;
        vel.x = ofSignedNoise( noisePos.x, noisePos.y, noisePos.z, noiseTime )/2;
        vel.y = ofSignedNoise( noiseTime,  noisePos.z, noisePos.y, noisePos.x )/2;
        vel.z = ofSignedNoise( noisePos.z, noiseTime,  noisePos.y, noisePos.x )/2;
        
        tempVert+=vel;
        
        trail.setVertex(vert, tempVert);
    }
    
    setNormals(trail);
    return playMe;
    
}

void cluster::display(){
    
    ofSetColor(255);
    for(std::vector<car>::iterator it = cars.begin() ; it != cars.end(); ++it) {
        (*it).display();
        //carDisplay(*it);
    }
    
    ofSetColor(255);
    //material.begin();
    trail.draw();
    //material.end();
}


//--------------------------------------------------------------
//Universal function which sets normals for the triangle mesh
void cluster::setNormals( ofMesh &mesh ){
    
    //The number of the vertices
    int nV = mesh.getNumVertices();
    
    //The number of the triangles
    int nT = mesh.getNumIndices() / 3;
    
    vector<ofPoint> norm( nV ); //Array for the normals
    
    //Scan all the triangles. For each triangle add its
    //normal to norm's vectors of triangle's vertices
    for (int t=0; t<nT; t++) {
        
        //Get indices of the triangle t
        int i1 = mesh.getIndex( 3 * t );
        int i2 = mesh.getIndex( 3 * t + 1 );
        int i3 = mesh.getIndex( 3 * t + 2 );
        
        //Get vertices of the triangle
        const ofPoint &v1 = mesh.getVertex( i1 );
        const ofPoint &v2 = mesh.getVertex( i2 );
        const ofPoint &v3 = mesh.getVertex( i3 );
        
        //Compute the triangle's normal
        ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();
        
        //Accumulate it to norm array for i1, i2, i3
        norm[ i1 ] += dir;
        norm[ i2 ] += dir;
        norm[ i3 ] += dir;
    }
    
    //Normalize the normal's length
    for (int i=0; i<nV; i++) {
        norm[i].normalize();
    }
    
    //Set the normals to mesh
    mesh.clearNormals();
    mesh.addNormals( norm );
    
}
