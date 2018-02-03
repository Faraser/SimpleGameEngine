#include "MainGame.h"

#include <Engine/Engine.h>
#include <random>
#include <Engine/ResourceManager.h>

const float DESIRED_FPS = 60.0f;
const int MAX_PHYSICS_STEPS = 6;
const float MS_PER_SECOND = 1000;
const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS;
const float MAX_DELTA_TIME = 1.0f;

MainGame::~MainGame() {}

void MainGame::run() {
    init();
    initBalls();

    Uint32 previousTicks = SDL_GetTicks();

    // Game loop
    while (m_gameState == GameState::RUNNING) {
        m_fpsLimiter.begin();
        processInput();

        // Calculate the frameTime in milliseconds
        Uint32 newTicks = SDL_GetTicks();
        Uint32 frameTime = newTicks - previousTicks;
        previousTicks = newTicks;

        float totalDeltaTime = static_cast<float>(frameTime) / DESIRED_FRAMETIME;

        int i = 0; // This counter makes sure we don't spiral to death!
        // Loop while we still have steps to process
        while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS) {
            // The deltaTime should be the smaller of the totalDeltaTime and MAX_DELTA_TIME
            float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);

            update(deltaTime);

            totalDeltaTime -= deltaTime;

            i++;
        }

        m_camera.update();
        draw();
        m_fps = m_fpsLimiter.end();
    }
}

