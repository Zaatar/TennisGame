#include "Text.h"

void Text::init()
{

    if (TTF_Init() == -1)
    {
        cout << "SDL_TTF failed to initialize" << endl;
    }

    //Initialize font
    font = TTF_OpenFont("../build/assets/Carlito-Regular.ttf", 28);
    if (font == NULL)
    {
        cout << "Font not set properly" << endl;
    }

    setText("SCORE");
    for (int i = 0; i < 16; ++i)
    {
        scaleMatrix[i] = textureScaleMatrix[i];
    }
    translationMatrix[13] = 0.9f;
}

int Text::round(float x)
{
    return (int)(x + 0.5);
}

int Text::nextpoweroftwo(int x)
{
    double logbase2 = log(x) / log(2);
    return round(pow(2, ceil(logbase2)));
}

void Text::setText(char *text)
{
    int surfaceWidth, surfaceHeight;
    message = TTF_RenderText_Blended(font, "Test", textColor);
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

    glTexImage2D(GL_TEXTURE_2D, 0, noOfColors, surfaceWidth, surfaceHeight, 0, texture_format, GL_UNSIGNED_BYTE, message->pixels);
    SDL_FreeSurface(message);

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
/*
void Text::load()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    

    shader.compileVertexShader();
    shader.compileFragmentShader();
    shader.createShaderProgram();
}
*/
void Text::render()
{
    glBindTexture(GL_TEXTURE_2D, texture);
    shader.use();
    int scaleMatrixLocation = glGetUniformLocation(shader.programId, "scaleMatrix");
    int translationMatrixLocation = glGetUniformLocation(shader.programId, "translationMatrix");
    glUniformMatrix4fv(scaleMatrixLocation, 1, GL_FALSE, scaleMatrix);
    glUniformMatrix4fv(translationMatrixLocation, 1, GL_FALSE, translationMatrix);
    glDrawArrays(GL_POLYGON, 0, 4);
}