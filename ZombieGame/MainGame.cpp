#include "MainGame.h"
#include "SDL2/SDL.h"
#include "OpenGL/gl3.h"
#include "iostream"
#include "random"
#include "ctime"

#include "../Engine/Engine.h"
#include "../Engine/Timing.h"
#include "../Engine/Errors.h"

#include "Zombie.h"
#include "Gun.h"

const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 1.3f;
const float PLAYER_SPEED = 5.0f;


MainGame::MainGame() :
        _screenWidth(1024),
        _screenHeight(768),
        _gameState(GameState::PLAY),
        _fps(0),
        _player(nullptr),
        _numHumansKilled(0),
        _numZombiesKilled(0) {

}

MainGame::~MainGame() {
    for (Level* level: _levels) {
        delete level;
    }

    for (Human* human: _humans) {
        delete human;
    }

    for (Zombie* zombie: _zombies) {
        delete zombie;
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

    // Add the player
    _player = new Player();
    _player->init(PLAYER_SPEED, _levels[_currentLevel]->getStartPlayerPos(), &_inputManager, &_camera, &_bullets);

    _humans.push_back(_player);


    // Add the humans
    std::mt19937 randomEngine;
    randomEngine.seed(time(nullptr));
    std::uniform_int_distribution<int> randX(2, _levels[_currentLevel]->getWidth() - 2);
    std::uniform_int_distribution<int> randY(2, _levels[_currentLevel]->getHeight() - 2);

    for (int i = 0; i < _levels[_currentLevel]->getNumHumans(); i++) {
        _humans.push_back(new Human);
        _humans.back()->init(HUMAN_SPEED,
                             glm::vec2(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH));
    }

    // Add the zombies
    const std::vector<glm::vec2>& zombiePositions = _levels[_currentLevel]->getZombieStartPositions();
    for (int i = 0; i < zombiePositions.size(); i++) {
        _zombies.push_back(new Zombie);
        _zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i]);
    }

    // Set up the players guns
    const float BULLET_SPEED = 7.0f;

    _player->addGun(new Gun("Magnum", 30, 1, glm::radians(10.0f), 30, BULLET_SPEED));
    _player->addGun(new Gun("Shotgun", 60, 20, glm::radians(40.0f), 4, BULLET_SPEED));
    _player->addGun(new Gun("MP5", 5, 1, glm::radians(20.0f), 20, BULLET_SPEED));
}


void MainGame::updateAgents() {
    // Update all humans
    for (int i = 0; i < _humans.size(); i++) {
        _humans[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies);
    }

    // Update all zombies
    for (int i = 0; i < _zombies.size(); i++) {
        _zombies[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies);
    }

    // Update zombie collisions
    for (int i = 0; i < _zombies.size(); i++) {
        // Collide with humans
        for (int j = i + 1; j < _zombies.size(); j++) {
            _zombies[i]->collideWithAgent(_zombies[j]);
        }
        // Collide with humans
        for (int j = 1; j < _humans.size(); j++) {
            if (_zombies[i]->collideWithAgent(_humans[j])) {
                // Add the new zombie and delete the human
                _zombies.push_back(new Zombie);
                _zombies.back()->init(ZOMBIE_SPEED, _humans[j]->getPosition());
                // Delete the human
                delete _humans[j];
                _humans[j] = _humans.back();
                _humans.pop_back();
            }
        }

        // Collide with player
        if (_zombies[i]->collideWithAgent(_player)) {
            Engine::fatalError("GAME OVER");
        }
    }

    // Update human collisions
    for (int i = 0; i < _humans.size(); i++) {
        for (int j = i + 1; j < _humans.size(); j++) {
            _humans[i]->collideWithAgent(_humans[j]);
        }
    }
}

void MainGame::updateBullets() {
    // Update and collide with world
    for (int i = 0; i < _bullets.size();) {
        if (_bullets[i].update(_levels[_currentLevel]->getLevelData())) {
            _bullets[i] = _bullets.back();
            _bullets.pop_back();
        } else {
            i++;
        };

    }

    // Collide with humans and zombies
    bool wasBulletRemoved = false;

    for (int i = 0; i < _bullets.size(); i++) {
        wasBulletRemoved = false;
        // Loop through zombies
        for (int j = 0; j < _zombies.size();) {
            // Check collision
            if (_bullets[i].collideWithAgent(_zombies[j])) {

                // Damage zombie, and kill it if its out of health
                if (_zombies[j]->applyDamage(_bullets[i].getDamage())) {
                    // If zombie died, remove them
                    delete _zombies[j];
                    _zombies[j] = _zombies.back();
                    _zombies.pop_back();
                    _numZombiesKilled++;
                } else {
                    j++;
                }

                // Remove the bullet
                _bullets[i] = _bullets.back();
                _bullets.pop_back();
                wasBulletRemoved = true;
                // Make sure we don't skip the bullet
                i--;
                // Since the bullet died, no need to loop through any more zombies
                break;
            } else {
                j++;
            }
        }

        if (!wasBulletRemoved) {
            // Loop through humans, skip player
            for (int j = 1; j < _humans.size();) {
                // Check collision
                if (_bullets[i].collideWithAgent(_humans[j])) {

                    // Damage human, and kill it if its out of health
                    if (_humans[j]->applyDamage(_bullets[i].getDamage())) {
                        // If zombie died, remove them
                        delete _humans[j];
                        _humans[j] = _humans.back();
                        _humans.pop_back();
                        _numHumansKilled++;
                    } else {
                        j++;
                    }

                    // Remove the bullet
                    _bullets[i] = _bullets.back();
                    _bullets.pop_back();
                    // Make sure we don't skip the bullet
                    i--;
                    // Since the bullet died, no need to loop through any more zombies
                    break;
                } else {
                    j++;
                }
            }
        }
    }

}

void MainGame::gameLoop() {
    Engine::FpsLimiter fpsLimiter;
    fpsLimiter.setMaxFPS(60.0f);

    while (_gameState == GameState::PLAY) {
        fpsLimiter.begin();

        checkVictory();

        _inputManager.update();

        processInput();

        updateAgents();

        updateBullets();

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

    _agentSpriteBatch.begin();

    // Draw the humans
    for (int i = 0; i < _humans.size(); i++) {
        _humans[i]->draw(_agentSpriteBatch);
    }

    // Draw the zombies
    for (int i = 0; i < _zombies.size(); i++) {
        _zombies[i]->draw(_agentSpriteBatch);
    }

    // Draw the bullets
    for (int i = 0; i < _bullets.size(); i++) {
        _bullets[i].draw(_agentSpriteBatch);
    }

    _agentSpriteBatch.end();
    _agentSpriteBatch.renderBatch();

    _textureProgram.unuse();

    // Swap buffer and draw everything to the screen
    _window.swapBuffer();

}

void MainGame::checkVictory() {
    // If all zombies are dead, we win
    if (_zombies.empty()) {
        std::cout << "You killed " << _numZombiesKilled << " zombies" << std::endl;
        std::cout << "You killed " << _numHumansKilled << " humans" << std::endl;
        std::cout << "Humans remaining " << _humans.size() - 1 << std::endl;
        Engine::fatalError("You win!");
    }
}

