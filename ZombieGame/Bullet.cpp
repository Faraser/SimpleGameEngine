#include "Bullet.h"
#include "Level.h"
#include "Agent.h"

#include "../Engine/ResourceManager.h"

Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float damage, float speed) :
        _position(position),
        _direction(direction),
        _damage(damage),
        _speed(speed) {

}

Bullet::~Bullet() {

}

bool Bullet::update(const std::vector<std::string>& levelData) {
    _position += _direction * _speed;

    return collideWithWorld(levelData);
}

void Bullet::draw(Engine::SpriteBatch& spriteBatch) {
    glm::vec4 destRect(_position.x + BULLET_RADIUS, _position.y + BULLET_RADIUS, BULLET_RADIUS * 2, BULLET_RADIUS * 2);

    const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

    Engine::Color color = {0, 0, 0, 255};

    spriteBatch.draw(destRect, uvRect, Engine::ResourceManager::getTexture("Textures/circle.png").id, 0.0f, color);
}

bool Bullet::collideWithAgent(Agent* agent) {
    const float MIN_DISTANCE = AGENT_RADIUS + BULLET_RADIUS;

    glm::vec2 centerPosA = _position;
    glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_WIDTH / 2);

    glm::vec2 distVec = centerPosA - centerPosB;

    float distance = glm::length(distVec);

    float collisionDepth = MIN_DISTANCE - distance;

    if (collisionDepth > 0) {
        return true;
    }

    return false;
}

bool Bullet::collideWithWorld(const std::vector<std::string>& levelData) {
    glm::ivec2 gridPosition(floor(_position.x / (float) TILE_WIDTH), floor(_position.y / (float) TILE_WIDTH));

    // If agent is outside the world, just return
    if (gridPosition.x < 0 || gridPosition.x >= levelData[0].size() ||
        gridPosition.y < 0 || gridPosition.y >= levelData.size()) {
        return true;
    }

    return levelData[gridPosition.y][gridPosition.x] != '.';
}
