#pragma once

#include <Engine/SpriteBatch.h>
#include <Engine/InputManager.h>
#include "Box.h"

class Player {
public:
    Player();

    ~Player();

    void init(b2World * world, const glm::vec2& position, const glm::vec2& dimensions, Engine::ColorRGBA8 color);

    void draw(Engine::SpriteBatch & spriteBatch);

    void update(Engine::InputManager& inputManager);

    const Box& getBox() const { return m_collisionBox; }

private:
    Box m_collisionBox;
};


