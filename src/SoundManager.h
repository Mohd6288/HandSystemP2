#pragma once
#include "ofMain.h"

class SoundManager {
public:
    enum SoundType {
        Normal,
        REPEL,
        SWIRL,
        RIVER,
        START_SOUND,
        PARTICLES_SOUND,
        NUM_SOUNDS // Always last, gives the total number of sounds
    };

    void setup();
    void playSound(SoundType type);
    void stopAllSounds();

private:
    ofSoundPlayer sounds[NUM_SOUNDS];
    string soundFiles[NUM_SOUNDS] = {
        "eleEffecct.wav",
        "repelEffect.wav",
        "Swirl.wav",
        "river.wav",
        "startSound.wav",
        "particlesSound.wav"
    };
};
