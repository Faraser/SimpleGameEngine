#pragma once
#include "Opengl/gl3.h"

struct Vertex {
    struct Position {
        float x;
        float y;
    } position;
    struct Color {
        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
    } color;
};