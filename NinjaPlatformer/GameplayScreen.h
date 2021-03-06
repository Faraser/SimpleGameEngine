#pragma once

#include <Engine/IGameScreen.h>
#include <Engine/SpriteBatch.h>
#include <Engine/GLSLprogram.h>
#include <Engine/Camera2D.h>
#include <Engine/GLTexture.h>
#include <Engine/Window.h>
#include <Engine/DebugRenderer.h>
#include <Engine/GUI.h>

#include <Box2D/Box2D.h>
#include <vector>

#include "Box.h"
#include "Player.h"

class GameplayScreen : public Engine::IGameScreen {

public:
    GameplayScreen(Engine::Window* window);

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

    void initUI();

    bool onExitClicked(const CEGUI::EventArgs& e);

    Engine::GLSLprogram m_textureProgram;
    Engine::GLSLprogram m_lightProgram;
    Engine::SpriteBatch m_spriteBatch;
    Engine::Camera2D m_camera;
    Engine::GLTexture m_texture;
    Engine::Window* m_window;
    Engine::DebugRenderer m_debugRenderer;
    Engine::GUI m_gui;

    bool m_renderDebug = false;

    Player m_player;

    std::vector<Box> m_boxes;
    std::unique_ptr<b2World> m_world;
};


