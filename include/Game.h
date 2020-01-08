#ifndef GAME_H
#define GAME_H

class Game
{
    public:
        Game();
        virtual ~Game();

        void init();
        void update();
        void render();

        bool running();

    protected:

    private:
        bool isRunning;
};

#endif // GAME_H
