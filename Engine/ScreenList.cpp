#include "ScreenList.h"

namespace Engine {

ScreenList::ScreenList(IMainGame* game) : m_game(game) {}

ScreenList::~ScreenList() {
    destroy();
}

IGameScreen* ScreenList::moveNext() {
    IGameScreen* currentScreen = getCurrent();
    if (currentScreen->getNextScreenIndex() != -1) {
        m_currentScreenIndex = currentScreen->getNextScreenIndex();
    }
    return getCurrent();
}

IGameScreen* ScreenList::movePrevious() {
    IGameScreen* currentScreen = getCurrent();
    if (currentScreen->getPreviosScreenIndex() != -1) {
        m_currentScreenIndex = currentScreen->getPrevousScreenIndex();
    }
    return getCurrent();
}

IGameScreen* ScreenList::getCurrent() {
    if (m_currentScreenIndex == -1) return nullptr;
    return m_screens[m_currentScreenIndex];
}

void ScreenList::setScreen(int nextScreen) {
    m_currentScreenIndex = nextScreen;
}

void ScreenList::addScreen(IGameScreen* newScreen) {
    m_screens.push_back(newScreen);
    newScreen->build();
    newScreen->setParentGame(m_game);
}

void ScreenList::destroy() {
    for (size_t i=0; i<m_screens.size(); i++) {
        m_screens[i]->destroy();
        delete m_screens[i];
    }
    m_screens.resize(0);
    m_currentScreenIndex = -1;
}

}

