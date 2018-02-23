#pragma once

#include <Engine/IGameScreen.h>
#include <Engine/Window.h>
#include <Engine/GUI.h>
#include <Engine/Camera2D.h>

class MainMenuScreen : public Engine::IGameScreen {

public:
    MainMenuScreen(Engine::Window* window);

    ~MainMenuScreen();

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

    bool onExitButtonClicked(const CEGUI::EventArgs& e);
    bool onNewGameButtonClicked(const CEGUI::EventArgs& e);

    Engine::Camera2D m_camera;
    Engine::Window* m_window;
    Engine::GUI m_gui;

};




