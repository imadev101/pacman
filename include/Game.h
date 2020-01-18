#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <bits/stdc++.h>

// predeclaration
class Map;
class Player;


class Game
{
    public:
        Game();
        virtual ~Game();

        void init(const char* title, int width, int height);
        void handleEvents();
        void update();
        void render();
        void clean();

        bool running();

        static SDL_Renderer *renderer;
        SDL_Window* window;
        SDL_Event event;

        Map *map;
        Player *player;

        void renderText(const char* chars, int x, int y, int w, int h);
        void renderInt(int intToText, int x, int y, int w, int h);

    protected:

    private:
        bool isRunning;

};

#endif // GAME_H
