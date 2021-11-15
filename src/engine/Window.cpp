#include <iostream>
#include "Window.h"

using std::cout;
using std::endl;

Window::Window(const std::string &title) : context(nullptr), title(title) {}

Window::~Window()
{
    SDL_Quit();
}

bool Window::init(int xPos, int yPos, int width, int height, bool isFullScreen)
{
    int flags = SDL_WINDOW_OPENGL;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout << "SDL failed to initialize." << endl;
        return 1;
    }

    //Initialize window and openGL
    window = SDL_CreateWindow("Tennis Game", xPos, yPos, width, height, flags);
    cout << "SDL window created!" << endl;
    context = SDL_GL_CreateContext(window);
    cout << "SDL Context created!" << endl;
    glewExperimental = GL_TRUE;
    glewInit();
    cout << "Glew Initialized" << endl;

    //Tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); //enable depth testing
    glDepthFunc(GL_LESS);    // depth-testing interprets a smaller value as "closer"

    //Set viewport and clear color
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    return true;
}

void Window::clearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen
}

void Window::swapBuffer()
{
    SDL_GL_SwapWindow(window); //Swapbuffer
}

void Window::clean()
{
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);
}