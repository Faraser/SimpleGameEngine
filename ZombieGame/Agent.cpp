#include "Agent.h"

#include "Engine/ResourceManager.h"

#include "Level.h"

Agent::Agent() {

}

Agent::~Agent() {

}

void Agent::draw(Engine::SpriteBatch& spriteBatch) {
    const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

    glm::vec4 destRect;
    destRect.x = _position.x;
    destRect.y = _position.y;
    destRect.z = AGENT_WIDTH;
    destRect.w = AGENT_WIDTH;

    spriteBatch.draw(destRect, uvRect, _textureId, 0.0f, _color, _direction);
}

bool Agent::collideWithLevel(const std::vector<std::string>& levelData) {
    std::vector<glm::vec2> collideTilePositions;

    // Check the four corners
    checkTilePosition(levelData, collideTilePositions, _position.x, _position.y);
    checkTilePosition(levelData, collideTilePositions, _position.x + AGENT_WIDTH, _position.y);
    checkTilePosition(levelData, collideTilePositions, _position.x, _position.y + AGENT_WIDTH);
    checkTilePosition(levelData, collideTilePositions, _position.x + AGENT_WIDTH, _position.y + AGENT_WIDTH);

    for (int i = 0; i < collideTilePositions.size(); i++) {
        collideWithTile(collideTilePositions[i]);
    }

    return !collideTilePositions.empty();
}

bool Agent::collideWithAgent(Agent* agent) {
    const float MIN_DISTANCE = AGENT_RADIUS * 2.0f;

    glm::vec2 centerPosA = _position + glm::vec2(AGENT_WIDTH / 2);
    glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_WIDTH / 2);

    glm::vec2 distVec = centerPosA - centerPosB;

    float distance = glm::length(distVec);

    float collisionDepth = MIN_DISTANCE - distance;

    if (collisionDepth > 0) {
        glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;
        _position += collisionDepthVec / 2.0f;
        agent->_position -= collisionDepthVec / 2.0f;
        return true;
    }

    return false;
}

void Agent::checkTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePositions,
                              float x, float y) {
    glm::vec2 cornerPos = glm::vec2(floor(x / (float) TILE_WIDTH),
                                    floor(y / (float) TILE_WIDTH));

    // If agent is outside the world, just return
    if (cornerPos.x < 0 || cornerPos.x >= levelData[0].size() ||
        cornerPos.y < 0 || cornerPos.y >= levelData.size()) {
        return;
    }

    if (levelData[cornerPos.y][cornerPos.x] != '.') {
        collideTilePositions.push_back(cornerPos * (float) TILE_WIDTH + glm::vec2((float) TILE_WIDTH / 2.0f));
    }
}

// AABB collision
void Agent::collideWithTile(glm::vec2 tilePos) {
    const float TILE_RADIUS = (float) TILE_WIDTH / 2.0f;
    const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

    glm::vec2 centerPlayerPos = _position + glm::vec2(AGENT_RADIUS);
    glm::vec2 distVec = centerPlayerPos - tilePos;

    float xDepth = MIN_DISTANCE - std::abs(distVec.x);
    float yDepth = MIN_DISTANCE - std::abs(distVec.y);

    if (xDepth > 0 && yDepth > 0) {
        if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)) {
            if (distVec.x < 0) {
                _position.x -= xDepth;
            } else {
                _position.x += xDepth;
            }
        } else {
            if (distVec.y < 0) {
                _position.y -= yDepth;
            } else {
                _position.y += yDepth;
            }
        }
    }
}

bool Agent::applyDamage(float damage) {
    _health -= damage;
    if (_health <= 0) return true;
    return false;
}


