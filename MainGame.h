#pragma once
#include "SDL2/SDL.h"
#include "Engine/Sprite.h"
#include "Engine/GLSLprogram.h"
#include "Engine/GLTexture.h"
#include "vector"
#include "Engine/Window.h"
#include "Engine/Camera2D.h"
#include "Engine/SpriteBatch.h"
#include "Engine/InputManager.h"
#include "Engine/Timing.h"

#include "Bullet.h"

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

    Engine::Window _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;

    Engine::GLSLprogram _colorProgram;
    Engine::Camera2D _camera;

    Engine::SpriteBatch _spriteBatch;

    Engine::InputManager _inputManager;
    Engine::FpsLimiter _fpsLimiter;

    float _fps;
    float _maxFPS;

    float _time;

    std::vector<Bullet> _bullets;
};


