#include "Sprite.h"
#include "Vertex.h"
#include "cstddef"
#include "string"
#include "ResourceManager.h"
#include "OpenGL/gl3.h"

namespace Engine {
    Sprite::Sprite() {
        _vboID = 0;
    }

    Sprite::~Sprite() {
        if (_vboID != 0) {
            glDeleteBuffers(1, &_vboID);
        }
    }

    void Sprite::init(float x, float y, float width, float height, const std::string &texturePath) {
        _x = x;
        _y = y;
        _width = width;
        _height = height;

        _texture = ResourceManager::getTexture(texturePath);

        if (_vboID == 0) {
            glGenBuffers(1, &_vboID);
        }

        Vertex vertexData[6];

        // first triangle
        vertexData[0].setPosition(x + width, y + height);
        vertexData[0].setUV(1.0f, 1.0f);

        vertexData[1].setPosition(x, y);
        vertexData[1].setUV(0.0f, 0.0f);

        vertexData[2].setPosition(x, y + height);
        vertexData[2].setUV(0.0f, 1.0f);

        // second triangle
        vertexData[3].setPosition(x, y);
        vertexData[3].setUV(0.0f, 0.0f);

        vertexData[4].setPosition(x + width, y);
        vertexData[4].setUV(1.0f, 0.0f);

        vertexData[5].setPosition(x + width, y + height);
        vertexData[5].setUV(1.0f, 1.0f);

        for (int i = 0; i < 6; i++) {
            vertexData[i].setColor(255, 0, 255, 255);
        }

        vertexData[0].color.r = 0;
        vertexData[5].color.r = 0;

        glBindBuffer(GL_ARRAY_BUFFER, _vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

        // Unbind buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Sprite::draw() {

        glBindTexture(GL_TEXTURE_2D, _texture.id);

        glBindBuffer(GL_ARRAY_BUFFER, _vboID);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}