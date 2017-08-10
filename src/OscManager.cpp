#include "OscManager.h"

//--------------------------------------------------------------
void OscManager::setup(string host, int portReceiver,  int portSender){
    
    receiver.setup(portReceiver);
    sender.setup(host, portSender);
    
}

//--------------------------------------------------------------
void OscManager::update(){
    
    isToeGesture=false;
    
    while(receiver.hasWaitingMessages()){
        
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        if(m.getAddress() == "/LEFT/sensorValues"){
            
            getOrpheSensorValues(0, m);
            
        }else if (m.getAddress() == "/RIGHT/sensorValues"){
            
            getOrpheSensorValues(1, m);
            
        }else if(m.getAddress() == "/LEFT/gesture" && m.getArgAsString(1) == "HEEL"){
            
            heelGestureCounter(0);
            
        }else if(m.getAddress() == "/RIGHT/gesture" && m.getArgAsString(1) == "HEEL"){
            
            heelGestureCounter(1);
            
        }else if(m.getArgAsString(1) == "TOE"){
            
            isToeGesture=true;
            
        }
    }
    
    //reset heel count
    for (int i=0; i<2; i++) {
        for (int j=0; j<3; j++) {
            if(heelCount[i]==(j+1) && (ofGetElapsedTimef()-heelTime[i][j]) > heelElapsedTime){
                heelCountReseter(i);
            }
        }
    }
}

//--------------------------------------------------------------
void OscManager::getOrpheSensorValues(int LorR, ofxOscMessage m){
    
    quatW[LorR] = m.getArgAsFloat(0);
    quatX[LorR] = m.getArgAsFloat(1);
    quatY[LorR] = m.getArgAsFloat(2);
    quatZ[LorR] = m.getArgAsFloat(3);
    
    eulerX[LorR] = m.getArgAsFloat(4);
    eulerY[LorR] = m.getArgAsFloat(5);
    eulerZ[LorR] = m.getArgAsFloat(6);
    
    accX[LorR] = m.getArgAsFloat(7);
    accY[LorR] = m.getArgAsFloat(8);
    accZ[LorR] = m.getArgAsFloat(9);
    
    gyroX[LorR] = m.getArgAsFloat(10);
    gyroY[LorR] = m.getArgAsFloat(11);
    gyroZ[LorR] = m.getArgAsFloat(12);
    
    orientation[LorR] = m.getArgAsInt(13);
    
    impact[LorR] = m.getArgAsInt(14);
}

//--------------------------------------------------------------
void OscManager::heelGestureCounter(int LorR){
    if(heelTF[LorR][0]==false){
        
        heelTF[LorR][0]=true;
        heelCount[LorR]++;
        heelTime[LorR][0] = ofGetElapsedTimef();
        
    }else if(heelTF[LorR][0]==true && heelTF[LorR][1]==false && (ofGetElapsedTimef()-heelTime[LorR][0])<heelElapsedTime){
        
        heelTF[LorR][1]=true;
        heelTime[LorR][1] = ofGetElapsedTimef();
        heelCount[LorR]++;
        
    }else if(heelTF[LorR][0]==true && heelTF[LorR][1]==true && (ofGetElapsedTimef()-heelTime[LorR][1])<heelElapsedTime){
        
        heelTF[LorR][2]=true;
        heelTime[LorR][2] = ofGetElapsedTimef();
        heelCount[LorR]++;
        
    }else{
        
        heelCountReseter(LorR);
        
    }
}

//--------------------------------------------------------------
void OscManager::heelCountReseter(int LorR){
    for (int i=0; i<3; i++) {
        heelTF[LorR][i]=false;
        heelTime[LorR][i]=0;
    }
    heelCount[LorR]=0;
}

//--------------------------------------------------------------
void OscManager::triggerLightWithRGBColor(int LorRorBOTH, int lightNum, int r, int g, int b){
    ofxOscMessage m;
    
    if(LorRorBOTH==0){
        m.setAddress("/LEFT/triggerLightWithRGBColor");
    }else if(LorRorBOTH==1){
        m.setAddress("/RIGHT/triggerLightWithRGBColor");
    }else if(LorRorBOTH==2){
        m.setAddress("/BOTH/triggerLightWithRGBColor");
    }
    //light pattern
    m.addIntArg(lightNum);
    //light color
    m.addIntArg(r);
    m.addIntArg(g);
    m.addIntArg(b);
    
    sender.sendMessage(m);
}

//--------------------------------------------------------------
void OscManager::setHSVColor(int LorRorBOTH,int lightNum, int h, int s, int b){
    ofxOscMessage m;
    
    if(LorRorBOTH==0){
        m.setAddress("/LEFT/setHSVColor");
    }else if(LorRorBOTH==1){
        m.setAddress("/RIGHT/setHSVColor");
    }else if(LorRorBOTH==2){
        m.setAddress("/BOTH/setHSVColor");
    }
    //light pattern
    m.addIntArg(lightNum);
    //light color
    m.addIntArg(h);
    m.addIntArg(s);
    m.addIntArg(b);
    
    sender.sendMessage(m);
}

//--------------------------------------------------------------
void OscManager::setLightOn(int LorRorBOTH,int lightNum){
    ofxOscMessage m;
    
    m.setAddress("/BOTH/setLightOn");
    m.addIntArg(lightNum);
    
    sender.sendMessage(m);
}

//--------------------------------------------------------------
void OscManager::setLightOff(int LorRorBOTH,int lightNum){
    ofxOscMessage m;
    
    m.setAddress("/BOTH/setLightOff");
    m.addIntArg(lightNum);
    
    sender.sendMessage(m);
}


