#pragma once

#include <Engine/SpriteBatch.h>
#include <Engine/GLSLprogram.h>
#include <memory>

#include "Ball.h"

class BallRenderer {
public:
    void renderBalls(Engine::SpriteBatch& spriteBatch, const std::vector<Ball> & balls, const glm::mat4& projectionMatrix);
private:
    std::unique_ptr<Engine::GLSLprogram> m_program = nullptr;
};


