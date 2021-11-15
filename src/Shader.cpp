#include "Shader.h"

void Shader::compileVertexShader()
{
    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShader, NULL);
    glCompileShader(vs);
}

void Shader::compileFragmentShader()
{
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShader, NULL);
    glCompileShader(fs);
}

void Shader::createShaderProgram()
{
    programId = glCreateProgram();
    glAttachShader(programId, vs);
    glAttachShader(programId, fs);
    glLinkProgram(programId);
}

Shader &Shader::use()
{
    glUseProgram(programId);
    return *this;
}