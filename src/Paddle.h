#ifndef PADDLE_H
#define PADDLE_H

#include <cctype>
#include "Square.h"

class Paddle : public Square
{
public:
    void init(string orientation);

    int getScore() { return score; }
    void incrementScore() { ++score; }
    void resetScore() { score = 0; }

    void movement(float dt, bool moveUp, bool moveDown, Square ball);
    void aiMovement(float dt, float threshold, Square ball);
    void playerMovement(float dt, float threshold, bool moveUp, bool moveDown);
    void moveUpwards(float dt, float threshold);
    void moveDownwards(float dt, float threshold);

    bool getAiControlled() { return aiControlled; }
    void setAiControlled(bool aiP) { aiControlled = aiP; }

private:
    int score = 0;
    bool aiControlled = false;
};
#endif
