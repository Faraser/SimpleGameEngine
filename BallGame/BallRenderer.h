#pragma once

#include <Engine/SpriteBatch.h>
#include "Ball.h"

class BallRenderer {
public:
    void renderBall(Engine::SpriteBatch& spriteBatch, Ball& ball);
};


