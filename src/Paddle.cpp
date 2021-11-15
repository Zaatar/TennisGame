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

void Paddle::moveUpwards(float dt, float threshold)
{

    if (lastPositionY > threshold)
    {
        speedY = 0;
    }
    translationMatrix[13] = speedY * dt + lastPositionY;
    lastPositionY = translationMatrix[13];
    speedY = 1;
}

void Paddle::moveDownwards(float dt, float threshold)
{
    if (lastPositionY < -threshold)
    {
        speedY = 0;
    }
    translationMatrix[13] = -speedY * dt + lastPositionY;
    lastPositionY = translationMatrix[13];
    speedY = 1;
}

void Paddle::aiMovement(float dt, float threshold, Square ball)
{
    if (ball.getLastPositionY() > lastPositionY)
    {
        moveUpwards(dt, threshold);
    }
    else if (ball.getLastPositionY() < lastPositionY)
    {
        moveDownwards(dt, threshold);
    }
}

void Paddle::playerMovement(float dt, float threshold, bool moveUp, bool moveDown)
{
    if (moveUp == true)
    {
        moveUpwards(dt, threshold);
    }

    if (moveDown == true)
    {
        moveDownwards(dt, threshold);
    }
}

void Paddle::movement(float dt, bool moveUp, bool moveDown, Square ball)
{
    float threshold = 1.0 - 0.3;
    if (aiControlled)
    {
        aiMovement(dt, threshold, ball);
    }
    else
    {
        playerMovement(dt, threshold, moveUp, moveDown);
    }
}