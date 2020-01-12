# Rendering a TicTacToe board using SDL

I somehow ran out of time before I could clean and tweak this code, the click areas are approximative while the multiple SDL_Delay() calls for debug make the game look laggy and unconsistent.

### Init 

Every SDL initialization goes into my Game::init() function as it should be executed once. 
*Later I will split the code into init() for the main game init() and start() to start a new match, so we don't have to start the application again each time we start a game.*

```cpp
    // create a window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        cout << "SDL Error :" << SDL_GetError() << endl;
        isRunning = false;
    }

    // create a renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
```

The window and renderer vars are member of the Game class. 

### Render

Every time we render a frame we have to start by clearing everything with ```SDL_RenderClear(renderer)```.

I will not copy paste the whole function here as it's all in the github repository, and it's long and boring code, but the logic is to draw and fill Rectangles to have a grid to play the game.

SDL supports loading images as textures but that will be in a future tutorial.

So for every element, we set up a rectangle, set up a color, then either draw (lines) or fill with the renderer.

```cpp
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
```

For the code logic, imagine you're using mspaint and draw rectangles over each others. So start from the background and finish with the frontground.

Once every rectangle is done, just ask the renderer to draw his scope.

```cpp
    SDL_RenderPresent(renderer);
```

### Handling SDL Events

So at first I was not polling SDL events, instead I was only interacting with the console and my SDL window kept crashing while the game still ran on console.

I fix the problem by polling SDL events, it is actually mandatory in the SDL logic.

```cpp
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
                    // catch click pos
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
```

Game::handleEvents() is now called in the main game loop in main.cpp, along with update and render.

### Clean your mess

Don't forget to clean whatever you put in memory. SDL is no different, I now have a Game::clean() that is called whenever the game is over.

```cpp
void Game::clean()
{
    // free memory
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
```

I could probably have put that into the Game destructor instead, but I could need to clean the game without fully destroying it in the future.

So that's it, enjoy the shiny design and color!
