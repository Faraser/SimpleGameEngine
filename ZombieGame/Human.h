#pragma once

#include "Agent.h"
#include "../Engine/InputManager.h"

class Human : public Agent {
public:
    Human();
    virtual ~Human();

    virtual void update();
};
