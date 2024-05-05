#include "Hand.h"


HandGesture recognizeHandGesture(const std::vector<glm::vec2>& handLandmarks) {
    if (handLandmarks.size() < 21) {
        std::cerr << "Error: Not enough landmarks provided." << std::endl;
        return UNKNOWN;  // Ensure all landmarks are present
    }

    // Array to store distances from palm to each fingertip
    float palmToFingers[5];
    // Array to store positions of fingertips
    glm::vec2 fingers[5];
    // Array to store angles between consecutive fingers
    float anglesBetweenFingers[4];

    // Correct indices for fingertips based on the explanation
    int fingerIndices[5] = { 4, 8, 12, 16, 20 };

    for (int i = 0; i < 5; ++i) {
        int idx = fingerIndices[i];
        fingers[i] = handLandmarks[idx];
        palmToFingers[i] = glm::distance(handLandmarks[0], fingers[i]);
        //std::cout << "Distance from palm to fingertip: " << palmToFingers[i] << std::endl;
    }

    // Calculate angles between adjacent fingers
    for (int i = 0; i < 4; ++i) {
        glm::vec2 vec1 = fingers[i] - handLandmarks[0];
        glm::vec2 vec2 = fingers[i + 1] - handLandmarks[0];
        anglesBetweenFingers[i] = glm::angle(glm::normalize(vec1), glm::normalize(vec2));
        //std::cout << "Angle between fingers " << i << " and " << i + 1 << ": " << anglesBetweenFingers[i] << std::endl;
    }

    // Gesture Detection Logic
    bool isHandOpen = std::all_of(palmToFingers, palmToFingers + 5, [](float d) { return d > 0.16; });
    bool isFist = std::all_of(palmToFingers, palmToFingers + 5, [](float d) { return d < 0.10; });
    bool isFlatHand = std::all_of(anglesBetweenFingers, anglesBetweenFingers + 4, [](float angle) { return angle < 0.5; });

    if (isFist) return FIST;
    if (isFlatHand) return FLAT_HAND;
    if (isHandOpen) return OPEN_HAND;
    return CLOSED_HAND;
}

void Hand::setup()
{
    receiver.setup(RECEIVE_PORT);
    ofLogToConsole();
    leftHandLandmarks.resize(21); // Prepare 21 landmarks for each hand
    rightHandLandmarks.resize(21);
    soundManger.setup();
   
}


