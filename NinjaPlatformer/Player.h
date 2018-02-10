#pragma once

#include <Engine/SpriteBatch.h>
#include <Engine/InputManager.h>
#include <Engine/DebugRenderer.h>
#include <Engine/GLTexture.h>
#include "Capsule.h"

class Player {
public:
    void init(b2World* world,
              const glm::vec2& position,
              const glm::vec2& drawDims,
              const glm::vec2& collisionDim,
              Engine::ColorRGBA8 color);

    void draw(Engine::SpriteBatch& spriteBatch);

    void drawDebug(Engine::DebugRenderer& debugRenderer);

    void update(Engine::InputManager& inputManager);

    const Capsule& getCapsule() const { return m_capsule; }

private:
    glm::vec2 m_drawDims;
    Engine::ColorRGBA8 m_color;
    Engine::GLTexture m_texture;
    Capsule m_capsule;
};


