#ifndef PADDLE_H
#define PADDLE_H

#include <cctype>
#include "Square.h"

class Paddle : public Square
{
public:
    void init(string orientation);
    void movement(float dt, bool moveUp, bool moveDown);

    int getScore() { return score; }
    void incrementScore() { ++score; }

private:
    int score = 0;
};
#endif
