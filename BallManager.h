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

class BallManager {
public:
    /// <summary>
    /// Sets Ball Parameters
    /// </summary>
    /// <param name="index"> - the index for ball selection</param>
    /// <param name="r"> - radius in picometers</param>
    /// <param name="mass"> - mass in atomic mass units</param>
    /// <param name="charge"> - charge in elementary charge</param>
    void ballSet(int index, float r, float mass, float charge);
    void ballInitialize(float solidRadius, float stripeRadius, float tableWidth, float tableHeight);
    void ballRemove(int index);
    glm::vec2 spriteSet(int index, float scalingFactor);
};