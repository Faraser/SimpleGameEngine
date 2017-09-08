#pragma once
#include "SDL2/SDL.h"

class MainGame {
public:
    MainGame();
    ~MainGame() = default;

    void run();

    void initSystems();

private:
    SDL_Window * _window;
    int _screenWidth;
    int _screenHeight;
};


