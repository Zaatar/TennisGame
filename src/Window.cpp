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

    if (TTF_Init() == -1)
    {
        cout << "SDL_TTF failed to initialize" << endl;
        return 1;
    }

    //Initialize window and openGL
    window = SDL_CreateWindow("Tennis Game", xPos, yPos, width, height, flags);
    context = SDL_GL_CreateContext(window);
    glewExperimental = GL_TRUE;
    glewInit();

    //Initialize font
    font = TTF_OpenFont("../build/assets/Carlito-Regular.ttf", 28);
    if (font == NULL)
    {
        cout << "Font not set properly" << endl;
        return -1;
    }

    //Tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); //enable depth testing
    glDepthFunc(GL_LESS);    // depth-testing interprets a smaller value as "closer"

    //Set viewport and clear color
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    return true;
}

void Window::renderText()
{
    message = TTF_RenderText_Solid(font, "Test Test Test", textColor);
    int format = 0;
    Uint8 colors = message->format->BytesPerPixel;
    if (colors == 4)
    { // alpha
        if (message->format->Rmask == 0x000000ff)
            format = GL_RGBA;
        else
            format = GL_BGRA;
    }
    else
    { // no alpha
        if (message->format->Rmask == 0x000000ff)
            format = GL_RGB;
        else
            format = GL_BGR;
    }
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, format, message->w, message->h, 0, format, GL_UNSIGNED_BYTE, message->pixels);
    SDL_FreeSurface(message);
    TTF_CloseFont(font);
    TTF_Quit();
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