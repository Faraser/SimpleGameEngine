#include "Ball.h"

Ball::Ball(float radius_, float mass_, const glm::vec2& pos_, const glm::vec2& vel_, unsigned int textureId_,
           const Engine::ColorRGBA8& color_) :
    radius(radius_),
    mass(mass_),
    position(pos_),
    velocity(vel_),
    textureId(textureId_),
    color(color_) {}
