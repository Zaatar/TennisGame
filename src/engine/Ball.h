#ifndef BALL_H
#define BALL_H

#include <iostream>
#include "Square.h"

using std::cout;
using std::endl;

class Ball : public Square
{
public:
    void init();
    void movement(float dt, float lpaddleYPosition, float rpaddleYPosition);
    bool getLPaddleScored() { return lpaddleScored; }
    void setLPaddleScored(bool lscoredP) { lpaddleScored = lscoredP; }
    bool getRPaddleScored() { return rpaddleScored; }
    void setRPaddleScored(bool rscoredP) { rpaddleScored = rscoredP; }

private:
    bool lpaddleScored = false;
    bool rpaddleScored = false;
};
#endif