#pragma once
#include "BallManager.h"
#include "Borders.h"

using namespace glm;

//Handles Collisions and Forces

class Physics
{
private:

public:
	//physics equations


	//general calculations
	static std::vector<glm::vec2> accelerationCalculation();
	static bool pocketSinkCheck(int index);
	static bool stationaryCheck();
};


//New Physics Package