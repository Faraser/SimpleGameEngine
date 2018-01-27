#pragma once

#include "Engine/GLSLprogram.h"
#include "Engine/Window.h"
#include "Engine/Camera2D.h"
#include "Engine/InputManager.h"
#include "Engine/SpriteBatch.h"
#include "Engine/SpriteFont.h"
#include "Engine/AudioEngine.h"
#include "Engine/ParticleEngine2D.h"
#include "Engine/ParticleBatch2D.h"

#include "Level.h"
#include "Player.h"
#include "Bullet.h"

#include <vector>

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

    void drawHud();

    void updateAgents(float deltaTime);

    void updateBullets(float deltaTime);

    void checkVictory();

    void addBlood(const glm::vec2& position, int numParticles);

    Engine::Window _window;

    Engine::Camera2D _camera;
    Engine::Camera2D _hudCamera;

    Engine::InputManager _inputManager;
    Engine::GLSLprogram _textureProgram;

    Engine::SpriteBatch _agentSpriteBatch;
    Engine::SpriteBatch _hudSpriteBatch;
    Engine::SpriteFont * _spriteFont;

    Engine::ParticleEngine2D _particleEngine;
    Engine::ParticleBatch2D* _bloodParticleBatch;

    Engine::AudioEngine _audioEngine;

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


