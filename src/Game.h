#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <GL/glew.h>
#include "Shader.h"

class Game
{
public:
    Game();
    ~Game();

    void init(int screenWidth, int screenHeight);
    void load();
    void handleInputs();
    void update(float dt);
    void render();
    void clean();

    bool getIsRunning() { return isRunning; }
    void setIsRunning(bool irP) { isRunning = irP; }
    int getWindowWidth() { return windowWidth; }
    void setWindowWidth(int widthP) { windowWidth = widthP; }
    int getWindowHeight() { return windowHeight; }
    void setWindowHeight(int heightP) { windowHeight = heightP; }

private:
    bool isRunning;
    int windowWidth, windowHeight;
    GLuint vao;
    GLuint vbo;
    GLfloat points[16] = {
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

    float lastPositionX = 0.5f;
    float lastPositionY = 0.5f;
    float speedX = 1.0f;
    float speedY = 1.0f;
    Shader shader;
};
#endif