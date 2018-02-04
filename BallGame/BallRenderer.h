#pragma once

#include <Engine/SpriteBatch.h>
#include <Engine/GLSLprogram.h>
#include <memory>

#include "Ball.h"

class BallRenderer {
public:
    virtual void renderBalls(Engine::SpriteBatch& spriteBatch,
                             const std::vector<Ball> & balls,
                             const glm::mat4& projectionMatrix);
protected:
    std::unique_ptr<Engine::GLSLprogram> m_program = nullptr;
};

class MomentumBallRenderer : public BallRenderer {
public:
    virtual void renderBalls(Engine::SpriteBatch& spriteBatch,
                             const std::vector<Ball> & balls,
                             const glm::mat4& projectionMatrix) override;

};

class VelocityBallRenderer : public BallRenderer {
public:
    VelocityBallRenderer(int screenWidth, int screenHeight);
    virtual void renderBalls(Engine::SpriteBatch& spriteBatch,
                             const std::vector<Ball> & balls,
                             const glm::mat4& projectionMatrix) override;
private:
    int m_screenWidth;
    int m_screenHeight;

};

class TrippyBallRenderer : public BallRenderer {
public:
    TrippyBallRenderer(int screenWidth, int screenHeight);
    virtual void renderBalls(Engine::SpriteBatch& spriteBatch,
                             const std::vector<Ball> & balls,
                             const glm::mat4& projectionMatrix) override;
private:
    int m_screenWidth;
    int m_screenHeight;
    float m_time = 0.0f;
};
