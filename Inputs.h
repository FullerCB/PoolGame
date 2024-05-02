#pragma once
#include "BallManager.h"

class Inputs
{
private:
    glm::vec2 cuePos;

public:
    void updateCuePosition(sf::Sprite& cueSprite, float mouseX, float mouseY, float scalingFactor, float cueLengt);
    bool cueContact(float cueLength) const;
    glm::vec2 fireCue() const;
};