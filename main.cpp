#include <iostream>
#include "Game.h"

using namespace std;

Game *game;

int main()
{
    cout << "Hello world!" << endl;

    // initiate game
    cout << "Welcome to TicTacToe Game" << endl;
    game = new Game();
    game->init();

    // while game not over
    while (game->running())
    {

        // handle events
        cout << "Computer or player turn" << endl;
        game->handleEvents();

        // update
        cout << "Checking victory condition" << endl;
        game->update();

        // render
        game->render();
    }

    // game over
    cout << "Game over condition met (board is full or someone won)" << endl;

    return 0;
}
