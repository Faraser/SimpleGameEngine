#pragma once

#include "string"
#include "vector"
#include "glm/glm.hpp"

#include "../Engine/SpriteBatch.h"

class Level {
public:
    Level(const std::string &fileName);

    ~Level();

    void draw();

private:
    std::vector<std::string> _levelData;
    int _numHumans;
    Engine::SpriteBatch _spriteBatch;

    glm::ivec2 _startPlayerPosition;
    std::vector<glm::ivec2> _zombieStartPosition;
};

