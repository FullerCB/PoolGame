#include "BallManager.h"

std::vector<sBallManager> ballData(16);

void BallManager::ballSet(int index, float r, float mass, float charge)
{
	ballData[index].radius = r;
    ballData[index].mass = mass;
    ballData[index].charge = charge;
}

void BallManager::ballInitialize(float solidRadius, float stripeRadius, float tableWidth, float tableHeight)
{
    //5556 x 3181 pm
    float blackX = 3108;
    float blackY = tableHeight / 2;
    float positionRadius = glm::max(126.0f, glm::max(stripeRadius, solidRadius));
    
    //cue
    ballData[0].velocity = glm::vec2(0.0f, 0.0f);

    //8ball
    ballData[8].velocity = glm::vec2(0.0f, 0.0f);

    //solids
    for (int i = 1; i <= 7; i++) {
        ballData[i].radius = solidRadius;
        ballData[i].velocity = glm::vec2(0.0f, 0.0f);
    }

    //stripes
    for (int i = 9; i <= 15; i++) {
        ballData[i].radius = stripeRadius;
        ballData[i].velocity = glm::vec2(0.0f, 0.0f);
    }




    //Setup top (front) to bottom (back) all relative to black ball
    ballData[7].position = glm::vec2(3.464f * positionRadius + blackX, blackY);
    ballData[9].position = glm::vec2(1.732f * positionRadius + blackX, blackY + positionRadius);     ballData[13].position = glm::vec2(1.732f * positionRadius + blackX, blackY - positionRadius);
    ballData[1].position = glm::vec2(blackX, blackY - (2 * positionRadius));     ballData[8].position = glm::vec2(blackX, blackY);     ballData[4].position = glm::vec2(blackX, blackY + (2 * positionRadius));
    ballData[14].position = glm::vec2(blackX - (1.732f * positionRadius), blackY - (3 * positionRadius));     ballData[12].position = glm::vec2(blackX - (1.732f * positionRadius), blackY - positionRadius);     ballData[5].position = glm::vec2(blackX - (1.732f * positionRadius), blackY + positionRadius);     ballData[6].position = glm::vec2(blackX - (1.732f * positionRadius), blackY + (3 * positionRadius));
    ballData[2].position = glm::vec2(blackX - (3.464f * positionRadius), blackY - (4 * positionRadius));     ballData[10].position = glm::vec2(blackX - (3.464f * positionRadius), blackY - (2 * positionRadius));     ballData[3].position = glm::vec2(blackX - (3.464f * positionRadius), blackY);    ballData[11].position = glm::vec2(blackX - (3.464f * positionRadius), blackY + (2 * positionRadius));     ballData[15].position = glm::vec2(blackX - (3.464f * positionRadius), blackY + (4 * positionRadius));

}

void BallManager::ballRemove(int index)
{
    //rather than delete the asset and reload (in the case of a reset) just move the asset offscreen to be faster
    ballData[index].radius = -500.0f;
    ballData[index].position = glm::vec2(-1000.0f, -1000.0f);
    ballData[index].velocity = glm::vec2(0.0f, 0.0f);
    ballData[index].acceleration = glm::vec2(0.0f, 0.0f);
}

//sets sprites based on positioning
glm::vec2 BallManager::spriteSet(int index, float scalingFactor)
{
    // Create an instance of the SpritePosition struct
    glm::vec2 spritePosition;

    // Calculate the positions
    spritePosition.x = std::round(ballData[index].position.x * scalingFactor);
    spritePosition.y = std::round(ballData[index].position.y * scalingFactor);

    // Return the SpritePosition
    return spritePosition;
}