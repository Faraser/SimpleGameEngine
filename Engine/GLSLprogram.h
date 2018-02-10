#pragma once

#include <OpenGL/OpenGL.h>
#include <string>

namespace Engine {
class GLSLprogram {
public:
    GLSLprogram();

    ~GLSLprogram();

    void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

    void compileShadersFromSource(const char* vertexSource, const char* fragmentSource);

    void linkShaders();

    void addAttribute(const std::string& attributeName);

    GLint getUniformLocation(const std::string& uniformName);

    void use();

    void unuse();

    void dispose();

private:
    void compileShader(const char* source, const std::string& name, GLuint id);

    GLuint _programID;

    GLuint _vertexShaderID;
    GLuint _fragmentShaderID;

    int _numAttributes;
};
}
