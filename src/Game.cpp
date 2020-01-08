#include "Game.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

char board[9];
bool playerTurn = false;

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

bool Game::running() { return isRunning; }

void Game::init()
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
            /*
            //todo check valid move from player
            bool valid = false;
            while (!valid)
            {
                if (id < 0 || id > 8 || board[id]!=' ')
                    // try again
            }
            */
            cin >> input;
            id = input - 1; // array starts at 0, render at 1

            board[id] = 'X';
            playerTurn = false;
        } else {
            bool moveFound = false;
            while (!moveFound)
            {
                int id = rand() % 9;
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
    cout << "Current board :\n";
    for (int i = 0; i < 9; i++)
    {
        // line begin
        if ((i%3) == 0)
        {
            cout << "|";
        }

        // show index OR content
        int k = i+1;
        if (board[i] == ' ')
        {
            cout << k << "|";
        } else {
            cout << board[i] << "|";
        }


        // line end
        if ((k%3) == 0)
        {
            cout << "\n";
        }
    }

    cout << endl; // endl will flush buffer but "\n" won't
}
