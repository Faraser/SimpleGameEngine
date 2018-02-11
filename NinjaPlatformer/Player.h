#pragma once

#include <Engine/SpriteBatch.h>
#include <Engine/InputManager.h>
#include <Engine/DebugRenderer.h>
#include <Engine/TileSheet.h>
#include "Capsule.h"

enum class PlayerMoveState { STANDING, RUNNING, PUNCHING, IN_AIR };

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
    Engine::TileSheet m_texture;
    Capsule m_capsule;
    PlayerMoveState m_moveState = PlayerMoveState::STANDING;
    float m_animTime = 0.0f;
    int m_direction = 1; // 1 or -1
    bool m_onGround = false;
    bool m_punching = false;
};


