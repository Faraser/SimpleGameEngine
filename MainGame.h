#pragma once

#include "Engine/GLSLprogram.h"
#include "Engine/Window.h"
#include "Engine/Camera2D.h"
#include "Engine/InputManager.h"

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
    Engine::GLSLprogram _colorProgram;
    Engine::Camera2D _camera;
    Engine::InputManager _inputManager;
};


