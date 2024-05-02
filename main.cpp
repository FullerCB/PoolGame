#include "Game.h"



int main()
{
    //game engine
    Game game;


    //game loop
    while (game.running())
    {
        //Update
        game.update();
        //Render
        game.render();
    }

    return 0;
}