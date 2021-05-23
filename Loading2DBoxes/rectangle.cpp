#include "rectangle.h"

Rectangle::Rectangle(const Rectangle& rec)
{
    this->topLeft = rec.topLeft;
    this->bottomLeft = rec.bottomLeft;
    this->topRight = rec.topRight;
    this->bottomRight = rec.bottomRight;
}

Rectangle::Rectangle(Coords& tl, Coords& tr, Coords& bl, Coords& br)
{
    topLeft = tl;
    topRight = tr;
    bottomLeft = bl;
    bottomRight = br;
}

Rectangle::Rectangle(int length, int height)
{
    topLeft.setCoords(0, height);
    topRight.setCoords(length, height);
    bottomLeft.setCoords(0, 0);
    bottomRight.setCoords(length, 0);
}

void Rectangle::setRectangle(int length, int height)
{
    topLeft.setCoords(0, height);
    topRight.setCoords(length, height);
    bottomLeft.setCoords(0, 0);
    bottomRight.setCoords(length, 0);
}