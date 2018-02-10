#include "GLSLprogram.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <OpenGL/gl3.h>

#include "EngineErrors.h"
#include "IOManager.h"

namespace Engine {
GLSLprogram::GLSLprogram() :
        _programID(0),
        _vertexShaderID(0),
        _fragmentShaderID(0),
        _numAttributes(0) {

}

GLSLprogram::~GLSLprogram() {

}

void GLSLprogram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
    std::string vertSource;
    std::string fragSource;

    IOManager::readFileToBuffer(vertexShaderFilePath, vertSource);
    IOManager::readFileToBuffer(fragmentShaderFilePath, fragSource);

    compileShadersFromSource(vertSource.c_str(), fragSource.c_str());
};

void GLSLprogram::compileShadersFromSource(const char* vertexSource, const char* fragmentSource) {
    _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (_vertexShaderID == 0) {
        fatalError("Vertex shader failed to be created");
    }

    _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (_fragmentShaderID == 0) {
        fatalError("Fragment shader failed to be created");
    }

    compileShader(vertexSource, "Vertex shader", _vertexShaderID);
    compileShader(fragmentSource, "Fragment shader", _fragmentShaderID);

};

void GLSLprogram::compileShader(const char* source, const std::string& name, GLuint id) {
    std::cout << "Shader code: " << source << std::endl;

    glShaderSource(id, 1, &source, nullptr);

    glCompileShader(id);

    GLint isCompiled = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> errorLog(maxLength);
        glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

        glDeleteShader(id);

        std::printf("%s\n", &errorLog[0]);
        fatalError("Shader " + name + "failed to compile");
    }
}

void GLSLprogram::linkShaders() {
    _programID = glCreateProgram();

    glAttachShader(_programID, _vertexShaderID);
    glAttachShader(_programID, _fragmentShaderID);

    glLinkProgram(_programID);

    GLint isLinked = 0;
    glGetProgramiv(_programID, GL_LINK_STATUS, (int*) &isLinked);

    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> errorLog(maxLength);
        glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

        glDeleteProgram(_programID);

        glDeleteShader(_vertexShaderID);
        glDeleteShader(_fragmentShaderID);

        std::printf("%s\n", &errorLog[0]);
        fatalError("Shaders failed to link");

    }

    glDetachShader(_programID, _vertexShaderID);
    glDetachShader(_programID, _fragmentShaderID);

    glDeleteShader(_vertexShaderID);
    glDeleteShader(_fragmentShaderID);
};

void GLSLprogram::addAttribute(const std::string& attributeName) {
    glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
};

void GLSLprogram::use() {
    glUseProgram(_programID);
    for (int i = 0; i < _numAttributes; i++) {
        glEnableVertexAttribArray(i);
    }
}

void GLSLprogram::unuse() {
    glUseProgram(0);
    for (int i = 0; i < _numAttributes; i++) {
        glDisableVertexAttribArray(i);
    }
}


GLint GLSLprogram::getUniformLocation(const std::string& uniformName) {
    GLint location = glGetUniformLocation(_programID, uniformName.c_str());
    if (location == GL_INVALID_INDEX) {
        fatalError("Uniform " + uniformName + " no found in shader");
    }
    return location;
}

void GLSLprogram::dispose() {
    if (_programID) glDeleteProgram(_programID);
}

}
