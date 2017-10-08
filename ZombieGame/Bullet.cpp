#include "Bullet.h"
#include "../Engine/ResourceManager.h"

Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float damage, float speed) :
    _position(position),
    _direction(direction),
    _damage(damage),
    _speed(speed)
{

}

Bullet::~Bullet() {

}

void Bullet::update(std::vector<Human*>& humans, std::vector<Zombie*>& zombies) {
    _position += _direction * _speed;
}

void Bullet::draw(Engine::SpriteBatch& spriteBatch) {
    glm::vec4 destRect(_position.x + BULLET_RADIUS, _position.y + BULLET_RADIUS, BULLET_RADIUS * 2, BULLET_RADIUS * 2);

    const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

    Engine::Color color = {75, 75, 75, 255};

    spriteBatch.draw(destRect, uvRect, Engine::ResourceManager::getTexture("Textures/circle.png").id, 0.0f, color);
}
