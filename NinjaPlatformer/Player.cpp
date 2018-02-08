#include "Player.h"

Player::Player() {

}

Player::~Player() {

}

void Player::init(b2World* world,
                  const glm::vec2& position,
                  const glm::vec2& dimensions,
                  Engine::GLTexture texture,
                  Engine::ColorRGBA8 color) {
    m_collisionBox.init(world, position, dimensions, texture, color, true);
}

void Player::update() {

}

void Player::draw(Engine::SpriteBatch& spriteBatch) {
    m_collisionBox.draw(spriteBatch);
}

