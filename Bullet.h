#pragma once

#include "glm/glm.hpp"
#include "engine/SpriteBatch.h"

class Bullet {
public:
    Bullet(glm::vec2 position, glm::vec2 direction, float speed, int lifeTime);
    ~Bullet();

    void draw(Engine::SpriteBatch &spriteBatch);
    bool update();
private:
    glm::vec2 _position;
    glm::vec2 _direction;
    float _speed;
    int _lifeTime;
};

