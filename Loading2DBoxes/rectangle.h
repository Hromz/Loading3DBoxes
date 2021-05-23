#include "coords.h"
#include <vector>
#include <map>
#include <utility>
#include <set>
#include <iostream>
#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle : Coords
{
public:
    Coords topLeft;
    Coords bottomLeft;
    Coords topRight;
    Coords bottomRight;

    Rectangle() {};
    Rectangle(const Rectangle& rec);
    Rectangle(Coords& tl, Coords& tp, Coords& bl, Coords& br);
    Rectangle(int length, int height);
    ~Rectangle() { };

    Coords getTopLeft() { return topLeft; }
    Coords getTopRight() { return topRight; }
    Coords getBottomLeft() { return bottomLeft; }
    Coords getBottomRight() { return bottomRight; }

    int getWidth(){ return topRight.getX() - topLeft.getX(); }
    int getHeight() { return topRight.getY() - bottomRight.getY(); }
    int getX() { return topRight.getX(); }
    int getY() { return topRight.getY(); }

    void setTopLeft(Coords coords) { topLeft = coords; }
    void setTopRight(Coords coords) { topRight = coords; }
    void setBottomLeft(Coords coords) { bottomLeft = coords; }
    void setBottomRight(Coords coords) { bottomRight = coords; }
    void setRectangle(int length, int height);
};

#endif // RECTANGLE_H