#pragma once

#include "OpenGL/OpenGL.h"

namespace Engine {
struct Position {
    float x;
    float y;
};

struct ColorRGBA8 {
    ColorRGBA8() : r(0), g(0), b(0), a(0) {};
    ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : r(R), g(G), b(B), a(A) {};

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
    ColorRGBA8 color;
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
}
