#pragma once

#include <Engine/IGameScreen.h>

class GameplayScreen : public Engine::IGameScreen {

public:
    GameplayScreen();

    ~GameplayScreen();

    void build() override;

    void destroy() override;

    void onEntry() override;

    void onExit() override;

    void update() override;

    void draw() override;

    int getNextScreenIndex() const override;

    int getPreviousScreenIndex() const override;
private:
    void checkInput();
};


