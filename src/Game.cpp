#include "Game.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

char board[9];
bool playerTurn = false;
int playerPlayed = -1;

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

bool Game::running() { return isRunning; }

void Game::init(const char* title, int width, int height)
{
    // clear board
    for (int i = 0; i < 9; i++)
    {
        board[i] = ' ';
    }

    // coin toss for start
    // note: rand() is terrible but will be enough here
    srand(time(0));
    playerTurn = (rand() % 2 == 0);

    // create a window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        cout << "SDL Error :" << SDL_GetError() << endl;
        isRunning = false;
    }

    // create a renderer
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (playerTurn)
    {
        cout << "Player starts." << endl;
    } else {
        cout << "Computer starts." << endl;
    }


    isRunning = true;

    // render at init to show current board with number indexes
    render();
}

void Game::handleEvents()
{
    cout << "Polling events..." << endl;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
                cout << "We got a click at " << event.motion.x << "," << event.motion.y << endl;
                if (playerTurn)
                {
                    if ((event.motion.x > 160)&&(event.motion.x < 480)&&(event.motion.y > 140)&&(event.motion.y < 450))
                    {
                        if (event.motion.x < 250)
                        {
                            if (event.motion.y < 240)
                            {
                                playerPlayed = 0;
                            }
                            else if (event.motion.y < 360 )
                            {
                                playerPlayed = 3;
                            }
                            else
                            {
                                playerPlayed = 6;
                            }
                        }
                        else if (event.motion.x < 340)
                        {
                            if (event.motion.y < 240)
                            {
                                playerPlayed = 1;
                            }
                            else if (event.motion.y < 360 )
                            {
                                playerPlayed = 4;
                            }
                            else
                            {
                                playerPlayed = 7;
                            }
                        }
                        else
                        {
                            if (event.motion.y < 240)
                            {
                                playerPlayed = 2;
                            }
                            else if (event.motion.y < 360 )
                            {
                                playerPlayed = 5;
                            }
                            else
                            {
                                playerPlayed = 8;
                            }
                        }
                    }
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
     // check if board is full with no victory conditions met
    bool full = true;
    for (int i = 0; i < 9; i++)
    {
        if (board[i]==' ') {
            full = false;
        }
    }

    if (!full) {
        // PLAY
        int id;
        int input;
        if (playerTurn)
        {
            cout << "Player turn." << endl;
            cout << "Where do you want to play?" << endl;

            if (playerPlayed > -1)
            {
                if (playerPlayed > 8)
                {
                    cout << "Out of range." << endl;
                }
                else if (board[playerPlayed]!=' ')
                {
                    cout << "Can't play over someone's mark." << endl;
                }
                else
                {
                    board[playerPlayed] = 'X';
                    playerTurn = false;
                    playerPlayed = -1;
                }
            }

        } else {
            bool moveFound = false;
            while (!moveFound)
            {
                id = rand() % 9;
                //cout << "Debug : rand()%9 = " << id << endl;
                if (board[id] == ' ')
                {
                    board[id] = 'O';
                    moveFound = true;
                    cout << "Computer plays O at " << id + 1 << endl;
                }
            }
            playerTurn = true;
        }

        // CHECK VICTORY
        /* victory conditions
            0,1,2
            3,4,5
            6,7,8
            0,3,6
            1,4,7
            2,5,8
            0,4,8
            2,4,6
        */

        // there is a cleaner way to check current board against an array of winning conditions
        // most likely the compiler will end up generating similar code
        if (
            ((board[0]=='X')&&(board[1]=='X')&&(board[2]=='X'))
            ||((board[3]=='X')&&(board[4]=='X')&&(board[5]=='X'))
            ||((board[6]=='X')&&(board[7]=='X')&&(board[8]=='X'))
            ||((board[0]=='X')&&(board[3]=='X')&&(board[6]=='X'))
            ||((board[1]=='X')&&(board[4]=='X')&&(board[7]=='X'))
            ||((board[2]=='X')&&(board[5]=='X')&&(board[8]=='X'))
            ||((board[0]=='X')&&(board[4]=='X')&&(board[8]=='X'))
            ||((board[2]=='X')&&(board[4]=='X')&&(board[6]=='X'))
            )
        {
            cout << "Player won." << endl;
            isRunning = false;
        } else if (
            ((board[0]=='O')&&(board[1]=='O')&&(board[2]=='O'))
            ||((board[3]=='O')&&(board[4]=='O')&&(board[5]=='O'))
            ||((board[6]=='O')&&(board[7]=='O')&&(board[8]=='O'))
            ||((board[0]=='O')&&(board[3]=='O')&&(board[6]=='O'))
            ||((board[1]=='O')&&(board[4]=='O')&&(board[7]=='O'))
            ||((board[2]=='O')&&(board[5]=='O')&&(board[8]=='O'))
            ||((board[0]=='O')&&(board[4]=='O')&&(board[8]=='O'))
            ||((board[2]=='O')&&(board[4]=='O')&&(board[6]=='O'))
            )
        {
            cout << "Computer won." << endl;
            isRunning = false;
        }
    } else {
        cout << "Board is full, no one won." << endl;
        isRunning = false;
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

    // draw grid
    SDL_Rect gridARect;
    gridARect.x = 260;
    gridARect.y = 130;
    gridARect.w = 10;
    gridARect.h = 320;
    // set current renderer color
    SDL_SetRenderDrawColor(renderer, 0xCC, 0xBB, 0xAA, 0xFF);
    // render rect
    SDL_RenderFillRect(renderer, &gridARect);

    // draw grid
    SDL_Rect gridBRect;
    gridBRect.x = 370;
    gridBRect.y = 130;
    gridBRect.w = 10;
    gridBRect.h = 320;
    // set current renderer color
    SDL_SetRenderDrawColor(renderer, 0xCC, 0xBB, 0xAA, 0xFF);
    // render rect
    SDL_RenderFillRect(renderer, &gridBRect);

    // draw grid
    SDL_Rect gridCRect;
    gridCRect.x = 160;
    gridCRect.y = 230;
    gridCRect.w = 320;
    gridCRect.h = 10;
    // set current renderer color
    SDL_SetRenderDrawColor(renderer, 0xCC, 0xBB, 0xAA, 0xFF);
    // render rect
    SDL_RenderFillRect(renderer, &gridCRect);

    // draw grid
    SDL_Rect gridDRect;
    gridDRect.x = 160;
    gridDRect.y = 340;
    gridDRect.w = 320;
    gridDRect.h = 10;
    // set current renderer color
    SDL_SetRenderDrawColor(renderer, 0xCC, 0xBB, 0xAA, 0xFF);
    // render rect
    SDL_RenderFillRect(renderer, &gridDRect);

    // actually render
    SDL_RenderPresent(renderer);

    cout << "Current board :\n";
    int curY = 140;
    char curChar;

    for (int i = 0; i < 9; i++)
    {
        SDL_Rect markRect;
        markRect.y = curY;
        // line begin
        if ((i%3) == 0)
        {
            cout << "|";
            markRect.x = 170;
        } else {
            markRect.x = 170 + ((i%3) * 110);
        }

        // show index OR content
        int k = i+1;
        if (board[i] == ' ')
        {
            curChar = k;
            cout << k << "|";
        } else {
            curChar = board[i];
            cout << board[i] << "|";
        }
// line end
        if ((k%3) == 0)
        {
            cout << endl;
            curY += 110;
        }

        markRect.w = 80;
        markRect.h = 80;
        // set current renderer color
        if (curChar == 'X')
        {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x22, 0x22, 0xFF);
        } else if (curChar == 'O') {
            SDL_SetRenderDrawColor(renderer, 0x22, 0xFF, 0x22, 0xFF);
        } else {
            SDL_SetRenderDrawColor(renderer, 0xCC, 0xCC, 0xCC, 0xFF);
        }

        // render rect
        SDL_RenderFillRect(renderer, &markRect);

    }

    cout << endl; // endl will flush buffer but "\n" won't

    // actually render
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    // free memory
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
