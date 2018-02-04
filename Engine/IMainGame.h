#pragma once

#include <memory>
#include "ScreenList.h"
#include "IGameScreen.h"
#include "Window.h"

namespace Engine {

class IMainGame {
public:
    IMainGame();
    virtual ~IMainGame();

    void run();
    void exitGame();

    virtual void onInit() = 0;
    virtual void addScreen() = 0;
    virtual void onExit() = 0;

    virtual void update() = 0;
    virtual void draw() = 0;

    const float getFps() const { return m_fps; }

protected:
    bool init();
    bool initSystems();

    std::unique_ptr<ScreenList> m_screenList = nullptr;
    IGameScreen* m_currentScreen = nullptr;
    bool m_isRunning = false;
    float m_fps = 0.0f;
    Window m_window;
};

}


