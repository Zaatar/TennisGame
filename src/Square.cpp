#include "Square.h"

void Square::load()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    shader.compileVertexShader();
    shader.compileFragmentShader();
    shader.createShaderProgram();
}

void Square::render()
{
    shader.use();
    int scaleMatrixLocation = glGetUniformLocation(shader.programId, "scaleMatrix");
    int translationMatrixLocation = glGetUniformLocation(shader.programId, "translationMatrix");
    glUniformMatrix4fv(scaleMatrixLocation, 1, GL_FALSE, scaleMatrix);
    glUniformMatrix4fv(translationMatrixLocation, 1, GL_FALSE, translationMatrix);
    glDrawArrays(GL_POLYGON, 0, 4);
}