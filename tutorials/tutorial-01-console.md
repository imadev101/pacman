TicTacToe Game using Console

### In this tutorial about a simple Tic Tac Toe game using C++ we will see :
* Basic Game Logic
* Console input and output
* *Unpredictable* AI

### What you need :
* a working IDE for your favorite language, I use [CodeBlocks](www.codeblocks.org) for C++.
* basic object oriented programing skill

![Tic Tac Toe C++ game](https://cdn.steemitimages.com/DQmUtjNEJTnxKkJFgD3AGVQHpD5CMsNyoqkMT4TAjXqjyWW/image.png)

### Let's start

We can head first into the code, as the game is very simple, the mechanics are known, it doesn't need more **modeling** . We want to start a game, have player and AI plays a match, render each step and end game when someone won or board is full.

```cpp
int main()
{
    // init game

    // while game is running
        // play
        // check victory / tie
        // render

    return 0;
}
```

##### That's it. That's the base logic of every game.

Now make it into code, something that everyone should **do on their own** because the goal is to learn to design and code, not to learn how to copy paste.

Our main should look something like that :


```cpp
Game *game

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
```

### The Game class

##### Init

the game->init() is about setting up what's needed to play then starting the game. 

We need a 3x3 board, I will use a size 9 array of char and store it into the game object and assign a blank space as default value for each cell of the board.

```cpp
char board[9];
bool playerTurn = false;

void Game::init()
{
    // clear board
    for (int i = 0; i < 9; i++)
    {
        board[i] = ' ';
    }
```

Then I want a coin toss to know who starts, computer or player.

```cpp
    // note: rand() is terrible but will be enough here
    srand(time(0));
    playerTurn = (rand() % 2 == 0);
```

Once all is set up, the game enters the *running* state and we render the board using console. 

```cpp
    isRunning = true;
    render();
```

##### Update

First thing I want to check is if the board is full, to prevent any further move and end the game with a tie.

If not, we need to check whose turn it is.

###### Player turn :
* Render board and prompt player on his move.
* Check if move is valid (out of range, cell not empty)

###### Computer AI turn :
* Pick a random empty cell (I said the AI would be unpredictable, not smart) and play
* Output computer move

Then we need to check **Victory conditions**, there are several ways to do it, some look better than other, but the goal is to think and learn about the game logic, not make the best loop ever, so I'll just stack IF OR AND to make it work fast.

In the end, the code is compiled and will probably be similar in size and resources used.

I will not copy/paste all the code here, so go ahead and fill the blank. Remember to keep it simple.

##### Render

To be honest, I called it `render()` because I'm used to that logic, but in this case I will use it more for a `drawBoard()` as this is a console application and not a fully rendered game. The name will make more sense when we draw a actual board instead of `O`, `X` and `|`.

For now I will use a conditional loop to parse and draw the board and its content.

```cpp
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
```

Here you go, game logic and code samples, it's not the best game, but it works. And it feels better to finish a simple project than to have unfinished great ones.

#### Source code

If you have a hard time filling the blanks, or if you want to check the header file, include etc, the source can be found on github here : https://github.com/imadev101/tictactoe

#### What's next ?

There's plenty to be learned while working on making this game better, we can add a menu using a state machine, or a true renderer with [SDL library](https://www.libsdl.org/) to draw a proper board, or add a decent AI by implementing a decision making algorithm like [Minimax](https://en.wikipedia.org/wiki/Minimax). We could also dig into networking to make a multiplayer game.
