#pragma once
#include "SDL2/SDL.h"
#include "engine/Sprite.h"
#include "engine/GLSLprogram.h"
#include "engine/GLTexture.h"
#include "vector"
#include "engine/Window.h"

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
    void calculateFPS();

    Window _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;
    std::vector<Sprite*> _sprites;

    GLSLprogram _colorProgram;

    float _fps;
    float _maxFPS;
    float _frameTime;

    float _time;
};


