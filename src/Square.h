#ifndef SQUARE_H
#define SQUARE_H

class Square
{
public:
    Square() = default;
    ~Square() = default;
    void updateTranslationMatrix();
    void updateTranslationMatrix(float x, float y);
    float getSpeed() { return speed; }
    void setSpeed(float sP) { speed = sP; }
    float getLastPosition() { return lastPosition; }

private:
    float speed = 1.0f;
    float lastPosition = 0.5f;
    float points[16];
    float quarterScaleMatrix[16] = {
        0.25f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.25f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.25f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};
    float translationMatrix[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};
};
#endif