void MainGame::init() {
    Engine::init();

    m_screenWidth = 1024;
    m_screenHeight = 768;

    m_window.create("Ball Game", m_screenWidth, m_screenHeight, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    m_camera.init(m_screenWidth, m_screenHeight);

    // Point the camera to the center of the screen
    m_camera.setPosition(glm::vec2(m_screenWidth / 2.0f, m_screenHeight / 2.0f));

    m_spriteBatch.init();

    m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
    m_textureProgram.addAttribute("vertexPosition");
    m_textureProgram.addAttribute("vertexColor");
    m_textureProgram.addAttribute("vertexUV");
    m_textureProgram.linkShaders();

    m_fpsLimiter.setMaxFPS(60.0f);

    initRenderers();
}

void MainGame::initRenderers() {
    m_ballRenderers.push_back(std::make_unique<BallRenderer>());
}

struct BallSpawn {
    BallSpawn(const Engine::ColorRGBA8& color_,
              float radius_,
              float mass_,
              float minSpeed_, float maxSpeed_,
              float probability_) :
            color(color_),
            radius(radius_),
            mass(mass_),
            randSpeed(minSpeed_, maxSpeed_),
            probability(probability_) {}

    Engine::ColorRGBA8 color;
    float radius;
    float mass;
    float probability;
    std::uniform_real_distribution<float> randSpeed;
};

void MainGame::initBalls() {
    m_grid = std::make_unique<Grid>(m_screenWidth, m_screenHeight, CELL_SIZE);

    const int NUM_BALLS = 1000;

    std::mt19937 randomEngine(static_cast<unsigned int>(time(nullptr)));
    std::uniform_real_distribution<float> randX(0.0f, static_cast<float>(m_screenWidth));
    std::uniform_real_distribution<float> randY(0.0f, static_cast<float>(m_screenHeight));
    std::uniform_real_distribution<float> randDir(-1.0f, 1.0f);

    std::uniform_int_distribution<int> randColor(0, 255);
    std::uniform_real_distribution<float> randRM(2.0f, 6.0f);


    // Add all possible balls
    std::vector<BallSpawn> possibleBalls;
    float totalProbability = 0.0f;

    auto addBall = [&](float probability, auto... args) {
        totalProbability += probability;
        possibleBalls.emplace_back(args...);
    };

    for (int i = 0; i < 1000; i++) {
        addBall(1.0f,
                Engine::ColorRGBA8(randColor(randomEngine), randColor(randomEngine), randColor(randomEngine), 255),
                randRM(randomEngine), randRM(randomEngine), 0.0f, 0.0f, totalProbability);
    }


    // Random probability for ball spawn
    std::uniform_real_distribution<float> spawn(0.0f, totalProbability);

    m_balls.reserve(NUM_BALLS);

    // Set up ball to spawn with default value
    BallSpawn* ballToSpawn = &possibleBalls.front();

    for (int i = 0; i < NUM_BALLS; i++) {
        // Get the ball spawn roll
        float spawnVal = spawn(randomEngine);
        for (auto& possibleBall : possibleBalls) {
            if (spawnVal <= possibleBall.probability) {
                ballToSpawn = &possibleBall;
                break;
            }
        }

        // Get the random starting position
        glm::vec2 pos(randX(randomEngine), randY(randomEngine));


        // Get the random direction
        glm::vec2 direction(randDir(randomEngine), randY(randomEngine));
        if (direction.x != 0.0f || direction.y != 0.0f) {
            direction = glm::normalize(direction);
        } else {
            direction = glm::vec2(1.0f, 0.0f); // default direction
        }

        // Add ball
        m_balls.emplace_back(ballToSpawn->radius,
                             ballToSpawn->mass,
                             pos,
                             direction * ballToSpawn->randSpeed(randomEngine),
                             Engine::ResourceManager::getTexture("Textures/circle.png").id,
                             ballToSpawn->color);

        m_grid->addBall(&m_balls.back());
    }
}

void MainGame::update(float deltaTime) {
    m_ballController.updateBalls(m_balls, m_grid.get(), deltaTime, m_screenWidth, m_screenHeight);
}

void MainGame::draw() {
    glClearDepth(1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glActiveTexture(GL_TEXTURE0);

    // Grab the camera matrix
    glm::mat4 projectionMatrix = m_camera.getCameraMatrix();

    m_ballRenderers[m_currentRenderer]->renderBalls(m_spriteBatch, m_balls, projectionMatrix);

    m_textureProgram.use();

//    // Make sure the shader uses texture 0
//    GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
//    glUniform1i(textureUniform, 0);
//
//    GLint pUniform = m_textureProgram.getUniformLocation("P");
//    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
//
//    m_textureProgram.unuse();

    m_window.swapBuffer();
}

void MainGame::processInput() {
    m_inputManager.update();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                m_ballController.onMouseMove(m_balls,
                                             static_cast<float>(event.motion.x),
                                             static_cast<float>(m_screenHeight) - static_cast<float>(event.motion.y));
                m_inputManager.setMouseCoords(static_cast<float>(event.motion.x), static_cast<float>(event.motion.y));
                break;
            case SDL_KEYDOWN:
                m_inputManager.pressKey(static_cast<unsigned int>(event.key.keysym.sym));
                break;
            case SDL_KEYUP:
                m_inputManager.releaseKey(static_cast<unsigned int>(event.key.keysym.sym));
                break;
            case SDL_MOUSEBUTTONDOWN:
                m_ballController.onMouseDown(m_balls,
                                             static_cast<float>(event.button.x),
                                             static_cast<float>(m_screenHeight) - static_cast<float>(event.button.y));
                m_inputManager.releaseKey(event.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                m_ballController.onMouseUp(m_balls);
                m_inputManager.releaseKey(event.button.button);
                break;
        }
    }

    if (m_inputManager.isKeyPressed(SDLK_ESCAPE)) {
        m_gameState = GameState::EXIT;
    }

    // Handle gravity changes
    if (m_inputManager.isKeyPressed(SDLK_LEFT)) {
        m_ballController.setGravityDirection(GravityDirection::LEFT);
    } else if (m_inputManager.isKeyPressed(SDLK_RIGHT)) {
        m_ballController.setGravityDirection(GravityDirection::RIGHT);
    } else if (m_inputManager.isKeyPressed(SDLK_UP)) {
        m_ballController.setGravityDirection(GravityDirection::UP);
    } else if (m_inputManager.isKeyPressed(SDLK_DOWN)) {
        m_ballController.setGravityDirection(GravityDirection::DOWN);
    } else if (m_inputManager.isKeyPressed(SDLK_SPACE)) {
        m_ballController.setGravityDirection(GravityDirection::NONE);
    }

    // Switch renderers
    if (m_inputManager.isKeyPressed(SDLK_1)) {
        m_currentRenderer++;
        if (m_currentRenderer >= static_cast<int>(m_ballRenderers.size())) {
            m_currentRenderer = 0;
        }
    }

}

