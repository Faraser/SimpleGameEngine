#include "MainGame.h"
#include "iostream"
#include "string"
#include "OpenGL/gl3.h"
#include "Errors.h"

MainGame::MainGame() :
        _window(nullptr),
        _screenWidth(1024),
        _screenHeight(768),
        _gameState(GameState::PLAY),
        _time(0.0f),
        _maxFPS(60.0f)
{
}

void MainGame::run() {
    initSystems();

    _sprites.push_back(new Sprite());
    _sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "textures/jimmyJump_pack/PNG/peka.png");

    _sprites.push_back(new Sprite());
    _sprites.back()->init(0.0f, 0.0f, 1.0f, 1.0f, "textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");


//    _playerTexture = ImageLoader::loadPNG("textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
//    _playerTexture = ImageLoader::loadPNG("textures/jimmyJump_pack/PNG/peka.png");

    gameLoop();
}

void MainGame::initSystems() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fatalError("SDL could not initialize!");
    };

    _window = SDL_CreateWindow(
            "Game engine",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            _screenWidth,
            _screenHeight,
            SDL_WINDOW_OPENGL
    );

    if (_window == nullptr) {
        fatalError("Window could not be created!");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    if (glContext == nullptr) {
        fatalError("SDL_GLcontext could not been create");
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    initShaders();
}

void MainGame::gameLoop() {
    while (_gameState != GameState::EXIT) {
        float startTicks = SDL_GetTicks();


        processInput();
        _time += 0.01;
        drawGame();
        calculateFPS();

        static int frameCounter = 0;
        frameCounter++;
        if (frameCounter == 10) {
            std::cout << _fps << std::endl;
            frameCounter = 0;
        }


        float frameTicks = SDL_GetTicks() - startTicks;
        if (1000.0f / _maxFPS > frameTicks) {
           SDL_Delay(1000.0f / _maxFPS - frameTicks);
        }
    }
}

void MainGame::processInput() {
    SDL_Event evnt;
    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                break;
        }
    };
}

void MainGame::drawGame() {
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _colorProgram.use();
    glActiveTexture(GL_TEXTURE0);

    // Send texture to shader
    GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);

//    // Send time to shader
//    GLuint timeLocation = _colorProgram.getUniformLocation("time");
//    glUniform1f(timeLocation, _time);

    for (auto sprite : _sprites) {
        sprite->draw();
    }

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
    _colorProgram.unuse();
    SDL_GL_SwapWindow(_window);
}

void MainGame::initShaders() {
    _colorProgram.compileShaders("shaders/colorShading.vert",
                                 "shaders/colorShading.frag");
    _colorProgram.addAttribute("vertexPosition");
    _colorProgram.addAttribute("vertexColor");
    _colorProgram.addAttribute("vertexUV");
    _colorProgram.linkShaders();
}


void MainGame::calculateFPS() {
    static const int NUM_SAMPLES = 10;
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;

    static float prevTicks = SDL_GetTicks();
    float currentTicks = SDL_GetTicks();

    _frameTime = currentTicks - prevTicks;
    frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;
    prevTicks = currentTicks;

    currentFrame++;
    int count;
    if (currentFrame < NUM_SAMPLES) {
        count = currentFrame;
    } else {
        count = NUM_SAMPLES;
    }

    float frameTimeAverage = 0;
    for (int i = 0; i < count; i++) {
        frameTimeAverage += frameTimes[i];
    }
    frameTimeAverage /= count;

    if (frameTimeAverage > 0) {
        _fps = 1000.0f / frameTimeAverage;
    } else {
        _fps = 60.f;
    }
}
