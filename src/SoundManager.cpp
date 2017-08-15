#include "SoundManager.h"

#include <sys/types.h>
#include <dirent.h>

//--------------------------------------------------------------
void SoundManager::setup(){
    loadSound();
    sp=1;
    isPaused=false;
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
}

//--------------------------------------------------------------
void SoundManager::loadSound(){
    loadedSoundNum=0;
    
    //get sound file name and load sound file
    DIR* dp=opendir("../../../data/music");
    if (dp!=NULL)
    {
        struct dirent* dent;
        do{
            dent = readdir(dp);
            if (dent!=NULL){
                cout<<dent->d_name<<endl;
                soundName[loadedSoundNum]=dent->d_name;
                
                if(soundName[loadedSoundNum].front() != '.'){
                    string musicPass = "music/";
                    musicPass += soundName[loadedSoundNum];
                    soundList[loadedSoundNum].load(musicPass, true);
                    if(soundList[loadedSoundNum].isLoaded()){
                        //Delete character string after "."
                        size_t c;
                        while((c = soundName[loadedSoundNum].find_first_of(".")) != string::npos){
                            soundName[loadedSoundNum].erase(c,5);
                        }
                        loadedSoundNum++;
                    }
                }
                
                
            }
        }while(dent!=NULL);
        closedir(dp);
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
        soundList[soundPlayingNum].stop();
    }
    
    if(soundPlayingNum>=loadedSoundNum-1){
        soundPlayingNum=0;
    }else{
        soundPlayingNum++;
    }
    
    if(soundList[soundPlayingNum].isLoaded()){
        soundList[soundPlayingNum].play();
    }
}

//--------------------------------------------------------------
void SoundManager::changeSoundSpeed(float param){
    sp+=param;
}

