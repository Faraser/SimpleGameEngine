#include "MainGame.h"
#include "SDL2/SDL.h"
#include "OpenGL/gl3.h"
#include "iostream"
#include "random"
#include "ctime"

#include "../Engine/Engine.h"
#include "../Engine/Timing.h"

#include "Zombie.h"

MainGame::MainGame() :
        _screenWidth(1024),
        _screenHeight(768),
        _gameState(GameState::PLAY),
        _fps(0),
        _player(nullptr) {

}

MainGame::~MainGame() {
    for (Level* level: _levels) {
        delete level;
    }

    _levels.clear();
}

void MainGame::run() {
    initSystems();
    initLevel();

    gameLoop();
}

void MainGame::initSystems() {
    Engine::init();
    _window.create("Zombie Game", _screenWidth, _screenHeight, 0);

    initShaders();

    _agentSpriteBatch.init();

    _camera.init(_screenWidth, _screenHeight);
}

void MainGame::initShaders() {
    _textureProgram.compileShaders("Shaders/colorShading.vert",
                                   "Shaders/colorShading.frag");
    _textureProgram.addAttribute("vertexPosition");
    _textureProgram.addAttribute("vertexColor");
    _textureProgram.addAttribute("vertexUV");
    _textureProgram.linkShaders();
}

void MainGame::initLevel() {
    _levels.push_back(new Level("Levels/level1.txt"));
    _currentLevel = 0;

    _player = new Player();
    _player->init(4.0f, _levels[_currentLevel]->getStartPlayerPos(), &_inputManager);

    _humans.push_back(_player);


    std::mt19937 randomEngine;
    randomEngine.seed(time(nullptr));
    std::uniform_int_distribution<int> randX(2, _levels[_currentLevel]->getWidth() - 2);
    std::uniform_int_distribution<int> randY(2, _levels[_currentLevel]->getHeight() - 2);

    const float HUMAN_SPEED = 1.0f;

    for (int i = 0; i < _levels[_currentLevel]->getNumHumans(); i++) {
        _humans.push_back(new Human);
        _humans.back()->init(HUMAN_SPEED,
                             glm::vec2(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH));
    }
}


void MainGame::updateAgents() {
    // Update all humans
    for (int i = 0; i < _humans.size(); i++) {
        _humans[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies);
    }
    // Update collisions
    for (int i = 0; i < _humans.size(); i++) {
        for (int j = i + 1; j < _humans.size(); j++) {
            _humans[i]->collideWithAgent(_humans[j]);
        }
    }
}


void MainGame::gameLoop() {
    Engine::FpsLimiter fpsLimiter;
    fpsLimiter.setMaxFPS(60.0f);

    while (_gameState == GameState::PLAY) {
        fpsLimiter.begin();

        processInput();

        updateAgents();

        _camera.setPosition(_player->getPosition());
        _camera.update();

        drawGame();

        _fps = (int) fpsLimiter.end();
    }

}

void MainGame::processInput() {
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT:
                // Exit game
                _gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                _inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
                break;
            case SDL_KEYDOWN:
                _inputManager.pressKey(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
                _inputManager.releaseKey(evnt.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                _inputManager.pressKey(evnt.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                _inputManager.releaseKey(evnt.button.button);
                break;
        }
    }
}

void MainGame::drawGame() {
    // Set the base depth to 0
    glClearDepth(1.0);
    // Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _textureProgram.use();

    glActiveTexture(GL_TEXTURE0);

    // Make sure the shader uses texture 0
    GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
    glUniform1i(textureUniform, 0);

    // Grap the camera matrix
    glm::mat4 projectionMatrix = _camera.getCameraMatrix();
    GLint pUniform = _textureProgram.getUniformLocation("P");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    // Draw the level
    _levels[_currentLevel]->draw();

    // Draw the humans
    _agentSpriteBatch.begin();
    for (int i = 0; i < _humans.size(); i++) {
        _humans[i]->draw(_agentSpriteBatch);
    }
    _agentSpriteBatch.end();
    _agentSpriteBatch.renderBatch();

    _textureProgram.unuse();

    // Swap buffer and draw everything to the screen
    _window.swapBuffer();

}

