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

void Square::resetBall()
{
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

void Square::clampSpeed(float speed)
{
    if (speed > 1.5)
    {
        speed = 1.5;
    }
    if (speed < -1.5)
    {
        speed = -1.5;
    }
}

void Square::ballMovement(float dt, float lpaddleYPosition, float rpaddleYPosition)
{
    float threshold = 1.0 - 0.14;
    int origspeedY = speedY;
    int origspeedX = speedX;
    if (lastPositionX < -threshold)
    {
        //Ball hits above left paddle
        if (lastPositionY > lpaddleYPosition + 0.31)
        {
            lastPositionX = 0.0f;
            lastPositionY = 0.0f;
            //Score for right paddle
        }
        // Ball hits below left paddle
        else if (lastPositionY < lpaddleYPosition - 0.31)
        {
            lastPositionX = 0.0f;
            lastPositionY = 0.0f;
            //Score for right paddle
        }
        // Ball hits middle of the left paddle
        else if (lastPositionY > lpaddleYPosition - 0.10 && lastPositionY < lpaddleYPosition + 0.10)
        {
            if (speedX == 1.25)
            {
                speedX = origspeedX;
            }
            if (speedX == -1.25)
            {
                speedX = -origspeedX;
            }
            speedX = -speedX;
            speedY = 0;
        }
        //Ball hits the upper section of the left paddle
        else if (lastPositionY > lpaddleYPosition + 0.11 && lastPositionY < lpaddleYPosition + 0.3)
        {
            speedX = -speedX * 1.25;
            if (speedY == 0)
            {
                speedY = 1.25;
            }
            else
            {
                speedY = -speedY;
            }
            //The below line will be overwritten below, need to think of how to add this functionality.
            translationMatrix[13] = 0.75f;
        }
        //Ball hits the lower section of the left paddle
        else if (lastPositionY < lpaddleYPosition - 0.11 && lastPositionY > lpaddleYPosition - 0.3)
        {
            speedX = -speedX * 1.25;
            if (speedY == 0)
            {
                speedY = 1.25;
            }
            else
            {
                speedY = -speedY;
            }
            translationMatrix[13] = -0.75f;
        }
    }

    if (lastPositionX > threshold)
    {
        //Ball hits above right paddle
        if (lastPositionY > rpaddleYPosition + 0.31)
        {
            lastPositionX = 0.0f;
            lastPositionY = 0.0f;
            //Score for left paddle
        }
        // Ball hits below right paddle
        else if (lastPositionY < rpaddleYPosition - 0.31)
        {
            lastPositionX = 0.0f;
            lastPositionY = 0.0f;
            //Score for left paddle
        }
        // Ball hits middle of the right paddle
        else if (lastPositionY > rpaddleYPosition - 0.10 && lastPositionY < rpaddleYPosition + 0.10)
        {
            if (speedX == 1.25)
            {
                speedX = origspeedX;
            }
            if (speedX == -1.25)
            {
                speedX = -origspeedX;
            }
            speedX = -speedX;
            speedY = 0;
        }
        //Ball hits the upper section of the right paddle
        else if (lastPositionY > rpaddleYPosition + 0.11 && lastPositionY < rpaddleYPosition + 0.3)
        {
            speedX = -speedX * 1.25;
            if (speedY == 0)
            {
                speedY = 1.25;
            }
            else
            {
                speedY = -speedY;
            }
            translationMatrix[13] = 0.75f;
        }
        //Ball hits the lower section of the right paddle
        else if (lastPositionY < rpaddleYPosition - 0.11 && lastPositionY > rpaddleYPosition - 0.3)
        {
            speedX = -speedX * 1.25;
            if (speedY == 0)
            {
                speedY = 1.25;
            }
            else
            {
                speedY = -speedY;
            }
            translationMatrix[13] = -0.75f;
        }
    }

    if (speedX > 1.5)
    {
        speedX = 1.5;
    }
    if (speedX < -1.5)
    {
        speedX = -1.5;
    }
    if (speedY > 1.5)
    {
        speedY = 1.5;
    }
    if (speedY < -1.5)
    {
        speedY = -1.5;
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