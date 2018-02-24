#include <Engine/ResourceManager.h>
#include "EditorScreen.h"

EditorScreen::EditorScreen(Engine::Window* window) :
        m_window(window),
        m_spriteFont("Fonts/chintzy.ttf", 32) {
    m_screenIndex = SCREEN_INDEX_EDITOR;
}

EditorScreen::~EditorScreen() {

}

void EditorScreen::build() {

}

void EditorScreen::destroy() {

}

void EditorScreen::onEntry() {
    initUI();
    // Init camera
    m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
    m_camera.setScale(1.0f);

    m_spriteBatch.init();

    // Shader initialize
    m_textureProgram.compileShaders("Shaders/colorShading.vert",
                                    "Shaders/colorShading.frag");
    m_textureProgram.addAttribute("vertexPosition");
    m_textureProgram.addAttribute("vertexColor");
    m_textureProgram.addAttribute("vertexUV");
    m_textureProgram.linkShaders();

    m_blankTexture = Engine::ResourceManager::getTexture("Assets/blank.png");
}

void EditorScreen::onExit() {
    m_gui.destroy();
    m_textureProgram.dispose();
}

void EditorScreen::update() {
    m_camera.update();
    checkInput();
}

void EditorScreen::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

    m_textureProgram.use();

    // Upload texture uniform
    GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
    glUniform1i(textureUniform, 0);
    glActiveTexture(GL_TEXTURE0);

    // Camera matrix
    glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
    GLint pUniform = m_textureProgram.getUniformLocation("P");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    m_spriteBatch.begin();

    {   // Draw the color picker quad
        const float QUAD_SIZE = 75.0f;

        glm::vec4 destRect(m_blueSlider->getXPosition().d_scale * m_window->getScreenWidth() + 20.0f -
                           m_window->getScreenWidth() / 2.0f + QUAD_SIZE / 2.0f,
                           m_window->getScreenHeight() / 2.0f -
                           m_blueSlider->getYPosition().d_scale * m_window->getScreenHeight() -
                           m_blueSlider->getHeight().d_scale * m_window->getScreenHeight() * 0.5f - QUAD_SIZE / 2.0f,
                           QUAD_SIZE, QUAD_SIZE);
        m_spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), m_blankTexture.id, 0.0f,
                           Engine::ColorRGBA8((GLubyte) m_colorPickerRed,
                                              (GLubyte) m_colorPickerGreen,
                                              (GLubyte) m_colorPickerBlue,
                                              255));
    }

    {  // Draw labels for rigid and dynamic buttons
        glm::vec2 posRigid(m_rigidRadioButton->getXPosition().d_scale * m_window->getScreenWidth() -
                           m_window->getScreenWidth() / 2.0f + m_rigidRadioButton->getWidth().d_offset / 2.0f,
                           m_window->getScreenHeight() / 2.0f -
                           m_rigidRadioButton->getYPosition().d_scale * m_window->getScreenHeight());
        m_spriteFont.draw(m_spriteBatch, "Rigid", posRigid, glm::vec2(0.7f), 0.0f,
                          Engine::ColorRGBA8(255, 255, 255, 255),
                          Engine::Justification::MIDDLE);

        glm::vec2 posDynamic(m_dynamicRadioButton->getXPosition().d_scale * m_window->getScreenWidth() -
                             m_window->getScreenWidth() / 2.0f + m_dynamicRadioButton->getHeight().d_offset / 2.0f,
                             m_window->getScreenHeight() / 2.0f -
                             m_dynamicRadioButton->getYPosition().d_scale * m_window->getScreenHeight());
        m_spriteFont.draw(m_spriteBatch, "Dynamic", posDynamic, glm::vec2(0.7f), 0.0f,
                          Engine::ColorRGBA8(255, 255, 255, 255),
                          Engine::Justification::MIDDLE);
    }

    m_spriteBatch.end();
    m_spriteBatch.renderBatch();
    m_textureProgram.unuse();

    m_gui.draw();
}

int EditorScreen::getNextScreenIndex() const {
    return SCREEN_INDEX_NO_SCREEN;
}

int EditorScreen::getPreviousScreenIndex() const {
    return SCREEN_INDEX_MAINMENU;
}

void EditorScreen::checkInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        m_gui.onSDLEvent(event);
        switch (event.type) {
            case SDL_QUIT:
                onExitButtonClicked(CEGUI::EventArgs());
                break;
        }
    }
}

