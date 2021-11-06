#include <SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <GL/GLU.h>

#include "Timer.h"
#include "Window.h"
#include "Game.h"

using std::cout;
using std::endl;

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

int main(int argc = 0, char **argv = nullptr)
{
    //Handle args
    if (argc > 0)
    {
        for (int i = 0; i < argc; ++i)
        {
            cout << argv[i] << endl;
        }
    }

    Window window = Window("Tennis Game");
    if (!window.init(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false))
    {
        cout << "Error in initialising window" << endl;
        return 1;
    }

    //Get info
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    cout << "Renderer: " << renderer << endl;
    cout << "OpenGL version supported: " << version << endl;

    Timer timer;
    Game game;
    game.init(SCREEN_WIDTH, SCREEN_HEIGHT);
    game.load();
    float dt;

    while (game.getIsRunning())
    {
        dt = static_cast<float>(timer.computeDeltaTime()) / 1000.0f;
        game.handleInputs();

        game.update(dt);
        //Draw
        window.clearScreen();
        game.render();

        window.swapBuffer();
    }

    //Quit
    window.clean();

    return 0;
}