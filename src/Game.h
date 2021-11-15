#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <GL/glew.h>
#include <string>

#include "Square.h"
#include "Ball.h"
#include "Paddle.h"

using std::string;

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
    bool getIsGameOver() { return isGameOver; }
    string getWinner() { return winner; }

private:
    bool isRunning;
    bool isGameOver = false;
    int windowWidth, windowHeight;
    string winner;

    Ball ball;
    Paddle leftPaddle;
    Paddle rightPaddle;

    bool lMoveUp = false;
    bool lMoveDown = false;
    bool rMoveUp = false;
    bool rMoveDown = false;
};
#endif