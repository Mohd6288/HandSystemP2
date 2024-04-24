// Particle.h
#pragma once

#include "ofMain.h"

class Particle {
public:
    enum Behavior { NORMAL, BOUNCE, SWIRL, OTHER, ATTRACT, REPEL };
    enum BlendMode { DEFAULT, ADD, SUBTRACT, SCREEN };
    Behavior behavior; // Behavior attribute
    BlendMode blendMode;

    void setBehavior(Behavior newBehavior){//,BlendMode newBlendMode) {
        behavior = newBehavior;
        //blendMode = newBlendMode;
    }

    // Constructor and other member functions...

    void updateBehavior(); // Function to update based on behavior

    glm::vec2 position;
    glm::vec2 velocity;
    float lifespan; // Lifespan in frames
    ofColor color; // Color of the particle
    float size; // Size of the particle

    Particle(glm::vec2 startPos, glm::vec2 startVel, float life, ofColor startColor, float startSize);

    void update();
    void draw() const;
    bool isDead() const;



};
