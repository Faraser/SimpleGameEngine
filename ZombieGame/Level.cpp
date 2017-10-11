#include "Level.h"
#include "fstream"
#include "iostream"
#include "../Engine/Errors.h"
#include "../Engine/ResourceManager.h"


Level::Level(const std::string& fileName) {
    std::ifstream file;
    file.open(fileName);

    if (file.fail()) {
        Engine::fatalError("Failed to open " + fileName);
    }

    // Throw away first string in tmp
    std::string tmp;
    file >> tmp >> _numHumans;

    // Throw away first line
    std::getline(file, tmp);

    while (std::getline(file, tmp)) {
        _levelData.push_back(tmp);
    }

    _spriteBatch.init();
    _spriteBatch.begin();

    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    Engine::ColorRGBA8 whiteColor = {255, 255, 255, 255};

    // Render all the tiles
    for (int y = 0; y < _levelData.size(); y++) {
        for (int x = 0; x < _levelData[y].size(); x++) {
            // Grab the tile
            char tile = _levelData[y][x];

            // Get destRect
            glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

            // Process the tile
            switch (tile) {
                case 'B':
                case 'R':
                    _spriteBatch.draw(
                            destRect,
                            uvRect,
                            Engine::ResourceManager::getTexture("Textures/red_bricks.png").id,
                            0.0f,
                            whiteColor
                    );
                    break;
                case 'G':
                    _spriteBatch.draw(
                            destRect,
                            uvRect,
                            Engine::ResourceManager::getTexture("Textures/glass.png").id,
                            0.0f,
                            whiteColor
                    );
                    break;
                case 'L':
                    _spriteBatch.draw(
                            destRect,
                            uvRect,
                            Engine::ResourceManager::getTexture("Textures/light_bricks.png").id,
                            0.0f,
                            whiteColor
                    );
                    break;
                case '@':
                    _levelData[y][x] = '.'; // Don't collide
                    _startPlayerPosition.x = x * TILE_WIDTH;
                    _startPlayerPosition.y = y * TILE_WIDTH;
                    break;
                case 'Z':
                    _levelData[y][x] = '.'; // Don't collide
                    _zombieStartPosition.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
                    break;
                case '.':
                case '\n':
                case '\r':
                    break;
                default:
                    std::cout << "Unexpected symbol " << tile << " at (" << x << ", " << y << ")" << std::endl;
                    break;

            }
        }
    }

    _spriteBatch.end();
}

Level::~Level() {

}

void Level::draw() {
    _spriteBatch.renderBatch();
}
