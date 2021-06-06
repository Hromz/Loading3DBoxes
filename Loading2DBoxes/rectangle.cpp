#include "rectangle.h"

Rectangle::Rectangle(const Rectangle& rec)
{
    this->topLeftLHS = rec.topLeftLHS;
    this->bottomLeftLHS = rec.bottomLeftLHS;
    this->topRightLHS = rec.topRightLHS;
    this->bottomRightLHS = rec.bottomRightLHS;

    this->topLeftRHS = rec.topLeftRHS;
    this->bottomLeftRHS = rec.bottomLeftRHS;
    this->topRightRHS = rec.topRightRHS;
    this->bottomRightRHS = rec.bottomRightRHS;
}

Rectangle::Rectangle(Coords& tl, Coords& tr, Coords& bl, Coords& br, Coords & tlr, Coords& tpr, Coords& blr, Coords& brr)
{
    topLeftLHS = tl;
    topRightLHS = tr;
    bottomLeftLHS = bl;
    bottomRightLHS = br;

    topLeftRHS = tlr;
    bottomLeftRHS = blr;
    topRightRHS = tpr;
    bottomRightRHS = brr;
}

Rectangle::Rectangle(int length, int height,int width)
{
    topLeftLHS.setCoords(0, height, 0);
    topRightLHS.setCoords(length, height, 0);
    bottomLeftLHS.setCoords(0, 0, 0);
    bottomRightLHS.setCoords(length, 0, 0);

    topLeftRHS.setCoords(0, height, width);
    topRightRHS.setCoords(length, height, width);
    bottomLeftRHS.setCoords(0, 0, width);
    bottomRightRHS.setCoords(length, 0, width);
}

// length - x, height - y, width - z
void Rectangle::setRectangle(int length,int height, int width)
{
    topLeftLHS.setCoords(0, height, 0);
    topRightLHS.setCoords(length, height, 0);
    bottomLeftLHS.setCoords(0, 0, 0);
    bottomRightLHS.setCoords(length, 0, 0);

    topLeftRHS.setCoords(0, height, width);
    bottomLeftRHS.setCoords(0, 0, width);
    topRightRHS.setCoords(length, height, width);
    bottomRightRHS.setCoords(length, 0, width);
}