#include "coords.h"
#include <vector>
#include <utility>
#include <iostream>
#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle : Coords
{
public:
    //Left side of 3D box
    Coords topLeft;
    Coords bottomLeft;
    Coords topRight;
    Coords bottomRight;

    //Right side of 3D box
    Coords topLeftRight;
    Coords bottomLeftRight;
    Coords topRightRight;
    Coords bottomRightRight;

    Rectangle() {};
    Rectangle(const Rectangle& rec);
    Rectangle(Coords& tl, Coords& tp, Coords& bl, Coords& br, Coords& tlr, Coords& tpr, Coords& blr, Coords& brr);
    Rectangle(int length,int height, int width);
    ~Rectangle() { };

    Coords getTopLeft() { return topLeft; }
    Coords getTopRight() { return topRight; }
    Coords getBottomLeft() { return bottomLeft; }
    Coords getBottomRight() { return bottomRight; }

    int getLength(){ return topRight.getX() - topLeft.getX(); }
    int getHeight() { return topRight.getY() - bottomRight.getY(); }
    int getWidth() { return topRight.getZ() -  topRightRight.getZ(); }

    int getX() { return topRight.getX(); }
    int getY() { return topRight.getY(); }
    int getZ() { return topRightRight.getZ(); }

    void setTopLeft(Coords coords) { topLeft = coords; }
    void setTopRight(Coords coords) { topRight = coords; }
    void setBottomLeft(Coords coords) { bottomLeft = coords; }
    void setBottomRight(Coords coords) { bottomRight = coords; }

    void setTopLeftRight(Coords coords) { topLeftRight = coords; }
    void setTtopRightRight(Coords coords) { topRightRight = coords; }
    void setBottomLeftRight(Coords coords) { bottomLeftRight = coords; }
    void setBottomRightRight(Coords coords) { bottomRightRight = coords; }

    // length - x, height - y, width - z
    void setRectangle(int length,int height, int width);
};

#endif // RECTANGLE_H