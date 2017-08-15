#include "ofApp.h"

SoundManager &soundManager = SoundManager::getInstance();
OscManager &oscManager = OscManager::getInstance();

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetBackgroundAuto(true);
    ofBackground(255);
    ofEnableSmoothing();
    ofSetCircleResolution(64);
    
    soundManager.setup();
    oscManager.setup(HOST, PORT_RECEIVER, PORT_SENDER);
    
    timeStamp=0;
    
    soundCircleRotation=0;
    
    yeseva.load("font/YesevaOne-Regular.ttf", 10);
    
    INFO = true;
    
    //GUI
    gui.setup();
    gui.add(isSoundCircle.setup("soundCircle", true));
    gui.add(isCone.setup("cone", false));
    
    gui.add(heelElapsedTime.setup("heelElapsedTime", 1, 0, 5));
    gui.add(isHeelLocked.setup("heelLock", false));
    gui.add(toeMode.setup("toeMode", true));
    gui.add(gyroMode.setup("gyroMode", false));
    gui.add(gyroDirectMode.setup("gyroDirectMode", false));
    gui.add(toeUpParam.setup("toeUpParam", 0.1, 0, 1));
    gui.add(gyroUpParam.setup("gyroUpParam", 0.005, 0, 0.01));
    gui.add(gyroDirectParam.setup("gyroDirectParam", 7, 0, 10));
    gui.add(downParam.setup("downParam", 0.001, 0, 0.01));
    
    gui.setPosition(ofGetWidth()-200, 0);
    gui.setName("OMC GUI");
}

