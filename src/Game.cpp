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
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    shader.compileVertexShader();
    shader.compileFragmentShader();
    shader.createShaderProgram();
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
            {
                isRunning = false;
            }
            break;
        default:
            break;
        }
    }
}

void Game::update(float dt)
{
    if (abs(lastPositionX) > 1.0 - 0.125)
    {
        speedX = -speedX;
    }
    if (abs(lastPositionY) > 1.0 - 0.125)
    {
        speedY = -speedY;
    }

    translationMatrix[12] = speedX * dt + lastPositionX;
    lastPositionX = translationMatrix[12];
    translationMatrix[13] = speedY * dt + lastPositionY;
    lastPositionY = translationMatrix[13];

    shader.use();
    int scaleMatrixLocation = glGetUniformLocation(shader.programId, "scaleMatrix");
    int translationMatrixLocation = glGetUniformLocation(shader.programId, "translationMatrix");
    glUniformMatrix4fv(scaleMatrixLocation, 1, GL_FALSE, quarterScaleMatrix);
    glUniformMatrix4fv(translationMatrixLocation, 1, GL_FALSE, translationMatrix);
}

void Game::render()
{
    glDrawArrays(GL_POLYGON, 0, 4);
}

void Game::clean()
{
}