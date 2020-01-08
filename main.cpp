#include <iostream>
#include "Game.h"

using namespace std;

Game *game;

int main()
{
    // initiate game
    cout << "Welcome to TicTacToe Game" << endl;
    game = new Game();
    game->init();

    while (game->running())
    {
        game->update();
        game->render();
    }

    // game over

    return 0;
}
