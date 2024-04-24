#include "SoundManager.h"

void SoundManager::setup() {
    for (int i = 0; i < NUM_SOUNDS; i++) {
        if (!sounds[i].load(soundFiles[i])) {
            ofLogError("Sound Load") << "Failed to load " << soundFiles[i];
        }
        sounds[i].setMultiPlay(true);
    }
}

void SoundManager::playSound(SoundType type) {
    for (int i = 0; i < NUM_SOUNDS; i++) {
        if (i != type) {
            sounds[i].stop();
        }
    }
    if (!sounds[type].isPlaying()) {
        sounds[type].play();
    }
}

void SoundManager::stopAllSounds() {
    for (int i = 0; i < NUM_SOUNDS; i++) {
        sounds[i].stop();
    }
}
