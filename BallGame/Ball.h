#pragma once

#include <glm/glm.hpp>
#include <Engine/Vertex.h>

struct Ball {
    Ball(float radius_, float mass_, const glm::vec2& pos_, const glm::vec2& vel_, unsigned int textureId_,
         const Engine::ColorRGBA8& color_);

    float radius;
    float mass;
    glm::vec2 velocity;
    glm::vec2 position;
    unsigned int textureId;
    Engine::ColorRGBA8 color;
};


