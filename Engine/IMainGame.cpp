#include "IMainGame.h"
#include "Timing.h"
#include "Engine.h"

namespace Engine {

IMainGame::IMainGame() {}

IMainGame::~IMainGame() {}

void IMainGame::run() {
    if (!init()) return;

    FpsLimiter limiter;
    limiter.setMaxFPS(60.0f);

    m_isRunning = true;
    while (m_isRunning)  {
        limiter.begin();

        update();
        draw();

        m_fps = limiter.end();
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

    initSystems();

    onInit();
}

bool IMainGame::initSystems() {
    m_window.create("Default", 1024, 768, 0);
}

}