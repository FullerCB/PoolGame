
#include "Game.h"

//Intialization of assetmanager
AssetManager Game::assetManager;

//table dimensions in picometers
float tableWidth = 11112.0f;
float tableHeight = tableWidth * 6362.0f / 11112.0f;
//pixels/picometer
float scalingFactor = 1.0f;

void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initAssets()
{
    //Loads vital assets
    assetManager.LoadTexture("table", "assets/pooltablerep.png");
    assetManager.LoadTexture("Corner", "assets/blackcircle1.png");
    assetManager.LoadTexture("cue", "assets/cue.png");
    //Other assets may make if functions
    assetManager.LoadTexture("ball0", "assets/CueBall.png");
    assetManager.LoadTexture("ball1", "assets/Yellow1.png");
    assetManager.LoadTexture("ball2", "assets/Blue2.png");
    assetManager.LoadTexture("ball3", "assets/Red3.png");
    assetManager.LoadTexture("ball4", "assets/Purple4.png");
    assetManager.LoadTexture("ball5", "assets/Orange5.png");
    assetManager.LoadTexture("ball6", "assets/Green6.png");
    assetManager.LoadTexture("ball7", "assets/Brown7.png");
    assetManager.LoadTexture("ball8", "assets/Black8.png");
    assetManager.LoadTexture("ball9", "assets/Yellow9.png");
    assetManager.LoadTexture("ball10", "assets/Blue10.png");
    assetManager.LoadTexture("ball11", "assets/Red11.png");
    assetManager.LoadTexture("ball12", "assets/Purple12.png");
    assetManager.LoadTexture("ball13", "assets/Orange13.png");
    assetManager.LoadTexture("ball14", "assets/Green14.png");
    assetManager.LoadTexture("ball15", "assets/Brown15.png");
}

void Game::atomTypes() {
    std::cout << "Solids atom? (Fe, Al): ";
    std::cin >> this->atom1;
    std::transform(atom1.begin(), atom1.end(), atom1.begin(), ::tolower);
    std::cout << "Stripes atom? (Fe, Al): ";
    std::cin >> this->atom2;
    std::transform(atom2.begin(), atom2.end(), atom2.begin(), ::tolower);
    //the properties basedd on atoms are in creatObjects()
}

