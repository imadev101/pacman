#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Player.h"
#include <iostream>

SDL_Renderer* Game::renderer = nullptr;
TTF_Font *font = NULL;
SDL_Color textColor;

const int PLAYER_START_X =10;
const int PLAYER_START_Y =20;

int hiScore = 12;

bool readyMessage = true;

Game::Game()
{

}

Game::~Game()
{

}

bool Game::running() { return isRunning; }

void Game::init(const char* title, int width, int height)
{
    // create a window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        std::cout << "SDL Error :" << SDL_GetError() << std::endl;
        isRunning = false;
    }

    // create a renderer
    renderer = SDL_CreateRenderer(window, -1, 0);

    // init SDL and TTF
    if(TTF_Init() == -1)
    {
        std::cout << "TTF Error :" << TTF_GetError() << std::endl;
        isRunning = false;
    }
    font = TTF_OpenFont("pixel.ttf", 24);
    textColor = {0,0,0};

    map = new Map();
    map->init();

    player = new Player(this, map);
    player->setPosition(PLAYER_START_X,PLAYER_START_Y);

    isRunning = true;

    // render at init to show current board with number indexes
    render();
}

void Game::handleEvents()
{
    //std::cout << "Polling events..." << std::endl;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
                switch( event.key.keysym.sym)
                {
                case SDLK_UP:
                    player->move('N');
                    break;
                case SDLK_RIGHT:
                    player->move('E');
                    break;
                case SDLK_DOWN:
                    player->move('S');
                    break;
                case SDLK_LEFT:
                    player->move('W');
                    break;
                case SDLK_ESCAPE:
                    isRunning = false;
                    break;
                }
            break;

        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
        }
    }
}

void Game::update()
{
    player->update();
    //map->update();

    // remove ready message
    if ((player->xPos!=PLAYER_START_X)||(player->yPos!=PLAYER_START_Y))
    {
        readyMessage = false;
    }
}

void Game::render()
{
    // clear frame
    SDL_RenderClear(renderer);

    // render background and board
    // draw background
    SDL_Rect bgRect;
    bgRect.x = 0;
    bgRect.y = 0;
    bgRect.w = 640;
    bgRect.h = 480;
    // set current renderer color
    SDL_SetRenderDrawColor(renderer, 255, 170, 0, 255);
    // render rect
    SDL_RenderFillRect(renderer, &bgRect);


    // draw board
    SDL_Rect outerBoardRect;
    outerBoardRect.x = 150;
    outerBoardRect.y = 120;
    outerBoardRect.w = 340;
    outerBoardRect.h = 340;
    // set current renderer color
    SDL_SetRenderDrawColor(renderer, 0xCC, 0xBB, 0xAA, 0xFF);
    // render rect
    SDL_RenderFillRect(renderer, &outerBoardRect);

    SDL_Rect innerBoardRect;
    innerBoardRect.x = 160;
    innerBoardRect.y = 130;
    innerBoardRect.w = 320;
    innerBoardRect.h = 320;
    // set current renderer color
    SDL_SetRenderDrawColor(renderer, 0xEE, 0xDD, 0xCC, 0xFF);
    // render rect
    SDL_RenderFillRect(renderer, &innerBoardRect);

    // draw map
    map->render(renderer, 170, 140);

    player->render(renderer, 170, 140);

    // show ready at start
    if (readyMessage)
    {
        std::cout << "Starting to render ready message" << std::endl;

        // READY BACKGROUND
        SDL_Rect bgRect;
        bgRect.x = 245;
        bgRect.y = 295;
        bgRect.w = 60;
        bgRect.h = 20;

        SDL_SetRenderDrawColor(renderer, 255, 170, 0, 255);
        SDL_RenderFillRect(renderer, &bgRect);

        // READY TEXT
        renderText("READY", 255, 293, 100, 18);
    }

    // render SCORE
    renderText("SCORE", 150, 90, 150, 12);
    renderText("HI-SCORE", 300, 90, 150, 12);
    renderInt(player->score, 150, 102, 150, 12);
    renderInt(hiScore, 300, 102, 150, 12);

    // actually render
    SDL_RenderPresent(renderer);
}

void Game::renderText(const char* chars, int x, int y, int w, int h)
{
    // render SCORE
    SDL_Rect textRect;
    textRect.x = x;
    textRect.y = y;
    textRect.w = w;
    textRect.h = h;

    SDL_Surface* text = TTF_RenderText_Solid(font, chars, textColor);
    SDL_Texture* textTex = SDL_CreateTextureFromSurface(renderer, text);
    // query texture to get result width and height
    SDL_QueryTexture(textTex, NULL, NULL, &textRect.w, &textRect.h);
    SDL_FreeSurface(text);
    SDL_RenderCopy(renderer, textTex, NULL, &textRect);
}

void Game::renderInt(int intToText, int x, int y, int w, int h)
{
    std::string s = std::to_string(intToText);
    char const *pchar = s.c_str();

    renderText(pchar, x, y, w, h);
}

void Game::clean()
{
    // free memory
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    delete player;
    delete map;
}
