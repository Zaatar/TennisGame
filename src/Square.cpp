#include "Square.h"

void Square::updateTranslationMatrix()
{
    translationMatrix[12] = speed + lastPosition;
    translationMatrix[13] = speed + lastPosition;
}

void Square::updateTranslationMatrix(float xP, float yP)
{
    translationMatrix[12] = xP * speed + lastPosition;
    translationMatrix[13] = yP * speed + lastPosition;
}