void Game::initWindow()
{
	this->video_mode.height = 1200;
	this->video_mode.width = 1920;
    //Fullscreen or titlebar
	this->window = new sf::RenderWindow(this->video_mode, "Pool Game", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

Game::Game()
{
	this->initVariables();
    this->atomTypes();
    this->initAssets();
	this->initWindow();
    this->createObjects();
}

Game::~Game()
{
	delete this->window;
}

//accesors

const bool Game::running() const
{
	return this->window->isOpen();
}

//functions

void Game::createObjects() {
    
    //Background sprite
    backgroundSprite.setTexture(assetManager.GetTexture("table"));

    //Scale the background sprite to fit the window size

    sf::Vector2u windowSize = window->getSize();  //find window size and set variables
    float pixelsX = static_cast<float>(windowSize.x);
    float pixelsY = static_cast<float>(windowSize.y);

    float windowRatio = pixelsX / pixelsY;  //find ratio of window and real ratio of pool table, intialize scales
    float poolRatio = 262.0f / 150.0f;
    float backScaleX, backScaleY;


    //the following conditional statements make sure that the background isnt distorted

    if (poolRatio > windowRatio) { //if window is taller then put vertical bars
        backScaleX = pixelsX / backgroundSprite.getLocalBounds().width;
        backScaleY = backScaleX;
    }
    else if (poolRatio < windowRatio) { //if window is wider then set horizontal bars
        backScaleY = pixelsY / backgroundSprite.getLocalBounds().height;
        backScaleX = backScaleY;
    }
    else if (poolRatio == windowRatio) { //no bars if ratio is equal
        backScaleX = pixelsX / backgroundSprite.getLocalBounds().width;
        backScaleY = pixelsY / backgroundSprite.getLocalBounds().height;
    }
    backgroundSprite.setScale(backScaleX, backScaleY);

    //positioning factor to do physics and positioning and convert to something the window can ouotput (from picometers -> pixels)
    //Pool table normal 262cm x 150cm - Pool atoms is 11112 x 6362 pm

    scalingFactor = backScaleX * backgroundSprite.getLocalBounds().width / tableWidth;

    //Create Cue Sprite
    cueSprite.setTexture(assetManager.GetTexture("cue"));
    float cueScale = 0.33f * backScaleX * backgroundSprite.getLocalBounds().width / cueSprite.getLocalBounds().width; //constant coeff is based on cue to pool table scale
    cueSprite.setScale(cueScale, cueScale);
    cueSprite.setOrigin(cueSprite.getLocalBounds().width, cueSprite.getLocalBounds().height / 2);
    cueSprite.setPosition(2600 * scalingFactor, 100 * scalingFactor);

    // Create sprites for each ball and add them to the vector
    for (int i = 0; i <= 15; ++i) {
        sf::Sprite ballSprite;
        ballSprite.setTexture(assetManager.GetTexture("ball" + std::to_string(i)));
        ballSprites.push_back(ballSprite);
    }


    //Set start position of sprites - manually set, ballSet modifies ballData
    //Pool table normal 262cm x 150cm - Pool atoms is 11112 x 6362 pm
    
    //Ball properties dependent on atom

    if (this->atom1 == "fe") {
        solidRadius = 126;
        solidMass = 55;
        solidCharge = 2;
    }
    if (this->atom1 == "al") {
        solidRadius = 143;
        solidMass = 27;
        solidCharge = 3;
    }

    if (this->atom2 == "fe") {
        stripeRadius = 126;
        stripeMass = 55;
        stripeCharge = 2;
    }
    if (this->atom2 == "al") {
        stripeRadius = 143;
        stripeMass = 27;
        stripeCharge = 3;
    }

    //ballSet modifies ball properties
    //index radius mass charge
    //cue
    ballManager.ballSet(0, 126, 55, 2);
    //8ball
    ballManager.ballSet(8, 126, 55, 0);
    //solids
    for (int i = 1; i <= 7; i++) {
        ballManager.ballSet(i, solidRadius, solidMass, solidCharge);
    }
    //stripes
    for (int i = 9; i <= 15; i++) {
        ballManager.ballSet(i, solidRadius, solidMass, solidCharge);
    }

    //Pool table normal 262cm x 150cm - Pool atoms is 5556 x 3181 pm
    //places them in triangular formation and scratches cue ball
    ballManager.ballInitialize(solidRadius, stripeRadius, tableWidth, tableHeight);


    // Creating Background edge (specific to background sprite  annoying to configure) 5556 x 3181 pm
    // this is essentially creating a shape like this o====o and the physics code determines the nearest point
    // The nearest distance is determine and if the distance is less than sum of the radius of the particle and beam then a collision occurs
    // the beam is defined as a starting point, end point, and radius, the radius is used to approximate the corners on the pool table
    // I could just add more beams so no radius approximation is necessary, but that will increase runtime and not really effect much - this solution is more efficient, faster to implement, and only slightly more complex to code
    // 
    // 
    // SCALAR for changing table values
    float borderScaler = tableHeight / 3181;
    //Create Borders
    Borders::createBorder(borderScaler);
    //Create Pockets
    Borders::createPockets(borderScaler);

    //Create ball sprite scale
    //Pool table is 262cm x 150cm, pool ball is 5.715cm (diameter), however the png for the balls is 980x980 but the ball is only 576x576
    //This is atomic billiards so an atom radius of 126 picometers (iron) will be the same relative size as a normal pool ball
    sf::Sprite tempBallSprite;
    tempBallSprite.setTexture(assetManager.GetTexture("ball1"));
    float visualAdjuster = 1.045f; // accounts for slight visual output discrepency
    float ballScale = visualAdjuster * 0.0372f / 126.0f * backScaleX * backgroundSprite.getLocalBounds().width / tempBallSprite.getLocalBounds().width;
    
    //assigning from ballData to sprites and scaling stuff
    for (int i = 0; i <= 15; ++i) {
        auto textureSize = ballSprites[i].getLocalBounds(); //this finds the size of the sprite
        ballSprites[i].setScale(ballScale * ballData[i].radius, ballScale * ballData[i].radius); //
        ballSprites[i].setOrigin(textureSize.width / 2.f, textureSize.height / 2.f); //sets the positioning of sprite to center (default is top left)
        glm::vec2 spritePosition = ballManager.spriteSet(i, scalingFactor);//sets sprite location for the ballData positins
        ballSprites[i].setPosition(spritePosition.x, spritePosition.y);
    }

    //fixes issue so cue ball will not collide during intialization
    ballData[0].radius = -500;

}


void Game::pollEvents()
{
    //event polling
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            else if (this->ev.key.code == sf::Keyboard::R)
            {
                ballManager.ballInitialize(solidRadius, stripeRadius, tableWidth, tableHeight);
                ballManager.ballRemove(0);
            }
            break;
        }
        
        if (Physics::stationaryCheck()) {
            // Get the mouse position relative to the window
            glm::vec2 mousePosition = glm::vec2(static_cast<float>(sf::Mouse::getPosition(*this->window).x), 
                static_cast<float>(sf::Mouse::getPosition(*this->window).y));

            if (not scratch) { //check if cue has scratched
                if (ballData[0].position.x == -1000.0f){
                    scratch = true;
                }
            }

            if (scratch) { //check if scratch conditon is true
                ballData[0].position = mousePosition / scalingFactor;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { //places  ball after clicking
                    ballData[0].radius = 126;
                    scratch = false;
                }
                break;
            }
            
            
            //this makes it so you can hit the ball from any angle
            float cueScale = tableHeight / 3181;
            float closeWallDistance = min(min(ballData[0].position.x, ballData[0].position.y), min(abs(tableWidth - ballData[0].position.x), abs(tableHeight - ballData[0].position.y)));
            float cueLength = 1832.0f * cueScale ;
            if (closeWallDistance < cueLength) {
                cueLength = closeWallDistance * 0.7f;
            }
            // move cue to mouse
            cue.updateCuePosition(cueSprite, mousePosition.x, mousePosition.y, scalingFactor, cueLength, cueScale);
            if (cue.cueContact(cueLength)) {
                //MUST HOLD SHIFT TO FIRE CUE
                // COULD BE A BUTTON ON MOBILE
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                    ballData[0].velocity = cue.fireCue();
                }
            }
        }
        else {
            cueSprite.setPosition(-100, -500);
        }
        
        break;
        //case sf::Event::MouseButtonPressed:
        //    auto mousPos = sf::Mouse::getPosition(*this->window);
        //    std::cout << mousPos.x / scalingFactor << "," << mousPos.y / scalingFactor << std::endl;
        

    }
}

