#ifndef SQUARE_H
#define SQUARE_H

#include <SDL.h>
#include <iostream>
#include <GL/glew.h>

#include "Shader.h"

using std::string;

class Square
{
public:
    Square() = default;
    ~Square() = default;

    void initBall();
    void initLeftPaddle();
    void initRightPaddle();

    void load();
    void ballMovement(float dt, float lpaddleYPosition, float rpaddleYPosition);
    void paddleMovement(float dt, bool moveUp, bool moveDown);
    void resetBall();
    void render();
    void clampSpeed(float speed);

    float getSpeedX() { return speedX; }
    void setSpeedX(float sP) { speedX = sP; }
    float getSpeedY() { return speedY; }
    void setSpeedY(float sP) { speedY = sP; }
    float getLastPositionX() { return lastPositionX; }
    float getLastPositionY() { return lastPositionY; }

private:
    GLuint vao;
    GLuint vbo;
    Shader shader;
    float lastPositionX = 0.5f;
    float lastPositionY = 0.5f;
    float speedX = 1.0f;
    float speedY = 1.0f;

    float scaleMatrix[16] = {};

    float points[16] = {
        -0.5, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f};

    float quarterScaleMatrix[16] = {
        0.25f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.25f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.25f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};

    float translationMatrix[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};

    float paddleScaleMatrix[16] = {
        0.1f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.6f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};
};
#endif