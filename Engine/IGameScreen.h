#pragma once

namespace Engine {

enum class ScreenState {
    NONE, RUNNING, EXIT_APPLICATION, CHANGE_NEXT, CHANGE_PREVIOUS
};
class IMainGame;

class IGameScreen {
public:
    friend class ScreenList;

    // Called at beginning and end of application
    virtual void build() = 0;
    virtual void destroy() = 0;

    // Called when a screen enters and exits focus
    virtual void onEntry() = 0;
    virtual void onExit() = 0;

    // Called in the main game loop
    virtual void update() = 0;
    virtual void draw() = 0;

    int getScreenIndex() const { return m_screenIndex; }

    ScreenState getState() const { return m_currentState; }
    void setRunning() { m_currentState = ScreenState::RUNNING; }

    // Return the index of the next of previous screen when changing screens
    virtual int getNextScreenIndex() const = 0;
    virtual int getPreviousScreenIndex() const = 0;

    void setParentGame(IMainGame* game) { m_game = game; };

protected:
    ScreenState m_currentState = ScreenState::NONE;
    IMainGame* m_game = nullptr;
    int m_screenIndex = -1;
};
}


