#pragma once

#include "glm/glm.hpp"
#include "../Engine/SpriteBatch.h"
#include "../Engine/Vertex.h"

const float AGENT_WIDTH = 60;

class Agent {
public:
    Agent();

    virtual ~Agent();

    virtual void update() = 0;

    void draw(Engine::SpriteBatch &spriteBatch);

    glm::vec2 getPosition() const { return _position; };

protected:
    glm::vec2 _position;
    float _speed;
    Engine::Color _color;
};

