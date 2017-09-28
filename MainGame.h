#pragma once
#include "SDL2/SDL.h"
#include "engine/Sprite.h"
#include "engine/GLSLprogram.h"
#include "engine/GLTexture.h"
#include "vector"
#include "engine/Window.h"
#include "engine/Camera2D.h"
#include "engine/SpriteBatch.h"
#include "engine/InputManager.h"

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

    Engine::Window _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;

    Engine::GLSLprogram _colorProgram;
    Engine::Camera2D _camera;

    Engine::SpriteBatch _spriteBatch;

    Engine::InputManager _inputManager;

    float _fps;
    float _maxFPS;
    float _frameTime;

    float _time;
};


