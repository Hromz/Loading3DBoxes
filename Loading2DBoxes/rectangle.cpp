#include "rectangle.h"

Rectangle::Rectangle(const Rectangle& rec)
{
    this->topLeft = rec.topLeft;
    this->bottomLeft = rec.bottomLeft;
    this->topRight = rec.topRight;
    this->bottomRight = rec.bottomRight;

    this->topLeftRight = rec.topLeftRight;
    this->bottomLeftRight = rec.bottomLeftRight;
    this->topRightRight = rec.topRightRight;
    this->bottomRightRight = rec.bottomRightRight;
}

Rectangle::Rectangle(Coords& tl, Coords& tr, Coords& bl, Coords& br, Coords & tlr, Coords& tpr, Coords& blr, Coords& brr)
{
    topLeft = tl;
    topRight = tr;
    bottomLeft = bl;
    bottomRight = br;

    topLeftRight = tlr;
    bottomLeftRight = blr;
    topRightRight = tpr;
    bottomRightRight = brr;
}

Rectangle::Rectangle(int length,int width, int height)
{
    topLeft.setCoords(0, height, 0);
    topRight.setCoords(length, height, 0);
    bottomLeft.setCoords(0, 0, 0);
    bottomRight.setCoords(length, 0, 0);
}

// length - x, height - y, width - z
void Rectangle::setRectangle(int length,int height, int width)
{
    topLeft.setCoords(0, height, 0);
    topRight.setCoords(length, height, 0);
    bottomLeft.setCoords(0, 0, 0);
    bottomRight.setCoords(length, 0, 0);

    topLeftRight.setCoords(0, height, width);
    bottomLeftRight.setCoords(0, 0, width);
    topRightRight.setCoords(length, height, width);
    bottomRightRight.setCoords(length, 0, width);
}