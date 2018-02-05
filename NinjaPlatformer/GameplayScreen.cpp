#include "GameplayScreen.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <Engine/IMainGame.h>
#include <OpenGL/gl3.h>

GameplayScreen::GameplayScreen() {

}

GameplayScreen::~GameplayScreen() {

}

void GameplayScreen::build() {

}

void GameplayScreen::destroy() {

}

void GameplayScreen::onEntry() {
    std::cout << "on entry" << std::endl;
}

void GameplayScreen::onExit() {

}

void GameplayScreen::update() {
    std::cout << "update" << std::endl;
    checkInput();
}

void GameplayScreen::draw() {
    std::cout << "draw" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

int GameplayScreen::getNextScreenIndex() const {
    return -1;
}

int GameplayScreen::getPreviousScreenIndex() const {
    return -1;
}

void GameplayScreen::checkInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        m_game->onSDLEvent(event);
    }

}

