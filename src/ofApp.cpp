#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    //std::string c = "node .\\MediaPipe-Hands-OSC-main\\MediaPipe-Hands-OSC-main\\bridge.js";
    //ofSystem(c.c_str());
    //https://monlim.github.io/MediaPipe-Hands-OSC/

    //--------------Start tracking but you need to run the bride.js from coomand line------------------//
    std::string explorer = "explorer \"https://monlim.github.io/MediaPipe-Hands-OSC/\"";
    ofSystem(explorer.c_str());

    //----------------------------Hand And particle SYSTEM----------------------------------//
    ofSetFrameRate(45);
    ofSetBackgroundColor(0, 0, 0);
    hand.setup();
    //soundManager.setup();
    
}

//--------------------------------------------------------------
void ofApp::update() {
   
    hand.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    //screen frame rate
    hand.draw();
}

void ofApp::keyPressed(int key) {
    /*
    switch (key) {
    case '1':
        soundManager.playSound(SoundManager::RAINY);
        break;
    case '2':
        soundManager.playSound(SoundManager::BEAT);
        break;
    case '3':
        soundManager.playSound(SoundManager::GUITAR);
        break;
    case '4':
        soundManager.playSound(SoundManager::RIVER);
        break;
    case '5':
        soundManager.playSound(SoundManager::START_SOUND);
        break;
    default:
        soundManager.playSound(SoundManager::PARTICLES_SOUND);
        break;
    }
    */
}


//--------------------------------------------------------------

