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

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

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
    glEnable(GL_TEXTURE_2D); // enable 2D textures
    glDepthFunc(GL_LESS);    // depth-testing interprets a smaller value as "closer"

    //Set viewport and clear color
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    return true;
}

int Window::round(double x)
{
    return (int)(x + 0.5);
}

int Window::nextpoweroftwo(int x)
{
    double logbase2 = log(x) / log(2);
    return round(pow(2, ceil(logbase2)));
}

void Window::renderText()
{
    int surfaceWidth, surfaceHeight;
    message = TTF_RenderText_Blended(font, "Test Test Test", textColor);
    Uint8 noOfColors;
    int texture_format;
    if (message == NULL)
    {
        cout << "Message Surface not created properly" << endl;
    }
    surfaceWidth = nextpoweroftwo(message->w);
    surfaceHeight = nextpoweroftwo(message->h);

    noOfColors = message->format->BytesPerPixel;
    if (noOfColors == 4) // contains an alpha channel
    {
        if (message->format->Rmask == 0x000000ff)
            texture_format = GL_RGBA;
        else
            texture_format = GL_BGRA;
    }
    else if (noOfColors == 3) // no alpha channel
    {
        if (message->format->Rmask == 0x000000ff)
            texture_format = GL_RGB;
        else
            texture_format = GL_BGR;
    }
    else
    {
        printf("warning: the texture is not truecolor..  this will probably break\n");
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, noOfColors, surfaceWidth, surfaceHeight, 0, texture_format, GL_UNSIGNED_BYTE, message->pixels);
    SDL_FreeSurface(message);

    glBindTexture(GL_TEXTURE_2D, texture);

    //Draw with OpenGL
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex3f(100, 100, 0.0f);
    glTexCoord2i(1, 0);
    glVertex3f(228, 100, 0);
    glTexCoord2i(1, 1);
    glVertex3f(228, 228, 0);
    glTexCoord2i(0, 1);
    glVertex3f(100, 228, 0);
    glEnd();
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