#ifndef SQUARE_H
#define SQUARE_H

#include <GL/glew.h>

class Square
{
public:
    Square() = default;
    ~Square() = default;
    float updateTranslationX();
    float updateTranslationY();
    float getSpeedX() { return speedX; }
    void setSpeedX(float sP) { speedX = sP; }
    float getSpeedY() { return speedY; }
    void setSpeedY(float sP) { speedY = sP; }
    float getLastPositionX() { return lastPositionX; }
    float getLastPositionY() { return lastPositionY; }

private:
    float speedX = 1.0f;
    float speedY = 1.0f;
    float lastPositionX = 0.5f;
    float lastPositionY = 0.5f;
    GLfloat points[16] = {
        -0.5, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f};
    GLfloat ballScaleMatrix[16] = {
        0.25f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.25f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.25f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat translationMatrix[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat paddleScaleMatrix[16] = {
        0.1f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.6f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};
};
#endif