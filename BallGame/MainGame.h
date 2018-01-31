#pragma once

#include <Engine/Camera2D.h>
#include <Engine/SpriteBatch.h>
#include <Engine/InputManager.h>
#include <Engine/Window.h>
#include <Engine/GLSLprogram.h>
#include <Engine/Timing.h>
#include <memory>

#include "Ball.h"
#include "BallRenderer.h"
#include "BallController.h"

enum class GameState {
    RUNNING, EXIT
};

class MainGame {
public:
    ~MainGame();

    void run();

private:
    void init();

    void initRenderers();

    void initBalls();

    void update(float deltaTime);

    void draw();

    void processInput();

    int m_screenWidth = 0;
    int m_screenHeight = 0;

    std::vector<Ball> m_balls;

    int m_currentRenderer = 0;
    std::vector<std::unique_ptr<BallRenderer>> m_ballRenderers;

    BallController m_ballController;

    Engine::Window m_window;
    Engine::SpriteBatch m_spriteBatch;
    Engine::Camera2D m_camera;
    Engine::InputManager m_inputManager;
    Engine::GLSLprogram m_textureProgram;

    Engine::FpsLimiter m_fpsLimiter;
    float m_fps = 0.0f;

    GameState m_gameState = GameState::RUNNING;
};


