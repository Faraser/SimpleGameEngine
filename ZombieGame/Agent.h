#pragma once

#include "glm/glm.hpp"
#include "../Engine/SpriteBatch.h"
#include "../Engine/Vertex.h"

const float AGENT_WIDTH = 60.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class Zombie;

class Human;

class Agent {
public:
    Agent();

    virtual ~Agent();

    virtual void update(
            const std::vector<std::string>& levelData,
            std::vector<Human*>& humans,
            std::vector<Zombie*>& zombies,
            float deltaTime
    ) = 0;

    bool collideWithLevel(const std::vector<std::string>& levelData);

    bool collideWithAgent(Agent* agent);

    void draw(Engine::SpriteBatch& spriteBatch);

    glm::vec2 getPosition() const { return _position; };

    // Return true if agent die
    bool applyDamage(float damage);

protected:
    void checkTilePosition(
            const std::vector<std::string>& levelData,
            std::vector<glm::vec2>& collideTilePositions,
            float x,
            float y
    );

    void collideWithTile(glm::vec2 tilePos);

    glm::vec2 _position;
    Engine::ColorRGBA8 _color;
    float _speed;
    float _health;
};

