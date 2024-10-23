#include "Physics.h"

//types of collisions
static glm::vec2 Default() {

}

static glm::vec2 vanDerWaals() {

}

static glm::vec2 coulomb() {

}

static glm::vec2 gravity() {

}

static glm::vec2 lennardJonesPotential() {

}

//brute force method due to small number of balls. I will implement k-d tree algorithim if time permits but honestly may just add overhead
static std::vector<glm::vec2> collison() {
	std::vector<glm::vec2> force(16);

	for (int i = 0; i <= 15; ++i) {

		//Particle Particle Collisions
		for (int j = i + 1; j <= 15; ++j) {
			glm::vec2 v1 = ballData[i].position; //first ball position
			glm::vec2 v2 = ballData[j].position; //second ball position
			
			//General inputs to minimize calculations
			float distance = glm::length(v2 - v1);

			//___CONTACT FORCES___
			if (distance < (ballData[i].radius + ballData[j].radius)) {

				//General Contact Calculations
				glm::vec2 forceDirection = (v2 - v1) / distance; //unit vector between balls
				float overlap = ballData[i].radius + ballData[j].radius - distance; //finds overlap
				glm::vec2  relativeVelocity = ballData[i].velocity - ballData[j].velocity; //relative velocity

				//this is a nonconservative collision force
				//dynamic contact collision
				float forceMagnitude = 120000 * overlap; //some function of overlap
				force[i] -= forceDirection * forceMagnitude;
				force[j] += forceDirection * forceMagnitude;

				//damping force
				glm::vec2 dampingForce = 500.0f * glm::dot(relativeVelocity, forceDirection) * forceDirection;
				force[i] -= dampingForce;
				force[j] += dampingForce;
			}

			//___NON CONTACT FORCES___

			//coloumbs force determined to awkward to implement - constant slow acceleration and changing board 
			
			//if (distance < (350)) {
				//glm::vec2 forceDirection = (v2 - v1) / distance;
				//glm::vec2 coulombForce = -35000000.0f * (ballData[i].charge * ballData[j].charge) / (distance * distance) * forceDirection;
				//force[i] += coulombForce;
				//force[j] -= coulombForce;
			//}
		}

		//Particle Wall collisions
		for (auto& edge : vectorLines) {
			float fLineX1 = edge.ex - edge.sx;
			float fLineY1 = edge.ey - edge.sy;

			float fLineX2 = ballData[i].position.x - edge.sx;
			float fLineY2 = ballData[i].position.y - edge.sy;

			float fEdgeLength = fLineX1 * fLineX1 + fLineY1 * fLineY1;

			float t = max(0.0f, min(fEdgeLength, (fLineX1 * fLineX2 + fLineY1 * fLineY2))) / fEdgeLength;
			float fClosestPointX = edge.sx + t * fLineX1;
			float fClosestPointY = edge.sy + t * fLineY1;
			glm::vec2 closestPoint(fClosestPointX, fClosestPointY);

			float distance = glm::length(ballData[i].position - closestPoint);
			if (distance < (ballData[i].radius + edge.radius)) {
				//static collision 
				glm::vec2 forceDirection = (ballData[i].position - closestPoint) / distance; //unit vector between balls
				float overlap = ballData[i].radius + edge.radius - distance;
				float forceMagnitude = 6000 * ballData[i].mass * overlap; //some function of overlap
				force[i] += forceDirection * forceMagnitude;
			}
		}

		//Particle Friction force
		if (length(ballData[i].velocity) > 10.0f) {
			glm::vec2 frictionDirection = ballData[i].velocity /   (-1.0f * length(ballData[i].velocity));
			force[i] += (25.0f * length(ballData[i].velocity) + (80.0f * (9.81f) * ballData[i].mass)) * frictionDirection;
		}

		//numerical handling will deal with balls with very small velocities
	}
	return force;
}

std::vector<glm::vec2> Physics::accelerationCalculation() {
	std::vector<glm::vec2> force = collison();
	std::vector<glm::vec2> acceleration(16);
	for (int i = 0; i <= 15; ++i) {
		acceleration[i] = force[i] / ballData[i].mass;
	}
	return acceleration;
}

bool Physics::pocketSinkCheck(int index) {
	for (auto& pocket : pocketLocations) {
		float distance = glm::length(pocket.position - ballData[index].position);
		if (distance < pocket.radius) {
			return true;
		}
	}
	return false;
}

bool Physics::stationaryCheck() {
	for (auto& ball : ballData) {
		if (glm::length(ball.velocity) > 0.0f) {
			return false;
		}
	}
	return true;
}

//Attractive Forces
static std::vector<glm::vec2> forceTemplate() {

}

//Repulsive Forces