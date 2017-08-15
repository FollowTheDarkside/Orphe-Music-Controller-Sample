#pragma once

#include "ofMain.h"
#define SOUND_NUM 10

class SoundManager{

private:
    
    SoundManager() = default;
    ~SoundManager() = default;
    
public:
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;
    SoundManager(SoundManager&&) = delete;
    SoundManager& operator=(SoundManager&&) = delete;
    
    static SoundManager& getInstance() {
        static SoundManager inst;
        return inst;
    }
    
    void setup();
    void update();
    
    void loadSound();
    void unloadSound();
    void playStopSound();
    void pauseSound();
    void changeSound();
    void changeSoundSpeed(float param);
    
    string soundName[SOUND_NUM];
    ofSoundPlayer soundList[SOUND_NUM];
    int loadedSoundNum;
    int soundPlayingNum;
    
    double sp;
    double pos;
    double posMS;
    bool isPaused;
    float mag;
    float magHSV;
    float magRGB;
};
