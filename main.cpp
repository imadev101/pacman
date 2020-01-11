#include <iostream>
#include "Game.h"
#include "SDL.h"

using namespace std;

Game *game = NULL;

// screen resolutions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int arg, char* args[])
{

    // cap FPS
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO)<0)
    {
        cout << "SDL Error :" << SDL_GetError() << endl;
        return 0;
    }

    // initialize game
    cout << "Welcome to TicTacToe Game" << endl;
    game = new Game();
    game->init("TicTacToe", SCREEN_WIDTH, SCREEN_HEIGHT);

    while (game->running())
    {

        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();

        SDL_Delay(500); // DEV: slow down to read console

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    // game over
    SDL_Delay(3000);
    game->clean();

    delete game;

    return 0;
}