void EditorScreen::initUI() {
    m_gui.init("GUI");
    m_gui.loadScheme("TaharezLook.scheme");
    m_gui.setFont("DejaVuSans-10");


    { // Add the color picker
        const float X_DIM = 0.015f, Y_DIM = 0.1f;
        const float X_POS = 0.05f, Y_POS = 0.05f;
        const float PADDING = 0.02f;

        m_redSlider = static_cast<CEGUI::Slider*>(
                m_gui.createWidget("TaharezLook/Slider",
                                   glm::vec4(X_POS, Y_POS, X_DIM, Y_DIM),
                                   glm::vec4(0.0f), "RedSlider"));

        m_redSlider->setMaxValue(255.0f);
        m_redSlider->setCurrentValue(m_colorPickerRed);
        m_redSlider->subscribeEvent(CEGUI::Slider::EventValueChanged,
                                    CEGUI::Event::Subscriber(&EditorScreen::onColorPickerRedChanged, this));
        m_redSlider->setClickStep(1.0f);

        m_greenSlider = static_cast<CEGUI::Slider*>(
                m_gui.createWidget("TaharezLook/Slider",
                                   glm::vec4(X_POS + X_DIM + PADDING, Y_POS, X_DIM, Y_DIM),
                                   glm::vec4(0.0f), "GreenSlider"));

        m_greenSlider->setMaxValue(255.0f);
        m_greenSlider->setCurrentValue(m_colorPickerGreen);
        m_greenSlider->subscribeEvent(CEGUI::Slider::EventValueChanged,
                                      CEGUI::Event::Subscriber(&EditorScreen::onColorPickerGreenChanged, this));
        m_greenSlider->setClickStep(1.0f);

        m_blueSlider = static_cast<CEGUI::Slider*>(
                m_gui.createWidget("TaharezLook/Slider",
                                   glm::vec4(X_POS + (X_DIM + PADDING) * 2, Y_POS, X_DIM, Y_DIM),
                                   glm::vec4(0.0f), "BlueSlider"));

        m_blueSlider->setMaxValue(255.0f);
        m_blueSlider->setCurrentValue(m_colorPickerBlue);
        m_blueSlider->subscribeEvent(CEGUI::Slider::EventValueChanged,
                                     CEGUI::Event::Subscriber(&EditorScreen::onColorPickerBlueChanged, this));
        m_blueSlider->setClickStep(1.0f);
    }

    { // Add the physics mode radio buttons
        const float X_POS = 0.05f, Y_POS = 0.25f;
        const float DIMS_PX = 20.0f;
        const float PADDING = 0.07f;

        m_rigidRadioButton = static_cast<CEGUI::RadioButton*>(
                m_gui.createWidget("TaharezLook/RadioButton",
                                   glm::vec4(X_POS, Y_POS, 0.0f, 0.0f),
                                   glm::vec4(0.0f, 0.0f, DIMS_PX, DIMS_PX), "RigidRadioButton"));

        m_rigidRadioButton->setSelected(true);
        m_rigidRadioButton->subscribeEvent(CEGUI::RadioButton::EventMouseClick,
                                           CEGUI::Event::Subscriber(&EditorScreen::onRigidMouseClicked, this));

        m_dynamicRadioButton = static_cast<CEGUI::RadioButton*>(
                m_gui.createWidget("TaharezLook/RadioButton",
                                   glm::vec4(X_POS + PADDING, Y_POS, 0.0f, 0.0f),
                                   glm::vec4(0.0f, 0.0f, DIMS_PX, DIMS_PX),
                                   "DynamicRadioButton"));
        m_dynamicRadioButton->subscribeEvent(CEGUI::RadioButton::EventMouseClick,
                                             CEGUI::Event::Subscriber(&EditorScreen::onDynamicMouseClicked, this));
    }

    m_gui.setMouseCursor("TaharezLook/MouseArrow");
    m_gui.showMouseCursor();
}

bool EditorScreen::onExitButtonClicked(const CEGUI::EventArgs& e) {
    m_currentState = Engine::ScreenState::EXIT_APPLICATION;
    return true;
}

bool EditorScreen::onColorPickerRedChanged(const CEGUI::EventArgs& e) {
    m_colorPickerRed = m_redSlider->getCurrentValue();
    return true;
}

bool EditorScreen::onColorPickerGreenChanged(const CEGUI::EventArgs& e) {
    m_colorPickerGreen = m_greenSlider->getCurrentValue();
    return true;
}

bool EditorScreen::onColorPickerBlueChanged(const CEGUI::EventArgs& e) {
    m_colorPickerBlue = m_blueSlider->getCurrentValue();
    return true;
}

bool EditorScreen::onRigidMouseClicked(const CEGUI::EventArgs& e) {
    m_physicsMode = PhysicsMode::RIGID;
    return true;
}

bool EditorScreen::onDynamicMouseClicked(const CEGUI::EventArgs& e) {
    m_physicsMode = PhysicsMode::DYNAMIC;
    return true;
}
