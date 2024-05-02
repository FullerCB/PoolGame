#include "Inputs.h"

static std::vector<glm::vec2> cuePosHistory(4);

void Inputs::updateCuePosition(sf::Sprite& cueSprite, float mouseX, float mouseY, float scalingFactor, float cueLength) {
	glm::vec2 startPoint = ballData[0].position;
	cuePos = glm::vec2(mouseX / scalingFactor, mouseY / scalingFactor);
	float dx = cuePos.x - startPoint.x;
	float dy = cuePos.y - startPoint.y;
	float angle = atan2f(dy, dx) * 180.0f / 3.14159f;
	cueSprite.setPosition((cos(angle * 3.14159f / 180.0f) * (1832.0f - cueLength) + cuePos.x) * scalingFactor , (sin(angle * 3.1415926f / 180.0f) * (1832.0f - cueLength) + cuePos.y) * scalingFactor);
	cueSprite.setRotation(angle);
	cuePosHistory.insert(cuePosHistory.begin(), cuePos);
	cuePosHistory.pop_back();
}

bool Inputs::cueContact(float cueLength) const{
	if ((glm::length(cuePos - ballData[0].position)) < (ballData[0].radius + cueLength)) {
		return true;
	}
	return false;
}

glm::vec2 Inputs::fireCue() const{
	//uses last 4 frames to determine velocity of stick
	float xVel = (cuePosHistory[0].x - cuePosHistory[3].x) / (4.0f / 60.0f);
	float yVel = (cuePosHistory[0].y - cuePosHistory[3].y) / (4.0f / 60.0f);
	glm::vec2 velocityCue = glm::vec2(xVel, yVel) / 1.2f; //1.2 is arbitray just for a more natural feeling
	glm::vec2 distanceVec = ballData[0].position - cuePos;
	float dotProduct = glm::dot(velocityCue, distanceVec);
	float distanceMagnitudeSquared = glm::length(distanceVec) * glm::length(distanceVec);
	glm::vec2 projectedVelocity = (dotProduct / distanceMagnitudeSquared) * distanceVec;
	if (length(projectedVelocity) > 8000) { //limits max speed and prevents breaking the game
		float scale = length(projectedVelocity) / 8000;
		projectedVelocity = projectedVelocity / scale;
	}
	return glm::vec2(projectedVelocity.x, projectedVelocity.y);	
}