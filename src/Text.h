#ifndef TEXT_H
#define TEXT_H

#include <SDL_ttf.h>

class Text
{
public:
    Text(int pX, int pY, int pWidth, int pHeight);
    Text();
    ~Text();

private:
    int x, y;
    int width, height;
    TTF_Font *font;
    SDL_Color color;
    SDL_Surface *surface;
    SDL_Texture *texture;
};
#endif