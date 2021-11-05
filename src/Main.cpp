#include <SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <GL/GLU.h>

#include "Timer.h"
#include "Window.h"
#include "Shader.h"

using std::cout;
using std::endl;

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

int main(int argc = 0, char **argv = nullptr)
{
    GLfloat points[] = {
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

    //Handle args
    if (argc > 0)
    {
        for (int i = 0; i < argc; ++i)
        {
            cout << argv[i] << endl;
        }
    }

    Window window = Window("Tennis Game");
    Shader shader;
    if (!window.init(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false))
    {
        cout << "Error in initialising window" << endl;
        return 1;
    }
    GLuint vao = 0;
    GLuint vbo = 0;
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

    //Get info
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    cout << "Renderer: " << renderer << endl;
    cout << "OpenGL version supported: " << version << endl;

    Timer timer;
    float dt;

    bool isRunning = true;
    while (isRunning)
    {
        dt = static_cast<float>(timer.computeDeltaTime()) / 1000.0f;
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;
            default:
                break;
            }
        }

        //Update
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
        //Draw
        window.clearScreen();

        shader.use();
        int scaleMatrixLocation = glGetUniformLocation(shader.programId, "scaleMatrix");
        int translationMatrixLocation = glGetUniformLocation(shader.programId, "translationMatrix");
        glUniformMatrix4fv(scaleMatrixLocation, 1, GL_FALSE, quarterScaleMatrix);
        glUniformMatrix4fv(translationMatrixLocation, 1, GL_FALSE, translationMatrix);
        glDrawArrays(GL_POLYGON, 0, 4);

        window.swapBuffer();
    }

    //Quit
    window.clean();

    return 0;
}