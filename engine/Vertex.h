#pragma once

#include "OpenGL/OpenGL.h"

struct Position {
    float x;
    float y;
};

struct Color {
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
};

struct UV {
    float u;
    float v;
};

struct Vertex {
    Position position;
    Color color;
    UV uv;

    void setPosition(float x, float y) {
        position = {x, y};
    }

    void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
        color = {r, g, b, a};
    }

    void setUV(float u, float v) {
        uv = {u, v};
    }
};

