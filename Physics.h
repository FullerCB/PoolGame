#pragma once
#include "BallManager.h"

using namespace glm;

//Handles Collisions and Forces

class Physics
{
private:
	static std::vector<glm::vec2> collison();
public:
	static std::vector<glm::vec2> accelerationCalculation();
	static bool pocketSinkCheck(int index);
	static bool stationaryCheck();
};


//New Physics Package