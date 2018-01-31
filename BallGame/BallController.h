#pragma once

#include <vector>
#include "Ball.h"

enum class GravityDirection {
    NONE, LEFT, UP, RIGHT, DOWN
};

class BallController {
public:
    void updateBalls(std::vector<Ball>& balls, float deltaTime, int maxX, int maxY);

    void onMouseDown(std::vector<Ball>& balls, float mouseX, float mouseY);

    void onMouseUp(std::vector<Ball>& balls);

    void onMouseMove(std::vector<Ball>& balls, float mouseX, float mouseY);

    void setGravityDirection(GravityDirection dir) { m_gravityDirection = dir; };

private:
    void checkCollision(Ball& b1, Ball& b2);

    bool isMouseOnBall(Ball&b, float mouseX, float mouseY) const;

    glm::vec2 getGravityAccel() const;

    int m_grabbedBall = -1;
    glm::vec2 m_prevPos = glm::vec2(0.0f);
    glm::vec2 m_grabOffset = glm::vec2(0.0f);

    GravityDirection m_gravityDirection = GravityDirection::NONE;
};


