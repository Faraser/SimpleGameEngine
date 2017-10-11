#pragma once

#include "../Engine/GLSLprogram.h"
#include "../Engine/Window.h"
#include "../Engine/Camera2D.h"
#include "../Engine/InputManager.h"
#include "../Engine/SpriteBatch.h"

#include "Level.h"
#include "Player.h"
#include "Bullet.h"

#include "vector"

class Zombie;

enum class GameState {
    PLAY, EXIT
};

class MainGame {
public:
    MainGame();

    ~MainGame();

    void run();

private:
    void initSystems();

    void initShaders();

    void initLevel();

    void gameLoop();

    void processInput();

    void drawGame();

    void updateAgents(float deltaTime);

    void updateBullets(float deltaTime);

    void checkVictory();

    Engine::Window _window;
    Engine::Camera2D _camera;
    Engine::InputManager _inputManager;
    Engine::GLSLprogram _textureProgram;
    Engine::SpriteBatch _agentSpriteBatch;

    std::vector<Level*> _levels;

    std::vector<Human*> _humans;
    std::vector<Zombie*> _zombies;
    std::vector<Bullet> _bullets;

    int _numHumansKilled;
    int _numZombiesKilled;

    Player* _player;

    int _screenWidth;
    int _screenHeight;

    GameState _gameState;

    int _fps;
    int _currentLevel;
};


