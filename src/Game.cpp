#include "Game.h"

Game::Game() : isRunning(false), windowWidth(0), windowHeight(0) {}

Game::~Game() {}

void Game::init(int screenWidthP, int screenHeightP)
{
    windowWidth = screenWidthP;
    windowHeight = screenHeightP;
    isRunning = true;
    leftPaddle.init("left");
    rightPaddle.init("right");
    ball.init();
}

void Game::load()
{
    leftPaddle.load();
    rightPaddle.load();
    ball.load();
}

void Game::handleInputs()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                isRunning = false;
            if (event.key.keysym.sym == SDLK_w)
            {
                lMoveUp = true;
                lMoveDown = false;
            }
            if (event.key.keysym.sym == SDLK_s)
            {
                lMoveDown = true;
                lMoveUp = false;
            }
            if (event.key.keysym.sym == SDLK_UP)
            {
                rMoveUp = true;
                rMoveDown = false;
            }
            if (event.key.keysym.sym == SDLK_DOWN)
            {
                rMoveDown = true;
                rMoveUp = false;
            }
            break;
        default:
            break;
        }
    }
}

void Game::update(float dt)
{
    leftPaddle.movement(dt, lMoveUp, lMoveDown);
    rightPaddle.movement(dt, rMoveUp, rMoveDown);
    ball.movement(dt, leftPaddle.getLastPositionY(), rightPaddle.getLastPositionY());
}

void Game::render()
{
    ball.render();
    leftPaddle.render();
    rightPaddle.render();
}

void Game::clean()
{
}