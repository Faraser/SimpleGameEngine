#include "Zombie.h"
#include "Human.h"

Zombie::Zombie() {

}

Zombie::~Zombie() {

}

void Zombie::update(
        const std::vector<std::string>& levelData,
        std::vector<Human*>& humans,
        std::vector<Zombie*>& zombies,
        float deltaTime
) {
    Human* closestHuman = getNearestHuman(humans);
    if (closestHuman != nullptr) {
        glm::vec2 direction = glm::normalize(closestHuman->getPosition() - _position);
        _position += direction * _speed * deltaTime;
    }

    collideWithLevel(levelData);
}

void Zombie::init(float speed, glm::vec2 position) {
    _speed = speed;
    _position = position;
    _color = {0, 160, 0, 255};
    _health = 150;
}

Human* Zombie::getNearestHuman(std::vector<Human*>& humans) {
    Human* closestHuman = nullptr;
    float smallestDistance = 9999999.0f;

    for (int i = 0; i < humans.size(); i++) {
        glm::vec2 distVec = humans[i]->getPosition() - _position;
        float distance = glm::length(distVec);

        if (distance < smallestDistance) {
            smallestDistance = distance;
            closestHuman = humans[i];
        }
    }
    return closestHuman;
}
