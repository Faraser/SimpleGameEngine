#pragma once
#include "SDL2/SDL.h"

enum class GameState { PLAY, EXIT };

class MainGame {
public:
    MainGame();
    ~MainGame() = default;

    void run();

private:
    void initSystems();
    void gameLoop();
    void processInput();

    SDL_Window * _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;
};


