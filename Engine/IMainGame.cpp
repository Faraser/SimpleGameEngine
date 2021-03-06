#include "IMainGame.h"
#include "Timing.h"
#include "Engine.h"
#include <OpenGL/gl3.h>

namespace Engine {

IMainGame::IMainGame() {
    m_screenList = std::make_unique<ScreenList>(this);
}

IMainGame::~IMainGame() {}

void IMainGame::run() {
    if (!init()) return;

    FpsLimiter limiter;
    limiter.setMaxFPS(60.0f);

    m_isRunning = true;
    while (m_isRunning) {
        limiter.begin();

        inputManager.update();
        update();

        if (m_isRunning) { // If still need drawing
            draw();

            m_fps = limiter.end();
            m_window.swapBuffer();
        }
    }
}

void IMainGame::exitGame() {
    m_currentScreen->onExit();
    if (m_screenList) {
        m_screenList->destroy();
        m_screenList.reset();
    }
    m_isRunning = false;
}

bool IMainGame::init() {
    Engine::init();

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    if (!initSystems()) return false;

    onInit();
    addScreens();

    m_currentScreen = m_screenList->getCurrent();
    m_currentScreen->onEntry();
    m_currentScreen->setRunning();

    return true;
}

bool IMainGame::initSystems() {
    m_window.create("Default", 1024, 768, 0);
    return true;
}

void IMainGame::update() {
    if (m_currentScreen) {
        switch (m_currentScreen->getState()) {
            case ScreenState::RUNNING:
                m_currentScreen->update();
                break;
            case ScreenState::CHANGE_NEXT:
                m_currentScreen->onExit();
                m_currentScreen = m_screenList->moveNext();
                if (m_currentScreen) {
                    m_currentScreen->setRunning();
                    m_currentScreen->onEntry();
                }
                break;
            case ScreenState::CHANGE_PREVIOUS:
                m_currentScreen->onExit();
                m_currentScreen = m_screenList->movePrevious();
                if (m_currentScreen) {
                    m_currentScreen->setRunning();
                    m_currentScreen->onEntry();
                }
                break;
            case ScreenState::EXIT_APPLICATION:
                exitGame();
                break;
            default:
                break;
        }
    } else {
        exitGame();
    }
}

void IMainGame::draw() {
    glViewport(0, 0, m_window.getScreenWidth(), m_window.getScreenHeight());
    if (m_currentScreen && m_currentScreen->getState() == ScreenState::RUNNING) {
        m_currentScreen->draw();
    }
}

void IMainGame::onSDLEvent(SDL_Event& event) {
    switch (event.type) {
        case SDL_QUIT:
            exitGame();
            break;
        case SDL_MOUSEMOTION:
            inputManager.setMouseCoords(static_cast<float>(event.motion.x), static_cast<float>(event.motion.y));
            break;
        case SDL_KEYDOWN:
            inputManager.pressKey(static_cast<unsigned int>(event.key.keysym.sym));
            break;
        case SDL_KEYUP:
            inputManager.releaseKey(static_cast<unsigned int>(event.key.keysym.sym));
            break;
        case SDL_MOUSEBUTTONDOWN:
            inputManager.releaseKey(event.button.button);
            break;
        case SDL_MOUSEBUTTONUP:
            inputManager.releaseKey(event.button.button);
            break;
    }
}

}