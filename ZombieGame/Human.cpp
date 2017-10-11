#include "Human.h"
#include "random"
#include "ctime"
#include "glm/gtx/rotate_vector.hpp"

Human::Human() :
    _frames(0)
{

}

Human::~Human() {

}

void Human::update(
        const std::vector<std::string>& levelData,
        std::vector<Human*>& humans,
        std::vector<Zombie*>& zombies,
        float deltaTime
) {
    static std::mt19937 randomEngine(time(nullptr));
    static std::uniform_real_distribution<float> randRotate(-10.0f, 10.0f);

    _position += _direction * _speed * deltaTime;

    if (_frames == 60) {
        _direction = glm::rotate(_direction, randRotate(randomEngine));
        _frames = 0;
    } else {
        _frames++;
    }

    if (collideWithLevel(levelData)) {
        _direction = glm::rotate(_direction, randRotate(randomEngine));
    };
}

void Human::init(float speed, glm::vec2 position) {
    static std::mt19937 randomEngine(time(nullptr));
    static std::uniform_real_distribution<float> randDir(-0.1f, 0.1f);

    _color = { 200, 0, 200, 255 };
    _speed = speed;
    _position = position;
    _health = 20;

    // Get random direction
    _direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
    if (_direction.length() == 0) {
        _direction = glm::vec2(1.0f, 0.0f);
    }

    _direction = glm::normalize(_direction);
}
