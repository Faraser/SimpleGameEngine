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

    glm::vec2 getStartPlayerPos() const { return _startPlayerPosition; }

    const std::vector<glm::vec2> &getZombieStartPositions() const { return _zombieStartPosition; };

private:
    std::vector<std::string> _levelData;
    int _numHumans;
    Engine::SpriteBatch _spriteBatch;

    glm::vec2 _startPlayerPosition;
    std::vector<glm::vec2> _zombieStartPosition;
};

