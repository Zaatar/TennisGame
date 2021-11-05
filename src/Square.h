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

    void load();
    void ballMovement(float dt);
    void render();

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
    GLuint ballVao;
    GLuint ballVbo;
    GLuint lpaddleVao;
    GLuint lpaddleVbo;
    GLuint rpaddleVao;
    GLuint rpaddleVbo;
    float radius = 0.125;
    float lastPositionX = 0.5f;
    float lastPositionY = 0.5f;
    float speedX = 1.0f;
    float speedY = 1.0f;
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