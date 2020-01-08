#ifndef GAME_H
#define GAME_H

#include <iostream>

class Game
{
    public:
        Game();
        virtual ~Game();

        void init();
        void handleEvents();
        void update();
        void render();
        void clean();

        bool running();

    protected:

    private:
        bool isRunning;
};

#endif // GAME_H
