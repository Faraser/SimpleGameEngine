#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "../Engine/SpriteBatch.h"

class Human;
class Zombie;

const int BULLET_RADIUS = 5;

class Bullet {
public:
    Bullet(glm::vec2 position, glm::vec2 direction, float damage, float speed);

    ~Bullet();

    void update(std::vector<Human*>& humans, std::vector<Zombie*>& zombies);

    void draw(Engine::SpriteBatch& spriteBatch);

private:
    glm::vec2 _position;
    glm::vec2 _direction;
    float _damage;
    float _speed;
};


