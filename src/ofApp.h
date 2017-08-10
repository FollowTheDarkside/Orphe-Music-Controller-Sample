#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "SoundManager.h"
#include "OscManager.h"

#define HOST "localhost"
#define PORT_RECEIVER 1234
#define PORT_SENDER 4321

#define DEFAULT_LIGHT_NUM 0

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    /*VISUAL*/
    
    void drawInfo();
    
    void drawSoundCircle();
    float soundCircleRotation;
    ofTrueTypeFont verdana;
    
    void setOrpheRotation(int LorR);
    void drawCone(int LorR);
    
    /*Orphe*/
    float timeStamp;
    
    /*INFO*/
    bool INFO;
    
    ofxPanel gui;
    
    ofxFloatSlider heelElapsedTime;
    ofxToggle isHeelLocked;
    
    ofxToggle isSoundCircle;
    ofxToggle isCone;
    
    ofxToggle toeMode;
    ofxToggle gyroMode;
    ofxToggle gyroDirectMode;
    
    ofxFloatSlider toeUpParam;
    ofxFloatSlider gyroUpParam;
    ofxFloatSlider gyroDirectParam;
    ofxFloatSlider downParam;
    
};
