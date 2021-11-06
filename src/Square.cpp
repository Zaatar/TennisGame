#include "Square.h"

void Square::initBall()
{
    for (int i = 0; i < 16; ++i)
    {
        scaleMatrix[i] = quarterScaleMatrix[i];
    }
}

void Square::initLeftPaddle()
{
    translationMatrix[12] = -0.95f;
    lastPositionY = 0.0f;
    for (int i = 0; i < 16; ++i)
    {
        scaleMatrix[i] = paddleScaleMatrix[i];
    }
}

void Square::initRightPaddle()
{
    translationMatrix[12] = 0.95f;
    lastPositionY = 0.0f;
    for (int i = 0; i < 16; ++i)
    {
        scaleMatrix[i] = paddleScaleMatrix[i];
    }
}

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

void Square::ballMovement(float dt)
{
    float threshold = 1.0 - 0.14;
    if (abs(lastPositionX) > threshold)
    {
        speedX = -speedX;
    }
    if (abs(lastPositionY) > threshold)
    {
        speedY = -speedY;
    }

    translationMatrix[12] = speedX * dt + lastPositionX;
    lastPositionX = translationMatrix[12];
    translationMatrix[13] = speedY * dt + lastPositionY;
    lastPositionY = translationMatrix[13];
}

void Square::paddleMovement(float dt, bool moveUp, bool moveDown)
{
    float threshold = 1.0 - 0.3;
    if (moveUp == true)
    {
        if (lastPositionY > threshold)
        {
            speedY = 0;
        }
        translationMatrix[13] = speedY * dt + lastPositionY;
        lastPositionY = translationMatrix[13];
        speedY = 1;
    }

    if (moveDown == true)
    {
        if (lastPositionY < -threshold)
        {
            speedY = 0;
        }
        translationMatrix[13] = -speedY * dt + lastPositionY;
        lastPositionY = translationMatrix[13];
        speedY = 1;
    }
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