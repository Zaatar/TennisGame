#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <GL/glew.h>
#include <math.h>

class Window
{
public:
    Window(const std::string &title);
    ~Window();

    bool init(int xPos, int yPos, int width, int height, bool isFullScreen);
    void clearScreen();
    void swapBuffer();
    void clean();

    void renderText();
    int round(double x);
    int nextpoweroftwo(int x);

private:
    SDL_Window *window;
    SDL_GLContext context;
    const std::string &title;
    SDL_Surface *message = NULL;
    SDL_Color textColor = {255, 255, 255};
    TTF_Font *font = NULL;
    unsigned int texture;

    Window() = delete;
    Window(const Window &) = delete;
};
#endif