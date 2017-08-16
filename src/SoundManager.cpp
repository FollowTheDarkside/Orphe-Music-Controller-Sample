#include "SoundManager.h"

#include <sys/types.h>
#include <dirent.h>

//--------------------------------------------------------------
void SoundManager::setup(){
    loadSound();
    sp = 1;
    pos = 0;
    posMS = 0;
    isPaused = false;
}

//--------------------------------------------------------------
void SoundManager::update(){
    
    //get sound volume
    float * val = ofSoundGetSpectrum(1);
    mag=ofMap(val[0]*10, 0, 1, 0, 1,true);
    magHSV=ofMap(val[0]*10, 0, 1, 240, 359,true);
    magRGB=ofMap(val[0]*10, 0, 1, 0, 255,true);
    
    //adjust sound speed
    if(sp<0){
        sp=0;
    }else if(sp>1){
        sp=1;
    }
    
    soundList[soundPlayingNum].setSpeed(sp);
    pos = soundList[soundPlayingNum].getPosition();
    posMS = soundList[soundPlayingNum].getPositionMS();
}

//--------------------------------------------------------------
void SoundManager::loadSound(){
    loadedSoundNum=0;
    
    string folderName = "music/";
    ofDirectory dir(folderName);
    dir.listDir();
    dir.allowExt("mp3");
    dir.allowExt("wav");
    for(int i = 0; i < dir.size(); i++){
        cout << dir.getName(i) << endl;
        soundName[i] = dir.getName(i);
        string musicPass = "music/";
        musicPass += soundName[i];
        soundList[i].load(musicPass, true);
        
        //Delete character string after "."
        soundName[i].erase(soundName[i].find("."), 4);
        
        if(soundList[i].isLoaded()){
            loadedSoundNum++;
        }
    }
}

//--------------------------------------------------------------
void SoundManager::unloadSound(){
    for (int i=0; i<SOUND_NUM; i++) {
        if(soundList[i].isLoaded()){
            soundList[i].stop();
            soundList[i].unload();
        }
    }
    loadedSoundNum=0;
}

//--------------------------------------------------------------
void SoundManager::playStopSound(){

    if(!soundList[soundPlayingNum].isPlaying()){
        if(soundList[soundPlayingNum].isLoaded()){
            soundList[soundPlayingNum].play();
        }
    }else if(isPaused){
        if(soundList[soundPlayingNum].isLoaded()){
            soundList[soundPlayingNum].setPaused(false);
            isPaused = false;
        }
    }else{
        if(soundList[soundPlayingNum].isLoaded()){
            soundList[soundPlayingNum].stop();
        }
    }
}

//--------------------------------------------------------------
void SoundManager::pauseSound(){
    
    if(soundList[soundPlayingNum].isPlaying() && !isPaused){
        if(soundList[soundPlayingNum].isLoaded()){
            soundList[soundPlayingNum].setPaused(true);
            isPaused = true;
        }
    }else if (isPaused){
        if(soundList[soundPlayingNum].isLoaded()){
            soundList[soundPlayingNum].setPaused(false);
            isPaused = false;
        }
    }
}

//--------------------------------------------------------------
void SoundManager::changeSound(){
    
    if(soundList[soundPlayingNum].isLoaded()){
        soundList[soundPlayingNum].setPaused(false);
        soundList[soundPlayingNum].stop();
    }
    
    if(soundPlayingNum>=loadedSoundNum-1){
        soundPlayingNum=0;
    }else{
        soundPlayingNum++;
    }
    
    if(soundList[soundPlayingNum].isLoaded()){
        soundList[soundPlayingNum].play();
        isPaused = false;
    }
}

//--------------------------------------------------------------
void SoundManager::changeSoundSpeed(float param){
    sp+=param;
}

