#include "Human.h"
#include "random"
#include "ctime"

Human::~Human() {

}

Human::Human() {

}

void Human::update(
        const std::vector<std::string>& levelData,
        std::vector<Human*>& humans,
        std::vector<Zombie*>& zombies
) {
    _position += _direction * _speed;

    collideWithLevel(levelData);
}

void Human::init(float speed, glm::vec2 position) {
    static std::mt19937 randomEngine;
    randomEngine.seed(time(nullptr));
    static std::uniform_real_distribution<float> randDir(-1.0f, 1.0f);

    _speed = speed;
    _position = position;

    // Get random direction
    _direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
    if (_direction.length() == 0) {
        _direction = glm::vec2(1.0f, 0.0f);
    }

    _direction = glm::normalize(_direction);
}
