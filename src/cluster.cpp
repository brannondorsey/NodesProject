//
//  cluster.cpp
//  nodes01
//
//  Created by Chris Coleman on 1/28/16.
//
//

#include "cluster.h"
#include "ofApp.h"

cluster::cluster(ofVec3f start, ofVec3f target) {
    life = true;

    traffic = ofRandom(1, 10);
    ofVec3f clusTint = ofVec3f(ofRandom(0.7,0.8),ofRandom(.4,.6), ofRandom(.2, .4));
    for(int i = 1; i<traffic; i++) {
        car tempV = car(start, target, clusTint, i);
        cars.push_back(tempV);
    }
    
    frequency = 0.8;
    timeFrequency = .3;
    gridSize = 7.0;
    
    //glEnable(GL_POINT_SMOOTH); // use circular points instead of square points
    //glPointSize(3); // make the points bigger

}

void cluster::update(int maxSpd, int alphaTagetAng) {
    int frame = ofGetFrameNum();
    
    for(std::vector<car>::iterator it = cars.begin() ; it != cars.end(); ++it) {
        (*it).wander();
        (*it).arrive();
        (*it).update(maxSpd, alphaTagetAng);
        
        
        if(frame%10==0){
            (*it).add();
         }
        if (!(*it).life) {
            cars.erase(it);
            --it;
        }
    }
    
    if (cars.size()<1) {
            life = false;
    }
    //setNormals(trail);
    
}

void cluster::display(){
    
    ofSetColor(255);
    for(std::vector<car>::iterator it = cars.begin() ; it != cars.end(); ++it) {
        (*it).display();
    }
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
