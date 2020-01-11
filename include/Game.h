#ifndef GAME_H
#define GAME_H

#include "SDL.h"

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

        SDL_Renderer *renderer;
        SDL_Window* window;
        SDL_Event event;

    protected:

    private:
        bool isRunning;
};

#endif // GAME_H
