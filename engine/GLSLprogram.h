#pragma once

#include "OpenGL/OpenGL.h"
#include "string"

class GLSLprogram {
public:
    GLSLprogram();

    ~GLSLprogram();

    void compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);

    void linkShaders();

    void addAttribute(const std::string &attributeName);

    GLint getUniformLocation(const std::string &uniformName);

    void use();

    void unuse();

private:
    void compileShader(const std::string &filePath, GLuint id);

    GLuint _programID;

    GLuint _vertexShaderID;
    GLuint _fragmentShaderID;

    int _numAttributes;
};

