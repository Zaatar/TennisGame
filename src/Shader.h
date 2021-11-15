#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <iostream>

class Shader
{
public:
    Shader() = default;
    ~Shader() = default;

    GLuint programId;

    void compileVertexShader();
    void compileFragmentShader();
    void createShaderProgram();

    Shader &use();

private:
    GLuint vs;
    GLuint fs;

    const char *vertexShader =
        "#version 430\n"
        "in vec3 vertexPosition;"
        "uniform mat4 scaleMatrix;"
        "uniform mat4 translationMatrix;"
        "void main() {"
        "   gl_Position = translationMatrix * scaleMatrix * vec4(vertexPosition, 1.0);"
        "}";

    const char *fragmentShader =
        "#version 430\n"
        "out vec4 fragmentColor;"
        "void main() {"
        "   fragmentColor = vec4(1.0f,1.0f,1.0f,1.0f);"
        "}";
};
#endif