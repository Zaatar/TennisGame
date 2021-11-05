#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <GL/glew.h>
#include "Shader.h"
#include "Square.h"

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

    Square ball;
    Square leftPaddle;
    Square rightPaddle;
};
#endif