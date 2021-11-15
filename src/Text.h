#ifndef TEXT_H
#define TEXT_H
#include <GL/glew.h>
#include <SDL_ttf.h>
#include <iostream>
#include <math.h>

#include "Square.h"
#include "Shader.h"

using std::cout;
using std::endl;

class Text : public Square
{
public:
    Text() = default;
    ~Text() = default;

    void init();
    void setText(char *text);
    void render();
    //    void load();

    int round(float x);
    int nextpoweroftwo(int x);

private:
    SDL_Surface *message = NULL;
    SDL_Color textColor = {255, 255, 255, 255};
    TTF_Font *font = NULL;
    unsigned int texture;
    float texCoords[12] = {
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f};

    float textureScaleMatrix[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.15f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};
};

#endif