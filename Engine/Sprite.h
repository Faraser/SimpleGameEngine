#pragma once

#include <OpenGL/OpenGL.h>
#include <string>

#include "GLTexture.h"

namespace Engine {
class Sprite {

public:
    Sprite();

    ~Sprite();

    void init(float x, float y, float width, float height, const std::string& texturePath);

    void draw();

private:
    float _x;
    float _y;
    float _width;
    float _height;
    GLuint _vboID;
    GLTexture _texture;
};
}
