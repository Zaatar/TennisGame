#include "Paddle.h"

void Paddle::init(string orientation)
{
    for (int i = 0; i < orientation.length(); i++)
    {
        orientation[i] = tolower(orientation[i]);
    }
    if (orientation == "left" || orientation == "l")
    {
        translationMatrix[12] = -0.95f;
    }
    else
    {
        translationMatrix[12] = 0.95f;
    }
    lastPositionY = 0.0f;
    for (int i = 0; i < 16; ++i)
    {
        scaleMatrix[i] = paddleScaleMatrix[i];
    }
}
void Paddle::movement(float dt, bool moveUp, bool moveDown)
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