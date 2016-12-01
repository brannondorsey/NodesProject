#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    //ofSetupOpenGL(1080,1920,OF_WINDOW);
   
	ofGLWindowSettings settings;
	/*
    settings.setGLVersion(3,2);
    ofCreateWindow(settings);
    ofSetWindowShape(1080, 1920);
	*/

	settings.setGLVersion(2, 1); // Fixed pipeline 
	settings.setGLVersion(3, 2); // Programmable pipeline 
	settings.width = 1080; settings.height = 1920; 
	settings.windowMode = OF_FULLSCREEN;
	ofCreateWindow(settings);
	//ofSetWindowShape(1080, 1920);

    //ofSetWindowShape(1920, 1080);
    //ofToggleFullscreen();
			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
