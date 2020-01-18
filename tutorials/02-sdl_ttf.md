# Back to Pacman

Lately I have been reading about behavior tress, poking dots and color with procedural generation, and I felt like I had to go back to finish pacman.

Finishing project is sometime tedious and could seem useless because no one is ever going to play some games meant to be tutorial, but it's actually rewarding, and will force one to learn about the details.

So here I am again, wanting to jump to next project, and forcing myself to finish the simple stuff.

### Updates on Pacman :
* No tutorial will be written for the tile board or how pacman eat the dots as I plan to use vectors and an entity system is the next game, and this will be far more interesting to talk about.
* Dots and PowerUps now spawn on init()
* Pacman can eat them and win score (a status is applied for 10 seconds after eating a powerup)
* Score is now written.

Yup, written. SDL don't handle how to write stuff. So I need the SDL_ttf library, which will create a texture from a text and a font.

Basically, it's installed like SDL, or SDL_image or any extension. Download the dev files, link them into your project, and put the .dll into the project directory.

[See here how to setup SDL_ttf](http://gigi.nullneuron.net/gigilabs/displaying-text-in-sdl2-with-sdl_ttf/)

See how to install SDL_ttf on your project.

So here is today's subject :

### Writing stuff with SDL_ttf

The SDL_ttf library adds a set of tools and functions that works similar to SDL in the way of they need to be calls for load and quits.

I will add these in the mains Game::init() and Game::clean() methods :

```cpp
    // init SDL and TTF
    if(TTF_Init() == -1)
    {
        std::cout << "TTF Error :" << TTF_GetError() << std::endl;
        isRunning = false;
    }
    font = TTF_OpenFont("pixel.ttf", 24);
    textColor = {0,0,0};

```

```cpp
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
```

### Now the good stuff 

SDL_ttf can Render text from a string, it has some anti-aliasing and blending options (that can be resources intensive). I will use the solid rendering because I like pixels. 

```cpp
    SDL_Surface* text = TTF_RenderText_Solid(font,"READY", textColor);
```

Now the SDL renderer requires a texture so let's create one first.

```cpp
    SDL_Texture* textTex = SDL_CreateTextureFromSurface(renderer, text);
```

And we can now Free the memory used for the surface :

```cpp
    SDL_FreeSurface(text);
```

To render a copy, we also need a Rect for the destination area.

```cpp
    SDL_Rect textRect;
    textRect.x = 100;
    textRect.y = 50;
    textRect.w = 100;
    textRect.h = 20;
```

SDL_RenderCopy() will stretch the texture on the Rect, so we actually need to know what width and height are for the texture from text surface (especially when I don't know how long the text will be).

Which we can do with a query, sending references of our rect so the Query can edit position.

```cpp
SDL_QueryTexture(textTex, NULL, NULL, &textRect.w, &textRect.h);
```

Now the Rect will be of good width and height, we can call the RenderCopy()

```cpp
    SDL_RenderCopy(renderer, textTex, NULL, &textRect);
```

Et voila!

Since I have to call all this code several times, I made it into a couple functions to render a string or an int :

```cpp
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

```

All the source is in this commit :
https://github.com/imadev101/pacman/tree/d8c16d080319f438abbef6ae96939f2388f2f3d5


### TODO

Pacman is *nearly* finished, I *only* need to add : 
* ghosts
* lives
* fruits
* score persistence

but I may poke around some more stuff before that.
