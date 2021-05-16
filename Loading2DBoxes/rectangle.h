#include "coords.h"
#include <vector>
#include <iostream>
#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle : Coords
{
private:
    Coords topLeft;
    Coords bottomLeft;
    Coords topRight;
    Coords bottomRight;
    bool boxRhs = false;
    bool boxTop = false;
public:
    Rectangle() {};
    Rectangle(const Rectangle& rec);
    Rectangle(Coords& tl, Coords& tp, Coords& bl, Coords& br);
    Rectangle(int length, int height);
    ~Rectangle() { };

    bool containerCollision(const Rectangle& rec);
    bool boxCollision(const Rectangle& rec);
    void placeInside(const Rectangle& rec);

    Rectangle changeCoordsPlacingTop(const Rectangle& rec);
    Rectangle changeCoordsPlacingRHS(const Rectangle& rec);

    bool isPossiblePlaceOnTopOfBox(const Rectangle& rec);
    bool isPossiblePlaceOnRightHandSide(const Rectangle& rec);

    std::vector<Rectangle> container;


    Coords getTopLeft() { return topLeft; }
    Coords getTopRight() { return topRight; }
    Coords getBottomLeft() { return bottomLeft; }
    Coords getBottomRight() { return bottomRight; }
    bool containsBoxOnTop() { return boxTop; }
    bool  containsBoxRHS() { return boxRhs; }

    void setTopLeft(Coords coords) { topLeft = coords; }
    void setTopRight(Coords coords) { topRight = coords; }
    void setBottomLeft(Coords coords) { bottomLeft = coords; }
    void setBottomRight(Coords coords) { bottomRight = coords; }
    void setBoxOnRHS(bool b) { boxRhs = b; }
    void setBoxOnTop(bool b) { boxTop = b; }

    void print();
    void printCoords();
};

#endif // RECTANGLE_H