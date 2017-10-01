#include "Bullet.h"
#include "Engine/ResourceManager.h"

Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float speed, int lifeTime) :
        _position(position),
        _direction(direction),
        _speed(speed),
        _lifeTime(lifeTime) {

}

Bullet::~Bullet() {

}

void Bullet::draw(Engine::SpriteBatch &spriteBatch) {
    Engine::Color color = {255, 255, 255, 255};

    static Engine::GLTexture texture = Engine::ResourceManager::getTexture(
            "Textures/red_bricks.png");
    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
    glm::vec4 posAndSize(_position.x, _position.y, 30, 30);

    spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, color);
}

bool Bullet::update() {
    _position += _direction * _speed;
    _lifeTime--;

    return _lifeTime == 0;
}