void Hand::update()
{

    message.clear();
    while (receiver.hasWaitingMessages()) {
        receiver.getNextMessage(message);

        if (message.getAddress() == "/lx" || message.getAddress() == "/ly" ||
            message.getAddress() == "/rx" || message.getAddress() == "/ry") {
            processHandMessage(message);
        }
    }

    // Define a movement threshold, e.g., 0.01 based on your application's scale and sensitivity requirements
    float movementThreshold = 0.01;

    // Check for significant movement before generating particles
    if (hasSignificantMovement(leftHandLandmarks, prevLeftHandLandmarks, movementThreshold) ||
        hasSignificantMovement(rightHandLandmarks, prevRightHandLandmarks, movementThreshold)) {
        // Integrate particle generation here, for example:
        // Generate particles for left hand landmarks
       // Check for significant movement for the left hand
        if (hasSignificantMovement(leftHandLandmarks, prevLeftHandLandmarks, movementThreshold)) {
            for (const auto& landmark : leftHandLandmarks) {
                glm::vec2 particlePos = glm::vec2(landmark.x * ofGetWidth(), landmark.y * ofGetHeight());
                glm::vec2 particleVel = glm::vec2(ofRandom(-1, 1), ofRandom(-1, 0)); // Random velocity for more dynamic effect
                float particleLife = ofRandom(60, 120); // Lifespan in frames
                ofColor particleColor = ofColor::fromHsb(ofRandom(255), 255, 255); // Random color for each particle
                float particleSize = ofRandom(3, 6); // Random size for each particle

                particles.emplace_back(particlePos, particleVel, particleLife, particleColor, particleSize);
            }
        }

        // Check for significant movement for the right hand
        if (hasSignificantMovement(rightHandLandmarks, prevRightHandLandmarks, movementThreshold)) {
            for (const auto& landmark : rightHandLandmarks) {
                glm::vec2 particlePos = glm::vec2(landmark.x * ofGetWidth(), landmark.y * ofGetHeight());
                glm::vec2 particleVel = glm::vec2(ofRandom(-1, 1), ofRandom(-1, 0)); // Random velocity for more dynamic effect
                float particleLife = ofRandom(60, 120); // Lifespan in frames
                ofColor particleColor = ofColor::fromHsb(ofRandom(255), 255, 255); // Random color for each particle
                float particleSize = ofRandom(3, 6); // Random size for each particle

                particles.emplace_back(particlePos, particleVel, particleLife, particleColor, particleSize);
            }
        }

    }

    HandGesture leftHandGesture = recognizeHandGesture(leftHandLandmarks);
    HandGesture rightHandGesture = recognizeHandGesture(rightHandLandmarks);

    // Set particle behaviors based on hand gestures
    for (auto& particle : particles) {
        if (leftHandGesture == OPEN_HAND || rightHandGesture == OPEN_HAND) {
            particle.setBehavior(Particle::NORMAL);
            currentBehaviorDescription = "Behavior: Normal";
            soundManger.playSound(SoundManager::Normal);
        }
        else if (leftHandGesture == CLOSED_HAND || rightHandGesture == CLOSED_HAND) {
            particle.setBehavior(Particle::ATTRACT);
            currentBehaviorDescription = "Behavior: Attract";
            soundManger.playSound(SoundManager::PARTICLES_SOUND);
        }
        else if (leftHandGesture == FIST || rightHandGesture == FIST) {
            particle.setBehavior(Particle::REPEL);
            currentBehaviorDescription = "Behavior: Repel";
            soundManger.playSound(SoundManager::REPEL);
        }
        else if (leftHandGesture == FLAT_HAND || rightHandGesture == FLAT_HAND) {
            particle.setBehavior(Particle::SWIRL);  // Example: Using SWIRL for flat hand
            currentBehaviorDescription = "Behavior: SWIRAL";
            soundManger.playSound(SoundManager::SWIRL);
        }
    }
   
    // Update particles regardless of movement
    std::for_each(particles.begin(), particles.end(), [](Particle& particle) {
        particle.update();
        });

    // Remove dead particles
    particles.erase(std::remove_if(particles.begin(), particles.end(),
        [](const Particle& particle) { return particle.isDead(); }), particles.end());

  

    prevLeftHandLandmarks = leftHandLandmarks;
    prevRightHandLandmarks = rightHandLandmarks;
}


void Hand::processHandMessage(const ofxOscMessage& message)
{
    std::vector<glm::vec2>* handLandmarks = nullptr;

    // Determine which hand the message is for and select the appropriate landmark vector
    if (message.getAddress() == "/lx" || message.getAddress() == "/ly") {
        handLandmarks = &leftHandLandmarks;
    }
    else if (message.getAddress() == "/rx" || message.getAddress() == "/ry") {
        handLandmarks = &rightHandLandmarks;
    }

    if (handLandmarks) {
        for (int i = 0; i < 21; ++i) {
            // Update x or y based on the message address
            if (message.getAddress()[2] == 'x') { // Check the third character for 'x' or 'y'
                (*handLandmarks)[i].x = message.getArgAsFloat(i);
            }
            else {
                (*handLandmarks)[i].y = message.getArgAsFloat(i);
            }
        }
    }
}

void Hand::draw()
{
    //ofSetColor(ofColor::black);  // Set text color to white
    drawBox();
    
    // Draw current behavior description
    ofDrawBitmapString(currentBehaviorDescription, 10, ofGetHeight() - 20);
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);  // Enable additive blending
    for (auto& particle : particles) {
        particle.draw();
    }
    ofDisableBlendMode();  // Reset to default blend mode
    drawLanmarks();
}

