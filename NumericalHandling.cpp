#include "NumericalHandling.h"

void NumericalHandling::verlet(float timeStep) {
	
	//First acceleration calc
	std::vector<glm::vec2> oldAcceleration = Physics::accelerationCalculation();

	//position update
	for (int i = 0; i < ballData.size(); ++i) {

		ballData[i].position += (ballData[i].velocity * timeStep) + oldAcceleration[i] * (0.5f * timeStep * timeStep);
	
	};

	//new acceleration calc
	std::vector<glm::vec2> newAcceleration = Physics::accelerationCalculation();

	//velocity update
	for (int i = 0; i < ballData.size(); ++i) {

		if ((length(ballData[i].velocity) < 10.0f) and (length(newAcceleration[i]) <= 0.0f)){
			ballData[i].velocity = glm::vec2(0.0f, 0.0f);
		}

		ballData[i].velocity += (0.5f * timeStep) * (oldAcceleration[i] + newAcceleration[i]);
	};
}