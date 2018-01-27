#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {
class Camera2D {
public:
    Camera2D();

    ~Camera2D();

    void update();

    void init(int screenWidth, int screenHeight);

    glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

    void setPosition(const glm::vec2& newPosition) {
        _position = newPosition;
        _needsMatrixUpdate = true;
    }

    void setScale(float newScale) {
        _scale = newScale;
        _needsMatrixUpdate = true;
    }

    glm::vec2 getPosition() { return _position; }

    float getScale() { return _scale; }

    glm::mat4 getCameraMatrix() { return _cameraMatrix; }

    bool isBoxInView(const glm::vec2& position, const glm::vec2& dimensions);

private:
    int _screenWidth;
    int _screenHeight;
    bool _needsMatrixUpdate;
    float _scale;
    glm::vec2 _position;
    glm::mat4 _cameraMatrix;
    glm::mat4 _orthoMatrix;
};
}


