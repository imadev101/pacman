#include "Game.h"
#include <random>
#include <ctime>

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
    srand(time(0));
    playerTurn = (rand() % 2 == 0);

    if (playerTurn)
    {
        std::cout << "Player starts." << std::endl;
    } else {
        std::cout << "Computer starts." << std::endl;
    }


    isRunning = true;

    render();

}

void Game::handleEvents()
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
            std::cout << "Player turn." << std::endl;
            std::cout << "Where do you want to draw?" << std::endl;
            /*bool valid = false;
            while (!valid)
            {
                if (id < 0 || id > 8 || board[id]!=' ')
                    // try again
            }*/
            std::cin >> input;
            id = input - 1; // array starts at 0 //todo check valid

            board[id] = 'X';
            playerTurn = false;
        } else {
            bool found = false;
            while (!found)
            {
                int id = rand() % 9;
                //std::cout << "Debug : rand()%9 = " << id << std::endl;
                if (board[id] == ' ')
                {
                    board[id] = 'O';
                    found = true;
                    std::cout << "Computer played O at " << id + 1 << std::endl;
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
            std::cout << "Player won." << std::endl;
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
            std::cout << "Computer won." << std::endl;
            isRunning = false;
        }
    } else {
        std::cout << "Board is full, no one won." << std::endl;
        isRunning = false;
    }


}

void Game::update()
{

}

void Game::render()
{
    std::cout << "Current board\n";
    for (int i = 0; i < 9; i++)
    {
        // line begin
        if ((i%3) == 0)
        {
            std::cout << "|";
        }

        int k = i+1;
        if (board[i] == ' ')
        {
            std::cout << k << "|";
        } else {
            std::cout << board[i] << "|";
        }


        // line end
        if ((k%3) == 0)
        {
            std::cout << "\n";
        }
    }

    std::cout << std::endl; // endl will flush buffer but "\n" won't

    //isRunning = false; // dev todo del
}

void Game::clean()
{

}
