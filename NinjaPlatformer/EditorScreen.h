#pragma once

#include <Engine/IGameScreen.h>
#include <Engine/Window.h>
#include <Engine/GUI.h>
#include <Engine/Camera2D.h>
#include <Engine/GLSLprogram.h>
#include <Engine/SpriteBatch.h>
#include <Engine/SpriteFont.h>
#include "ScreenIndices.h"

enum class PhysicsMode {
    RIGID, DYNAMIC
};

class EditorScreen : public Engine::IGameScreen {

public:
    EditorScreen(Engine::Window* window);

    ~EditorScreen();

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
    bool onColorPickerRedChanged(const CEGUI::EventArgs& e);
    bool onColorPickerGreenChanged(const CEGUI::EventArgs& e);
    bool onColorPickerBlueChanged(const CEGUI::EventArgs& e);
    bool onRigidMouseClicked(const CEGUI::EventArgs& e);
    bool onDynamicMouseClicked(const CEGUI::EventArgs& e);


    float m_colorPickerRed = 255.0f;
    float m_colorPickerGreen = 255.0f;
    float m_colorPickerBlue = 255.0f;

    CEGUI::Slider* m_redSlider = nullptr;
    CEGUI::Slider* m_greenSlider = nullptr;
    CEGUI::Slider* m_blueSlider = nullptr;
    CEGUI::RadioButton* m_rigidRadioButton = nullptr;
    CEGUI::RadioButton* m_dynamicRadioButton = nullptr;

    Engine::GLSLprogram m_textureProgram;
    Engine::SpriteBatch m_spriteBatch;
    Engine::SpriteFont m_spriteFont;

    Engine::GLTexture m_blankTexture;

    Engine::Camera2D m_camera;
    Engine::Window* m_window;
    Engine::GUI m_gui;

    PhysicsMode m_physicsMode = PhysicsMode::RIGID;
};







