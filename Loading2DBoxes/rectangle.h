#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "coords.h"
#include <vector>
#include <utility>
#include <iostream>

class Rectangle : Coords
{
public:
    //Left side of 3D box
    Coords topLeftLHS;
    Coords bottomLeftLHS;
    Coords topRightLHS;
    Coords bottomRightLHS;

    //Right side of 3D box
    Coords topLeftRHS;
    Coords bottomLeftRHS;
    Coords topRightRHS;
    Coords bottomRightRHS;

    Rectangle() {};
    Rectangle(const Rectangle& rec);
    Rectangle(Coords& tl, Coords& tp, Coords& bl, Coords& br, Coords& tlr, Coords& tpr, Coords& blr, Coords& brr);
    Rectangle(int length,int height, int width);
    ~Rectangle() { };

    Coords gettopLeftLHS() { return topLeftLHS; }
    Coords getTopRight() { return topRightLHS; }
    Coords getBottomLeft() { return bottomLeftLHS; }
    Coords getBottomRight() { return bottomRightLHS; }

    int getLength(){ return bottomRightLHS.getX() - bottomLeftLHS.getX(); }
    int getHeight() { return topRightLHS.getY() - bottomRightLHS.getY(); }
    int getWidth() { return topRightRHS.getZ() - topRightLHS.getZ(); }

    int getX() { return topRightLHS.getX(); }
    int getY() { return topRightLHS.getY(); }
    int getZ() { return topRightRHS.getZ(); }

    void settopLeftLHS(Coords & coords) { topLeftLHS = coords; }
    void setTopRight(Coords & coords) { topRightLHS = coords; }
    void setBottomLeft(Coords & coords) { bottomLeftLHS = coords; }
    void setBottomRight(Coords & coords) { bottomRightLHS = coords; }

    void setTopLeftLHS(Coords & coords) { topLeftLHS = coords; }
    void setTopRightRight(Coords & coords) { topRightRHS = coords; }
    void setBottomLeftRight(Coords & coords) { bottomLeftRHS = coords; }
    void setBottomRightRight(Coords & coords) { bottomRightRHS = coords; }

    // length - x, height - y, width - z
    void setRectangle(int length,int height, int width);
};

#endif // RECTANGLE_H