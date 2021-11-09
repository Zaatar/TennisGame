#include "Ball.h"

void Ball::init()
{
    for (int i = 0; i < 16; ++i)
    {
        scaleMatrix[i] = quarterScaleMatrix[i];
    }
}

void Ball::movement(float dt, float lpaddleYPosition, float rpaddleYPosition)
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
            rpaddleScored = true;
        }
        // Ball hits below left paddle
        else if (lastPositionY < lpaddleYPosition - 0.31)
        {
            lastPositionX = 0.0f;
            lastPositionY = 0.0f;
            rpaddleScored = true;
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
            speedY = 1.25;
            //The below line will be overwritten below, need to think of how to add this functionality.
            translationMatrix[13] = 0.75f;
        }
        //Ball hits the lower section of the left paddle
        else if (lastPositionY < lpaddleYPosition - 0.11 && lastPositionY > lpaddleYPosition - 0.3)
        {
            speedX = -speedX * 1.25;
            speedY = -1.25;
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
            lpaddleScored = true;
        }
        // Ball hits below right paddle
        else if (lastPositionY < rpaddleYPosition - 0.31)
        {
            lastPositionX = 0.0f;
            lastPositionY = 0.0f;
            lpaddleScored = true;
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
            speedY = 1.25;
            translationMatrix[13] = 0.75f;
        }
        //Ball hits the lower section of the right paddle
        else if (lastPositionY < rpaddleYPosition - 0.11 && lastPositionY > rpaddleYPosition - 0.3)
        {
            speedX = -speedX * 1.25;
            speedY = -1.25;
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