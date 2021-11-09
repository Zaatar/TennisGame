#ifndef PADDLE_H
#define PADDLE_H

#include <cctype>
#include "Square.h"

class Paddle : public Square
{
public:
    void init(string orientation);
    void movement(float dt, bool moveUp, bool moveDown);

private:
};
#endif
