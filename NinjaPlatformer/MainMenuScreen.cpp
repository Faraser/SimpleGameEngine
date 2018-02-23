#include "MainMenuScreen.h"
#include "ScreenIndices.h"

MainMenuScreen::MainMenuScreen(Engine::Window* window) : m_window(window) {
    m_screenIndex = SCREEN_INDEX_MAINMENU;
}

MainMenuScreen::~MainMenuScreen() {

}

void MainMenuScreen::build() {

}

void MainMenuScreen::destroy() {

}

void MainMenuScreen::onEntry() {
    initUI();
    // Init camera
    m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
    m_camera.setScale(32.0f);
}

void MainMenuScreen::onExit() {
    m_gui.destroy();
}

void MainMenuScreen::update() {
    m_camera.update();
    checkInput();
}

void MainMenuScreen::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

    m_gui.draw();
}

int MainMenuScreen::getNextScreenIndex() const {
    return SCREEN_INDEX_GAMEPLAY;
}

int MainMenuScreen::getPreviousScreenIndex() const {
    return SCREEN_INDEX_NO_SCREEN;
}

void MainMenuScreen::checkInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        m_gui.onSDLEvent(event);
    }
}

void MainMenuScreen::initUI() {
    m_gui.init("GUI");
    m_gui.loadScheme("TaharezLook.scheme");
    m_gui.setFont("DejaVuSans-10");
    auto exitButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button",
                                                                         glm::vec4(0.45f, 0.55f, 0.1f, 0.05f),
                                                                         glm::vec4(0.0f), "ExitButton"));
    exitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
                               CEGUI::Event::Subscriber(&MainMenuScreen::onExitButtonClicked, this));

    exitButton->setText("Exit Game");

    auto newGameButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button",
                                                                            glm::vec4(0.45f, 0.45f, 0.1f, 0.05f),
                                                                            glm::vec4(0.0f), "NewGameButton"));
    newGameButton->subscribeEvent(CEGUI::PushButton::EventClicked,
                                  CEGUI::Event::Subscriber(&MainMenuScreen::onNewGameButtonClicked, this));
    newGameButton->setText("New Game");

    m_gui.setMouseCursor("TaharezLook/MouseArrow");
    m_gui.showMouseCursor();
}

bool MainMenuScreen::onExitButtonClicked(const CEGUI::EventArgs& e) {
    m_currentState = Engine::ScreenState::EXIT_APPLICATION;
    return false;
}

bool MainMenuScreen::onNewGameButtonClicked(const CEGUI::EventArgs& e) {
    m_currentState = Engine::ScreenState::CHANGE_NEXT;
    return false;
}