void Game::pocketHandle()
{
    //determine pocket collisions
    for (int i = 1; i <= 7; i++) {
        if (Physics::pocketSinkCheck(i)) {
            ballManager.ballRemove(i);
        }
    }
    for (int i = 9; i <= 15; i++) {
        if (Physics::pocketSinkCheck(i)) {
            ballManager.ballRemove(i);
        }
    }
    if (Physics::pocketSinkCheck(0)) {
        ballManager.ballRemove(0);
    }
    if (Physics::pocketSinkCheck(8)) {
        ballManager.ballRemove(8);
    }
}

void Game::update() //reality update
{
    //run and check events
    this->pollEvents();

    //handle pocket stuff
    pocketHandle();
    
    //numerical calculations
    NumericalHandling::verlet(0.01667f);

    //movingsprites
    for (int i = 0; i <= 15; ++i) {
        glm::vec2 spritePosition = ballManager.spriteSet(i, scalingFactor);
        ballSprites[i].setPosition(spritePosition.x, spritePosition.y);
    }

    //testing
    //std::cout << length(ballData[0].velocity.x) << std::endl;
}


void Game::render() //visualization
{
    /*
    Renders all objects by clearing frames
    and displaying new frames
    */
    
    this->window->clear();
    this->window->draw(backgroundSprite);

    // Draw balls

    for (const auto& ballSprite : ballSprites) {
        this->window->draw(ballSprite);
    }

    //draw cue
    this->window->draw(cueSprite);

    /*testing
    for (int i = 0; i <= 5; ++i) {
        LineWithCircles borderShape(vectorLines[i], scalingFactor);
        this->window->draw(borderShape);
    }
    */

    //display
    this->window->display();
}