#pragma once

#include "Human.h"
#include "Gun.h"

#include "Engine/Camera2D.h"

class Player : public Human {
public:
    Player();

    ~Player();

    void init(float speed, glm::vec2 position, Engine::InputManager* inputManager, Engine::Camera2D* camera,
              std::vector<Bullet>* bullets);

    void addGun(Gun* gun);

    void update(
            const std::vector<std::string>& levelData,
            std::vector<Human*>& humans,
            std::vector<Zombie*>& zombies,
            float deltaTime
    ) override;

private:
    Engine::InputManager* _inputManager;
    Engine::Camera2D* _camera;

    std::vector<Gun*> _guns;
    std::vector<Bullet>* _bullets;
    int _currentGunIndex;
};
