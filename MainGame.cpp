#include "MainGame.h"
#include "iostream"

MainGame::MainGame() {
    _window = nullptr;
    _screenWidth = 1024;
    _screenHeight = 768;
    _gameState = GameState::PLAY;
}

void MainGame::run() {
    initSystems();
    gameLoop();
}

void MainGame::initSystems() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL could not initialize! SDL_Error:" << SDL_GetError() << std::endl;
    };

    SDL_Window *_window = SDL_CreateWindow(
            "Game engine",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            _screenWidth,
            _screenHeight,
            SDL_WINDOW_OPENGL
    );

    if (_window == nullptr) {
        std::cout << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
    }
}

void MainGame::gameLoop() {
    while (_gameState != GameState::EXIT) {
        processInput();
    }
}

void MainGame::processInput() {
    SDL_Event evnt;
    while(SDL_PollEvent(&evnt)) {
        switch(evnt.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
        }
    };
}
