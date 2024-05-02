#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>


//create data structures and externalize them

struct sBallManager {
    float radius;
    float mass;
    float charge;
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;
};
extern std::vector<sBallManager> ballData; // Declaration of the vector of Ball objects

struct sLineSegment {
    float sx, sy;
    float ex, ey;
    float radius;
};

extern std::vector<sLineSegment> vectorLines;

struct sPocketProperties {
    glm::vec2 position;
    float radius;
};

extern std::vector<sPocketProperties> pocketLocations;

// Define the struct for sprite position
struct SpritePosition {
    float x, y;
};

class BallManager {
public:
    //member functions
    void ballSet(int index, float r, float mass, float charge);
    void ballInitialize(float solidRadius, float stripeRadius);
    void ballRemove(int index);
    SpritePosition spriteSet(int index, float scalingFactor);
};