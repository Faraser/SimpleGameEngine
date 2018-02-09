#include "Player.h"
#include <Engine/ResourceManager.h>

Player::Player() {

}

Player::~Player() {

}

void Player::init(b2World* world,
                  const glm::vec2& position,
                  const glm::vec2& dimensions,
                  Engine::ColorRGBA8 color) {
    Engine::GLTexture texture = Engine::ResourceManager::getTexture("Assets/blue_ninja.png");
    m_collisionBox.init(world, position, dimensions, texture, color, true, glm::vec4(0.0f, 0.0f, 0.1f, 0.5f));
}

void Player::update() {

}

void Player::draw(Engine::SpriteBatch& spriteBatch) {
    m_collisionBox.draw(spriteBatch);
}

