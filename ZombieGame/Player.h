#pragma once

#include "Human.h"

class Player : public Human {
public:
    Player();

    ~Player();

    void init(float speed, glm::vec2 position, Engine::InputManager *inputManager);

    void update();

private:
    Engine::InputManager *_inputManager;

};
