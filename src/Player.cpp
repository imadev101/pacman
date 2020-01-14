#include "Player.h"
#include "Map.h"

Player::Player(Game *mGame, Map *mMap)
{
    //ctor
    game = mGame;
    map = mMap;
    name = "JOE";
}

Player::~Player()
{
    //dtor
}

void Player::move(char direction)
{
    int xMod = 0;
    int yMod = 0;
    switch (direction)
    {
    case 'N':
        yMod = -1; // our zero y is north
        break;
    case 'E':
        xMod = 1;
        break;
    case 'S':
        yMod = 1;
        break;
    case 'W':
        xMod = -1;
        break;
    }
    // using modulo allow to round up around map
    int testX = (xPos+xMod)%map->width;
    // modulo is weird with negative number
    if (testX < 0) { testX = map->width; }
    int testY = (yPos+yMod)%map->height;
    if (testY < 0) { testY = map->height; }

    if (map->canWalk(testX, testY))
    {
        xVel = xMod;
        yVel = yMod;
    }
}

void Player::render(SDL_Renderer *renderer, int xPosRender, int yPosRender)
{
    int multiplier = 1;
    SDL_Rect playerRect;
    playerRect.x = xPosRender + xPos*10*multiplier - 3*multiplier;
    playerRect.y = yPosRender + yPos*10*multiplier - 3*multiplier;
    playerRect.w = 16*multiplier;
    playerRect.h = 16*multiplier;

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);

    SDL_RenderFillRect(renderer, &playerRect);
}

void Player::update()
{
        // using modulo allow to round up around map
    int testX = (xPos+xVel)%map->width;
    if (testX < 0) { testX = map->width + xVel; }
    int testY = (yPos+yVel)%map->height;
    if (testY < 0) { testY = map->height + yVel; }

    if (map->canWalk(testX, testY))
    {
        xPos = testX;
        yPos = testY;
    }
}

void Player::setPosition(int x, int y)
{
    xPos = x;
    yPos = y;
}
