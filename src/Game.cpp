#include "Game.h"

Game::Game() : isRunning(false), windowWidth(0), windowHeight(0) {}

Game::~Game() {}

void Game::init(int screenWidthP, int screenHeightP)
{
    windowWidth = screenWidthP;
    windowHeight = screenHeightP;
    isRunning = true;
}

void Game::load()
{
    ball.load();
    leftPaddle.load();
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
                lMoveUp = true;
            else
                lMoveUp = false;
            if (event.key.keysym.sym == SDLK_s)
                lMoveDown = true;
            else
                lMoveDown = false;
            break;
            if (event.key.keysym.sym == SDLK_UP)
                rMoveUp = true;
            else
                rMoveUp = false;
            break;
            if (event.key.keysym.sym == SDLK_DOWN)
                rMoveDown = true;
            else
                rMoveDown = false;
            break;
        default:
            break;
        }
    }
}

void Game::update(float dt)
{
    ball.ballMovement(dt);
    leftPaddle.drawLeftPaddle(dt, lMoveUp, lMoveDown);
}

void Game::render()
{
    ball.render();
    leftPaddle.render();
}

void Game::clean()
{
}