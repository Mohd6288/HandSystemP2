#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "Particle.h"
#include "SoundManager.h"



// Corrected port numbers
#define RECEIVE_PORT 9129
#define SEND_PORT 8080

enum HandGesture {
    UNKNOWN, OPEN_HAND, CLOSED_HAND, FIST, FLAT_HAND
};

class Hand {
public:
    void setup();
    void update();
    void processHandMessage(const ofxOscMessage& message);
    void draw();
 
    void displayFingerNames();

    void drawBox();

    void drawLanmarks();

    // Declare hasSignificantMovement function
    bool hasSignificantMovement(const vector<glm::vec2>& currentLandmarks, const vector<glm::vec2>& prevLandmarks, float threshold);

    

    
    ofxOscReceiver receiver;
    ofxOscMessage message;
    // ofxOscSender sender; // Uncomment if you're sending messages
    // Method to get the bounding box of the hand
    pair<glm::vec2, glm::vec2> getBoundingBox(const std::vector<glm::vec2>& handLandmarks);

    std::string currentBehaviorDescription;
    std::string fingerData;

    vector<glm::vec2> leftHandLandmarks;
    vector<glm::vec2> rightHandLandmarks;
    
    float animationDuration = 0.5; // Duration of animation in seconds
    std::vector<float> anglesBetweenFingers;
    // Linear interpolation function for smooth transitions


    vector<glm::vec2> prevLeftHandLandmarks;
    vector<glm::vec2> prevRightHandLandmarks;

    glm::vec2 prevLeftHandCentroid, prevRightHandCentroid;
    glm::vec2 leftHandVelocity, rightHandVelocity;
    float lastUpdateTime;  // Time at last update in seconds

    vector<Particle> particles;
    SoundManager soundManger;
    
};


