#include "Game.h"

char board[9];

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
    for (int i = 0; i < 9; i++)
    {
        board[i] = ' ';
    }

    isRunning = true;
}

void Game::handleEvents()
{

}

void Game::update()
{

}

void Game::render()
{
    std::cout << "Current board\n";
    for (int i = 0; i < 9; i++)
    {
        // if line begin
        if ((i%3) == 0)
        {
            std::cout << "|";
        }

        int k = i+1;
        std::cout << k << "|";

        // if line end
        if ((k%3) == 0)
        {
            std::cout << "\n";
        }
    }

    std::cout << std::endl;

    isRunning = false;
}

void Game::clean()
{

}
