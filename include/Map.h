#ifndef MAP_H
#define MAP_H

#include "Game.h"

class Map
{
    public:
        Map();
        virtual ~Map();

        void init();
        void render(SDL_Renderer *renderer, int xPosRender, int yPosRender);

        bool canWalk(int x, int y);


        const int width = 21;
        const int height = 27;

        char tiles[27][21];

        bool hasDot(int x, int y);
        bool eatDot(int x, int y);
        bool hasPowerUp(int x, int y);
        bool eatPowerUp(int x, int y);

    protected:

    private:

};

#endif // MAP_H
