#include "Player.h"
#include "SDL2/SDL.h"
#include <Engine/ResourceManager.h>
#include <iostream>


void Player::init(b2World* world,
                  const glm::vec2& position,
                  const glm::vec2& drawDims,
                  const glm::vec2& collisionDim,
                  Engine::ColorRGBA8 color) {
    m_texture = Engine::ResourceManager::getTexture("Assets/blue_ninja.png");
    m_color = color;
    m_drawDims = drawDims;
    m_capsule.init(world, position, collisionDim, 1.0f, 0.1f, true);
}

void Player::update(Engine::InputManager& inputManager) {
    b2Body* body = m_capsule.getBody();

    if (inputManager.isKeyDown(SDLK_a)) {
        body->ApplyForceToCenter(b2Vec2(-100.0, 0.0), true);
    } else if (inputManager.isKeyDown(SDLK_d)) {
        body->ApplyForceToCenter(b2Vec2(100.0, 0.0), true);
    } else {
        body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x * 0.9, body->GetLinearVelocity().y));
    }

    // Limited max speed
    const float MAX_SPEED = 10.0f;
    if (body->GetLinearVelocity().x < -MAX_SPEED) {
        body->SetLinearVelocity(b2Vec2(-MAX_SPEED, body->GetLinearVelocity().y));
    } else if (body->GetLinearVelocity().x > MAX_SPEED) {
        body->SetLinearVelocity(b2Vec2(MAX_SPEED, body->GetLinearVelocity().y));
    }

    // Loop through all the contact points
    for (b2ContactEdge* ce = body->GetContactList(); ce != nullptr; ce = ce->next) {
        b2Contact* c = ce->contact;
        if (c->IsTouching()) {
            b2WorldManifold manifold;
            c->GetWorldManifold(&manifold);
            // Check if the points are below
            bool below = false;
            for (int i = 0; i < b2_maxManifoldPoints; i++) {
                if (manifold.points[i].y < body->GetPosition().y - m_capsule.getDimensions().y / 2.0f + m_capsule.getDimensions().x / 2.0f + 0.01f) {
                    below = true;
                    break;
                };
            }
            if (below) {
                // We can jump
                if (inputManager.isKeyPressed(SDLK_w)) {
                    std::cout << "PRESS JUMP" << std::endl;
                    body->ApplyLinearImpulse(b2Vec2(0.0f, 30.0f), b2Vec2(0.0f, 0.0f), true);
                    break; // Jump only once
                }

            }
        }
    }

}

void Player::draw(Engine::SpriteBatch& spriteBatch) {
    glm::vec4 destRect;
    b2Body* body = m_capsule.getBody();

    destRect.x = body->GetPosition().x - m_drawDims.x / 2.0f;
    destRect.y = body->GetPosition().y - m_capsule.getDimensions().y / 2.0f;
    destRect.z = m_drawDims.x;
    destRect.w = m_drawDims.y;

    spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 0.1f, 0.5f), m_texture.id, 0.0f, m_color, body->GetAngle());
}

void Player::drawDebug(Engine::DebugRenderer& debugRenderer) {
    m_capsule.drawDebug(debugRenderer);
}

