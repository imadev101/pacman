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
    // the window and its content
    SDL_Window *window = NULL;
    SDL_Surface *surface = NULL;

    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO)<0)
    {
        cout << "SDL Error :" << SDL_GetError() << endl;
        return 0;
    }

    window = SDL_CreateWindow("TicTacToe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        cout << "SDL Error :" << SDL_GetError() << endl;
        return 0;
    }

    // get the window surface pointer
    surface = SDL_GetWindowSurface( window );

    // fill it
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xAA, 0x00));

    // update
    SDL_UpdateWindowSurface(window);

    // initialize game
    cout << "Welcome to TicTacToe Game" << endl;
    game = new Game();
    game->init();

    while (game->running())
    {
        game->update();
        game->render();
    }

    // game over

    // free memory
    SDL_DestroyWindow(window);
    SDL_Quit();

    delete game;

    return 0;
}
