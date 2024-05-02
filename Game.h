#pragma once

#include "AssetManager.h"
#include "Physics.h"
#include "NumericalHandling.h"
#include "Inputs.h"


/*

Game engine

*/

class Game
{
private:
	static AssetManager assetManager; // Declare a static AssetManager object
	BallManager ballManager; // Declare a ballManager object
	Inputs cue; //cue object

	sf::RenderWindow* window;
	sf::VideoMode video_mode;
	sf::Event ev;

	sf::Sprite backgroundSprite;
	sf::Sprite cueSprite;

	// Create a vector to store the ball sprites
	std::vector<sf::Sprite> ballSprites;
	float scalingFactor;

	//other variables
	bool scratch = true;
	std::string atom1;
	std::string atom2;
	float solidRadius = 0;
	float solidMass = 0;
	float solidCharge = 0;
	float stripeRadius = 0;
	float stripeMass = 0;
	float stripeCharge = 0;

	void initVariables();
	void initAssets();
	void atomTypes();
	void initWindow();
	void createObjects();
	void pocketHandle();

public:
	//constructors / deconstrutors
	Game();
	virtual ~Game();

	//accessors

	const bool running() const;

	//functions
	void pollEvents();
	void update();
	void render();
};
