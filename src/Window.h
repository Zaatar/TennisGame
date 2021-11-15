#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <SDL.h>
#include <GL/glew.h>
#include <iostream>

class Window
{
public:
    Window(const std::string &title);
    ~Window();

    bool init(int xPos, int yPos, int width, int height, bool isFullScreen);
    void clearScreen();
    void swapBuffer();
    void clean();

private:
    SDL_Window *window;
    SDL_GLContext context;
    const std::string &title;

    Window() = delete;
    Window(const Window &) = delete;
};
#endif