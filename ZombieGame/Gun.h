#pragma once

#include <string>
#include <glm/glm.hpp>
#include <vector>

#include "Bullet.h"
#include "Engine/AudioEngine.h"

class Gun {
public:
    Gun(std::string name, int fireRate, int bulletsPerShot, float spread,
        float bulletDamage, float bulletSpeed, Engine::SoundEffect fireEffect);

    ~Gun();

    void update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets,
                float deltaTime);

private:
    void fire(const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets);

    std::string _name;

    int _fireRate;

    int _bulletsPerShot;
    float _bulletSpeed;
    float _bulletDamage;

    float _spread; // Accuracy

    float _frameCounter;

    Engine::SoundEffect _fireEffect;
};