//--------------------------------------------------------------
void ofApp::update(){
    
    oscManager.update();
    oscManager.heelElapsedTime = heelElapsedTime;
    
    //toe -> sound speed
    if (toeMode) {
        if(oscManager.isToeGesture){
            soundManager.changeSoundSpeed(toeUpParam);
        }
    }
    
    //gyro -> sound speed
    if (gyroMode) {
        for(int i=0;i<2;i++){
            soundManager.changeSoundSpeed(fabs(oscManager.gyroX[i])*gyroUpParam);
            soundManager.changeSoundSpeed(fabs(oscManager.gyroY[i])*gyroUpParam);
            soundManager.changeSoundSpeed(fabs(oscManager.gyroZ[i])*gyroUpParam);
        }
    }
    
    //adjust sound speed
    soundManager.changeSoundSpeed(-downParam);
    
    //gyro -> sound speed
    if(gyroDirectMode){
        soundManager.sp=gyroDirectParam*(fabs(oscManager.gyroX[0])+fabs(oscManager.gyroY[0])+fabs(oscManager.gyroZ[0])+fabs(oscManager.gyroX[1])+fabs(oscManager.gyroY[1])+fabs(oscManager.gyroZ[1]));
        toeMode=false;
        gyroMode=false;
    }
    
    //sound end
    if(soundManager.pos >= 0.99){
        oscManager.triggerLightWithRGBColor(2, 2, 255, 255, 255);
        soundManager.changeSound();
    }
    
    soundManager.update();
    
    //heel 3 times
    if(!isHeelLocked){
        if(oscManager.heelCount[0]>=3){ //left
            
            if (soundManager.soundList[soundManager.soundPlayingNum].isPlaying()) {
                oscManager.setLightOff(2, DEFAULT_LIGHT_NUM);
            }else{
                oscManager.setLightOn(2, DEFAULT_LIGHT_NUM);
            }
            soundManager.playStopSound();
            oscManager.heelCount[0]=0;
            oscManager.triggerLightWithRGBColor(2, 2, 255, 255, 255);
            
        }else if(oscManager.heelCount[1]>=3){ //right
            
            soundManager.changeSound();
            oscManager.heelCount[1]=0;
            oscManager.triggerLightWithRGBColor(2, 2, 255, 255, 255);
            
        }
    }
    
    //sound volume -> light color
    float elapsedTime = ofGetElapsedTimef() - timeStamp;
    if (elapsedTime > 0.03) {
        oscManager.setHSVColor(2, DEFAULT_LIGHT_NUM, soundManager.magHSV, 255, 122);
        timeStamp = ofGetElapsedTimef();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(isSoundCircle){
        drawSoundCircle();
    }
    
    if(isCone){
        drawCone(0);
        drawCone(1);
    }
    
    if(INFO){
        drawInfo();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f': //fullscreen
            ofToggleFullscreen();
            gui.setPosition(ofGetWidth()-200, 0);
            break;
        case 'l': //sound load & unload
            if(soundManager.soundList[0].isLoaded()){
                soundManager.unloadSound();
            }else{
                soundManager.loadSound();
            }
            break;
        case 's': //sound play & stop
            if (soundManager.soundList[soundManager.soundPlayingNum].isPlaying()) {
                oscManager.setLightOff(2, DEFAULT_LIGHT_NUM);
            }else{
                oscManager.setLightOn(2, DEFAULT_LIGHT_NUM);
            }
            soundManager.playStopSound();
            oscManager.triggerLightWithRGBColor(2, 2, 255, 255, 255);
            break;
        case 'p': //sound pause
            soundManager.pauseSound();
            oscManager.triggerLightWithRGBColor(2, 2, 255, 255, 255);
            break;
        case 'n': //change sound
            soundManager.changeSound();
            break;
        case 'i': //draw info
            if(INFO){
                INFO=false;
                ofHideCursor();
            }else{
                INFO=true;
                ofShowCursor();
            }
            break;
        case 27: //esc key
            soundManager.unloadSound();
            oscManager.setLightOff(2, DEFAULT_LIGHT_NUM);
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

//--------------------------------------------------------------
void ofApp::drawInfo(){
    ofSetColor(0, 0, 0);
    string info;
    
    info+="-------------INFO-------------\n";
    //info+="eulerX = " + ofToString(oscManager.eulerX[0]) + "\n";
    //info+="eulerY = " + ofToString(oscManager.eulerY[0]) + "\n";
    //info+="eulerZ = " + ofToString(oscManager.eulerZ[0]) + "\n";
    info+="heel left count  = " + ofToString(oscManager.heelCount[0]) + "\n";
    info+="heel right count = " + ofToString(oscManager.heelCount[1]) + "\n";
    info+="volume = " + ofToString(soundManager.mag) + "\n";
    //info+="volume for HSV = " + ofToString(soundManager.magHSV) + "\n";
    info+="speed = " + ofToString(soundManager.sp) + "\n";
    info+="position = " + ofToString(soundManager.pos) + "\n";
    info+="loaded sound num = " + ofToString(soundManager.loadedSoundNum) + "\n";
    //info+="sound num = " + ofToString(soundManager.soundPlayingNum) + "\n";
    info+="-----------PLAYLIST-----------\n";
    for(int i=0; i<soundManager.loadedSoundNum; i++){
        if(soundManager.soundList[i].isLoaded()){
            info+=soundManager.soundName[i];
            if(soundManager.soundList[i].isPlaying()){
                info+=" : Now Playing!";
            }
            info+="\n";
        }
    }
    info+="------------------------------\n";
    ofDrawBitmapString(info,0,10);
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::drawSoundCircle(){
    ofPushMatrix();
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    if(!soundManager.soundList[soundManager.soundPlayingNum].isPlaying()){
        soundCircleRotation = 0;
    }else{
        soundCircleRotation = soundManager.posMS*0.5;
    }
    ofRotateZ(soundCircleRotation);
    
    ofFill();
    
    ofSetColor(0, 0, 0);
    ofDrawCircle(0, 0, ofGetHeight()/5);
    
    ofSetColor(255, 0, 0);
    ofDrawCircle(0, 0, ofGetHeight()/15);
    
    ofSetColor(255, 255, 255);
    ofDrawCircle(0, 0, ofGetHeight()/60);
    ofNoFill();
    
    ofSetColor(0, 0, 0);
    yeseva.drawString("Orphe", -20, 30);
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::setOrpheRotation(int LorR){
    
    ofQuaternion new_q;
    new_q.w() = oscManager.quatW[LorR];
    new_q.x() = oscManager.quatY[LorR];
    new_q.y() = oscManager.quatZ[LorR];
    new_q.z() = oscManager.quatX[LorR];
    
    ofVec3f qAxsis;
    float   angle;
    new_q.getRotate(angle, qAxsis);
    
    ofRotate(angle, qAxsis.x, qAxsis.y, qAxsis.z);
    ofRotateZ(180);
    
}

//--------------------------------------------------------------
void ofApp::drawCone(int LorR){
    ofPushMatrix();
    
    ofSetColor(0, 0, 0);
    
    if(LorR==0){
        ofTranslate(ofGetWidth()/2-200, ofGetHeight()/2);
    }else{
        ofTranslate(ofGetWidth()/2+200, ofGetHeight()/2);
    }
    
    setOrpheRotation(LorR);
    ofRotateX(90);
    
    ofConePrimitive cone;
    cone.set(50, 400);
    cone.setPosition(0, 0, 0);
    cone.drawWireframe();
    
    ofPopMatrix();
}


