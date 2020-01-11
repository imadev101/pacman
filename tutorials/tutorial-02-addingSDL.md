# Implementing SDL into my first c++ game

Today I will enhance the GUI of my TicTacToe game and make it a fully rendered application. For that I will use the SDL2 library.

### What is SDL?

SDL stands for Simple DirectMedia Layer. It is a cross-platform development library designed to provide classes and methods to interact with the player using controllers and graphics and audio rendering.

It is coded in C and works with most famous programming languages. As I'm using C++ I can simply load the native library.

### Setting up SDL2 in my c++ game

My set up is windows + codeblocks with mingw compiler. I need to download and link the library to my compiler, and provide a .dll for the game to run.

Lazy Foo has a tutorial for setting up SDL in nearly every OS/IDE setup :
http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php

Once it works, you should be able to include SDL in the project and run it without an error. I had to fix my main() by adding proper args to make it work because I was getting the SDL_main() not found error.

### Let's make a window

Let's start by including SDL.h on top of our main.cpp. Then we'll need a window, and fill its surface with color.

```cpp
#include <iostream>
#include "Game.h"
#include "SDL.h"

using namespace std;

int main(int arg, char* args[])
{
    Game *game = NULL;

    // the window and its content
    SDL_Window *window = NULL;
    SDL_Surface *surface = NULL;

    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO)<0)
    {
        cout << "SDL Error :" << SDL_GetError() << endl;
        return 0;
    }

    window = SDL_CreateWindow("TicTacToe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        cout << "SDL Error :" << SDL_GetError() << endl;
        return 0;
    }

    // get the window surface pointer
    surface = SDL_GetWindowSurface( window );

    // fill it with orange
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
    SDL_DestroyWindow(window);
    delete game;

    return 0;
}

```

So the code is pretty self-explanatory for most of it, we will have plenty of time to go deeper into what a surface, a rectangle, or a RGBA format is. So far, my set up works and I have a shiny orange window next to my console.

Next part will be about rendering the actual game this way.

The Source code for this commit can be browsed here :
https://github.com/imadev101/tictactoe/tree/c27f44c1a58ccd3e3b12ef531a5e4a8df76d2be1
