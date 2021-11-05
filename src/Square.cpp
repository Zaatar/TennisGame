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
    /*
    //Ball VAO & VBO
    glGenVertexArrays(1, &ballVao);
    glBindVertexArray(ballVao);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &ballVbo);
    glBindBuffer(GL_ARRAY_BUFFER, ballVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    //Left Paddle VAO & VBO
    glGenVertexArrays(1, &lpaddleVao);
    glBindVertexArray(lpaddleVao);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &lpaddleVbo);
    glBindBuffer(GL_ARRAY_BUFFER, lpaddleVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    //Right Paddle VAO & VBO
    glGenVertexArrays(1, &rpaddleVao);
    glBindVertexArray(rpaddleVao);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &rpaddleVbo);
    glBindBuffer(GL_ARRAY_BUFFER, rpaddleVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    */
}

void Square::ballMovement(float dt)
{
    if (abs(lastPositionX) > 1.0 - 0.14)
    {
        speedX = -speedX;
    }
    if (abs(lastPositionY) > 1.0 - 0.14)
    {
        speedY = -speedY;
    }

    translationMatrix[12] = speedX * dt + lastPositionX;
    lastPositionX = translationMatrix[12];
    translationMatrix[13] = speedY * dt + lastPositionY;
    lastPositionY = translationMatrix[13];

    shader.use();
    int scaleMatrixLocation = glGetUniformLocation(shader.programId, "scaleMatrix");
    int translationMatrixLocation = glGetUniformLocation(shader.programId, "translationMatrix");
    glUniformMatrix4fv(scaleMatrixLocation, 1, GL_FALSE, quarterScaleMatrix);
    glUniformMatrix4fv(translationMatrixLocation, 1, GL_FALSE, translationMatrix);
}