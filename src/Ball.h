#ifndef BALL_H
#define BALL_H

#include "Square.h"

class Ball : public Square
{
public:
    void init();
    void movement(float dt, float lpaddleYPosition, float rpaddleYPosition);

private:
};
#endif