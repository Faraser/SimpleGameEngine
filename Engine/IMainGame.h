#pragma once

#include <memory>
#include "ScreenList.h"
#include "IGameScreen.h"
#include "Window.h"
#include "InputManager.h"

namespace Engine {

class IMainGame {
public:
    IMainGame();
    virtual ~IMainGame();

    void run();
    void exitGame();

    virtual void onInit() = 0;
    virtual void addScreens() = 0;
    virtual void onExit() = 0;


    const float getFps() const { return m_fps; }

protected:
    // Custom update function
    virtual void update();
    // Custom render function
    virtual void draw();

    void onSDLEvent(SDL_Event& event);

    bool init();
    bool initSystems();

    std::unique_ptr<ScreenList> m_screenList = nullptr;
    IGameScreen* m_currentScreen = nullptr;
    bool m_isRunning = false;
    float m_fps = 0.0f;
    Window m_window;
    InputManager m_inputManager;
};

}


