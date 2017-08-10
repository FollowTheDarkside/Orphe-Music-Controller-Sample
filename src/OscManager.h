#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class ofApp;

class OscManager {
private:
    OscManager() = default;
    ~OscManager() = default;
    
public:
    OscManager(const OscManager&) = delete;
    OscManager& operator=(const OscManager&) = delete;
    OscManager(OscManager&&) = delete;
    OscManager& operator=(OscManager&&) = delete;
    
    static OscManager& getInstance() {
        static OscManager inst;
        return inst;
    }
    
    void setup(string host, int portReceiver, int portSender);
    void update();
    void getOrpheSensorValues(int LorR, ofxOscMessage m);
    void heelGestureCounter(int LorR);
    void heelCountReseter(int LorR);
    
    void triggerLightWithRGBColor(int LorRorBOTH,int lightNum, int r, int g, int b);
    void setHSVColor(int LorRorBOTH,int lightNum, int h, int s, int b);
    void setLightOn(int LorRorBOTH,int lightNum);
    void setLightOff(int LorRorBOTH,int lightNum);
    
    ofxOscReceiver receiver;
    ofxOscSender sender;
    
    bool isToeGesture;
    
    //OrpheSensorValues
    float quatW[2];
    float quatX[2];
    float quatY[2];
    float quatZ[2];
    
    float eulerX[2];
    float eulerY[2];
    float eulerZ[2];
    
    float accX[2];
    float accY[2];
    float accZ[2];
    
    float gyroX[2];
    float gyroY[2];
    float gyroZ[2];
    
    int orientation[2];
    
    int impact[2];
    
    float power[2];
    
    //for heel count
    float heelTime[2][3];
    bool heelTF[2][3];
    int heelCount[2];
    float heelElapsedTime;
    
};
