#include "Map.h"
#include "Game.h"
#include "TextureManager.h"
#include <fstream>
#include <iostream>
#include <bits/stdc++.h>

SDL_Texture* dotTexture = NULL;
SDL_Texture* powerUpTexture = NULL;

Map::Map()
{
    dotTexture = TextureManager::LoadTexture(Game::renderer, "images/dot.png");
    powerUpTexture = TextureManager::LoadTexture(Game::renderer, "images/powerUp.png");
}

Map::~Map()
{

}

void Map::init()
{
    // this is a lot easier to read/write than a fully char array
    std::string mapString[27] = {
        "WWWWWWWWWWWWWWWWWWWWW",
        "W.........W.........W",
        "W.WWW.WWW.W.WWW.WWW.W",
        "WoWXW.WXW.W.WXW.WXWoW",
        "W.WWW.WWW.W.WWW.WWW.W",
        "W...................W",
        "W.WWW.W.WWWWW.W.WWW.W",
        "W.WWW.W.WWWWW.W.WWW.W",
        "W.....W...W...W.....W",
        "WWWWW.WWW W WWW.WWWWW",
        "XXXXW.W       W.WXXXX",
        "XXXXW.W WWWWW W.WXXXX",
        "WWWWW.W W   W W.WWWWW",
        "     .  W   W  .     ",
        "WWWWW.W WWWWW W.WWWWW",
        "XXXXW.W       W.WXXXX",
        "XXXXW.W WWWWW W.WXXXX",
        "WWWWW.W WWWWW W.WWWWW",
        "W.........W.........W",
        "W.WWW.WWW.W.WWW.WWW.W",
        "Wo..W...........W..oW",
        "WWW.W.W.WWWWW.W.W.WWW",
        "WWW.W.W.WWWWW.W.W.WWW",
        "W.....W...W...W.....W",
        "W.WWWWWWW.W.WWWWWWW.W",
        "W...................W",
        "WWWWWWWWWWWWWWWWWWWWW"
    };

    // this will split the map strings into the tiles array
    for(int y = 0; y < height; y++)
    {
        strcpy(tiles[y], mapString[y].c_str());
    }
}

void Map::render(SDL_Renderer *renderer, int xPosRender, int yPosRender)
{
    int multiplier = 1; // this make the map bigger

    // each row
    for (int y = 0; y < height; y++)
    {
        // each col
        for (int x = 0; x < width; x++)
        {
            SDL_Rect tile;
            tile.x = xPosRender + x*10*multiplier;
            tile.y = yPosRender + y*10*multiplier;
            tile.w = 10*multiplier;
            tile.h = 10*multiplier;

            switch(tiles[y][x])
            {
            case 'W':
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xCC, 0xFF);
                break;
            case 'X':
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xAA, 0xFF);
                break;
            case 'o':
            case '.':
            case ' ':
                SDL_SetRenderDrawColor(renderer, 0xAA, 0xCC, 0x00, 0xFF);
                break;
            default:
                SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xFF);
                break;
            }
            // render rect
            SDL_RenderFillRect(renderer, &tile);

        }
    }

    // each row
    for (int y = 0; y < height; y++)
    {
        // each col
        for (int x = 0; x < width; x++)
        {
            SDL_Rect tile;
            tile.x = xPosRender + x*10*multiplier;
            tile.y = yPosRender + y*10*multiplier;
            tile.w = 10*multiplier;
            tile.h = 10*multiplier;

            SDL_Rect srcRect;
            srcRect.x = 0;
            srcRect.y = 0;
            srcRect.w = 16;
            srcRect.h = 16;

            switch(tiles[y][x])
            {
            case 'o':
                TextureManager::Draw(renderer, powerUpTexture, srcRect, tile);
                break;
            case '.':
                TextureManager::Draw(renderer, dotTexture, srcRect, tile);
                break;
            default:
                break;
            }

        }
    }
}


bool Map::canWalk(int x, int y)
{
    //std::cout << "canWalk(" << x << ", " << y << ")" << std::endl;
    return ((tiles[y][x]==' ')||(tiles[y][x]=='.')||(tiles[y][x]=='o'));
}

bool Map::hasDot(int x, int y)
{
    return (tiles[y][x]=='.');
}

bool Map::eatDot(int x, int y)
{
    //std::cout << "trying to eat dot at " << x << "," << y << std::endl;
    if (hasDot(x,y))
    {
        //std::cout << "eating dot at " << x << "," << y << std::endl;
        tiles[y][x] = ' ';
        return true;
    }
    return false;
}

bool Map::hasPowerUp(int x, int y)
{
    return (tiles[y][x]=='o');
}

bool Map::eatPowerUp(int x, int y)
{
    if (hasPowerUp(x,y))
    {
        tiles[y][x] = ' ';
        return true;
    }
    return false;
}
