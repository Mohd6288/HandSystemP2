#include "IntroManager.h"

void IntroManager::setup() {
    introFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    introFbo.begin();
    ofClear(255, 255, 255, 0);
    introFbo.end();

    // Load gesture images
    gestureImages.push_back(ofImage("open_hand.png"));
    gestureImages.push_back(ofImage("closed_hand.png"));
    gestureImages.push_back(ofImage("fist.png"));
    gestureImages.push_back(ofImage("flat_hand.png"));

    // Set instructions
    instructions.push_back("Open Hand: Reset the system.");
    instructions.push_back("Closed Hand: Attracts particles.");
    instructions.push_back("Fist: Repels particles.");
    instructions.push_back("Flat Hand: Causes particles to swirl.");

    // Load and configure sound player
    voicePlayer.load("aiVoice.wav");
    voicePlayer.setMultiPlay(false);
    voicePlayer.setLoop(false);

    introActive = true; // Start with instructions visible
    if (introActive) {
        voicePlayer.play(); // Start playback only if intro is active
    }
}

void IntroManager::toggleInstructions() {
    introActive = !introActive; // Toggle the visibility of instructions

    // Control sound playback based on intro visibility
    if (introActive) {
        voicePlayer.play();
    }
    else {
        voicePlayer.stop();
    }
}

void IntroManager::draw() {
    if (!introActive) return;

    introFbo.begin();
    ofClear(255, 255, 255, 0); // Clear the FBO to avoid drawing leftovers

    int numImages = gestureImages.size();
    float imageWidth = ofGetWidth() / numImages; // Divide window width by number of images
    float imageHeight = gestureImages[0].getHeight() * (imageWidth / gestureImages[0].getWidth()); // Maintain aspect ratio

    for (int i = 0; i < numImages; i++) {
        float x = i * imageWidth; // Position each image next to the previous
        float y = 0; // Start at the top of the window

        gestureImages[i].draw(x, y, imageWidth, imageHeight); // Draw each image resized

        // Draw the instruction text below each image
        std::string instructionText = instructions[i];
        ofDrawBitmapStringHighlight(instructionText, x + 5, y + imageHeight + 20, ofColor::black, ofColor::white);
    }

    // Add a text prompt for starting or toggling the intro
    std::string startPrompt = "Press 'S' to start or toggle instructions";
    ofDrawBitmapStringHighlight(startPrompt, (ofGetWidth() - 400) / 2, ofGetHeight() - 40, ofColor::yellow, ofColor::gray);

    introFbo.end();
    introFbo.draw(0, 0); // Draw the FBO content to the main window
}



bool IntroManager::isIntroActive() const {
    return introActive; // Return the state of the introActive variable
}

