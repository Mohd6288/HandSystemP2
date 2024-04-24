#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "Hand.h"
#include "ofxGui.h"
#include "Particle.h"
#include "SoundManager.h"

// Corrected port numbers
#define RECEIVE_PORT 9129
#define SEND_PORT 8080

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
   

    Hand hand;
   
    ofxOscMessage message;

    Particle::Behavior currentBehavior; // Current behavior
    vector<Particle> particles;

  
    //SoundManager soundManager;
   
};
