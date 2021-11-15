#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <GL/glew.h>
#include "Shader.h"
#include "Ball.h"
#include "Paddle.h"
#include "Text.h"

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
    void updateScore();

    bool getIsRunning() { return isRunning; }
    void setIsRunning(bool irP) { isRunning = irP; }
    int getWindowWidth() { return windowWidth; }
    void setWindowWidth(int widthP) { windowWidth = widthP; }
    int getWindowHeight() { return windowHeight; }
    void setWindowHeight(int heightP) { windowHeight = heightP; }

private:
    bool isRunning;
    int windowWidth, windowHeight;

    Ball ball;
    Paddle leftPaddle;
    Paddle rightPaddle;
    Text text;

    bool lMoveUp = false;
    bool lMoveDown = false;
    bool rMoveUp = false;
    bool rMoveDown = false;
};
#endif