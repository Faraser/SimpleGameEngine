#pragma once

#include <Engine/IGameScreen.h>
#include <Engine/SpriteBatch.h>
#include <Engine/GLSLprogram.h>
#include <Engine/Camera2D.h>
#include <Engine/GLTexture.h>
#include <Engine/Window.h>

#include <Box2D/Box2D.h>
#include <vector>

#include "Box.h"
#include "Player.h"

class GameplayScreen : public Engine::IGameScreen {

public:
    GameplayScreen(Engine::Window * window);

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

    Engine::GLSLprogram m_textureProgram;
    Engine::SpriteBatch m_spriteBatch;
    Engine::Camera2D m_camera;
    Engine::GLTexture m_texture;
    Engine::Window * m_window;

    Player m_player;

    std::vector<Box> m_boxes;
    std::unique_ptr<b2World> m_world;
};


