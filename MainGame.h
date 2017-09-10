#pragma once
#include "SDL2/SDL.h"
#include "Sprite.h"
#include "GLSLprogram.h"

enum class GameState { PLAY, EXIT };

class MainGame {
public:
    MainGame();
    ~MainGame() = default;

    void run();

private:
    void initSystems();
    void initShaders();
    void gameLoop();
    void processInput();
    void drawGame();

    SDL_Window * _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;
    Sprite _sprite;

    GLSLprogram _colorProgram;
};


