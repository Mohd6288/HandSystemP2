#include "Particle.h"

Particle::Particle(glm::vec2 startPos, glm::vec2 startVel, float life, ofColor startColor, float startSize)
    : position(startPos), velocity(startVel), lifespan(life), color(startColor), size(startSize), behavior(NORMAL),blendMode(DEFAULT) {
    // Constructor implementation
}

void Particle::updateBehavior() {
    switch (behavior) {
    case NORMAL:
        // Normal behavior implementation
        position += velocity;
        lifespan -= 1;
        size *= 0.98;
        color = color.lerp(ofColor(55, 20, 120), 0.03);
        velocity.x += ofRandom(-1, 1);
        velocity.y -= 0.1;
        blendMode = DEFAULT;
        break;
    case BOUNCE:
        // Bounce behavior: Ensuring particles bounce off window edges
        position += velocity;
        if (position.x <= 0 || position.x >= ofGetWidth()) velocity.x *= -1;
        if (position.y <= 0 || position.y >= ofGetHeight()) velocity.y *= -1;
        break;
    case SWIRL: {

        // Swirl behavior: Particles move in a circular path
        float angle = atan2(velocity.y, velocity.x) + ofDegToRad(2); // Increment angle
        auto speed = velocity.length();
        velocity.x = cos(angle) * speed;
        velocity.y = sin(angle) * speed;
        position += velocity;
        color = color.lerp(ofColor(55, 20, 120), 0.03);
        blendMode = ADD;
        // Optional: Implement central attraction or dynamic swirling center
        break;
    }
    
    case REPEL: {
        glm::vec2 repelPoint(ofGetWidth() / 2, ofGetHeight() / 2); // Repulsion point (center of the screen)
        glm::vec2 direction = position - repelPoint;
        float distance = glm::length(direction);
        float strength = std::min(10.0f, 100.0f / (distance + 1.0f)); // Repulsion strength diminishes with distance
        direction = glm::normalize(direction);
        color = color.lerp(ofColor(55, 20, 120), 0.03);
        velocity += direction * strength * 0.1f; // Adjust this factor to increase/decrease the influence
        position += velocity;
        blendMode = SUBTRACT;
        break;
    }
    case ATTRACT: {
        glm::vec2 attractPoint(ofGetWidth() / 2, ofGetHeight() / 2); // Attraction point (center of the screen)
        glm::vec2 direction = attractPoint - position;
        float distance = glm::length(direction);
        float strength = std::min(10.0f, 100.0f / (distance + 1.0f)); // Attraction strength diminishes with distance
        direction = glm::normalize(direction);
        color = color.lerp(ofColor(55, 20, 120), 0.03);
        velocity += direction * strength * 0.1f; // Adjust this factor to increase/decrease the influence
        position += velocity;
        blendMode = SCREEN;
        break;
    }
    }

}

void Particle::update() {
    updateBehavior();
}

void Particle::draw() const {

    switch (blendMode) {
    case DEFAULT:
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        break;
    case ADD:
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        break;
    case SUBTRACT:
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        break;
    case SCREEN:
        ofEnableBlendMode(OF_BLENDMODE_SCREEN);
        break;
    }

    ofSetColor(color);
    ofFill();
    ofDrawCircle(position,size);
    ofDisableBlendMode();
}

bool Particle::isDead() const {
    return lifespan <= 0;
}