std::pair<glm::vec2, glm::vec2> Hand::getBoundingBox(const std::vector<glm::vec2>& handLandmarks) {
    if (handLandmarks.empty()) return { {0, 0}, {0, 0} };

    float minX = handLandmarks[0].x, maxX = handLandmarks[0].x;
    float minY = handLandmarks[0].y, maxY = handLandmarks[0].y;

    for (const auto& landmark : handLandmarks) {
        minX = min(minX, landmark.x);
        maxX = max(maxX, landmark.x);
        minY = min(minY, landmark.y);
        maxY = max(maxY, landmark.y);
    }

    return { {minX, minY}, {maxX, maxY} };
}


void Hand::displayFingerNames() {
    // Placeholder for displaying finger names or IDs
    // This is where you could loop over landmarks and draw text for each
    ofSetColor(ofColor::black);
    // Example for the left hand
    std::vector<std::string> fingerNames = { "PalmBase","Thumb", "Index", "Middle", "Ring", "Pinky" };
    for (int i = 0; i < leftHandLandmarks.size() && i < fingerNames.size() * 4; i += 4) {
        ofDrawBitmapString(fingerNames[i / 4], leftHandLandmarks[i].x * ofGetWidth(), leftHandLandmarks[i].y * ofGetHeight());
    }
    for (int i = 0; i < rightHandLandmarks.size() && i < fingerNames.size() * 4; i += 4) {
        ofDrawBitmapString(fingerNames[i / 4], rightHandLandmarks[i].x * ofGetWidth(), rightHandLandmarks[i].y * ofGetHeight());
    }
}

void Hand::drawBox() {
    // Get bounding boxes for both hands
    ofSetColor(0);
    auto leftHandBox = getBoundingBox(leftHandLandmarks);
    auto rightHandBox = getBoundingBox(rightHandLandmarks);

    // Draw rectangles around both hands
    ofNoFill(); // Draw only the outline of the rectangle
    ofSetLineWidth(2); // Set the line width

    // Adjusting for window size and drawing left hand box
    ofDrawRectangle(leftHandBox.first.x * ofGetWidth(), leftHandBox.first.y * ofGetHeight(),
        (leftHandBox.second.x - leftHandBox.first.x) * ofGetWidth(),
        (leftHandBox.second.y - leftHandBox.first.y) * ofGetHeight());

    // Drawing right hand box
    ofDrawRectangle(rightHandBox.first.x * ofGetWidth(), rightHandBox.first.y * ofGetHeight(),
        (rightHandBox.second.x - rightHandBox.first.x) * ofGetWidth(),
        (rightHandBox.second.y - rightHandBox.first.y) * ofGetHeight());
}

void Hand::drawLanmarks() {
    // Assuming the landmarks are normalized, we map them to the window dimensions.
    ofSetColor(0);
    for (const auto& landmark : leftHandLandmarks) {
        ofDrawCircle(landmark.x * ofGetWidth(), landmark.y * ofGetHeight(), 10);
    }

    //ofSetColor(ofColor::red);
    for (const auto& landmark : rightHandLandmarks) {
        ofDrawCircle(landmark.x * ofGetWidth(), landmark.y * ofGetHeight(), 10);
    }
}

//This is a good practice as it avoids unnecessary particle generation when there is minimal or no movement.
bool Hand::hasSignificantMovement(const vector<glm::vec2>& currentLandmarks, const vector<glm::vec2>& prevLandmarks, float threshold)
{
    if (currentLandmarks.size() != prevLandmarks.size()) return true; // Size mismatch, assume movement

    for (size_t i = 0; i < currentLandmarks.size(); ++i) {
        if (glm::distance(currentLandmarks[i], prevLandmarks[i]) > threshold) {
            return true; // Found significant movement
        }
    }

    return false; // No significant movement found
}


