#pragma once

#include "../Engine/GLSLprogram.h"
#include "../Engine/Window.h"
#include "../Engine/Camera2D.h"
#include "../Engine/InputManager.h"

#include "Level.h"

#include "vector"

enum class GameState { PLAY, EXIT };

class MainGame {
public:
    MainGame();
    ~MainGame();

    void run();

private:
    void initSystems();
    void initShaders();
    void gameLoop();
    void processInput();
    void drawGame();

    Engine::Window _window;
    Engine::Camera2D _camera;
    Engine::InputManager _inputManager;
    Engine::GLSLprogram _textureProgram;

    std::vector<Level*> _levels;

    int _screenWidth;
    int _screenHeight;

    GameState _gameState;

    int _fps;
    int _currentLevel;
};


