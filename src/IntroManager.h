#pragma once

#include "ofMain.h"

class IntroManager {
public:
    void setup();
    //void update(float deltaTime);
    void draw();
    void toggleInstructions(); // Method to toggle visibility of instructions
    bool isIntroActive() const;

private:
    ofFbo introFbo;
    std::vector<ofImage> gestureImages;
    std::vector<std::string> instructions;
    ofSoundPlayer voicePlayer; // Sound player for instructions
    bool introActive; // Track whether the intro instructions are active
};
