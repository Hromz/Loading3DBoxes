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
    bool boxOnRhs = false;
    bool boxOnTopSide = false;
    std::vector<Rectangle> container;
public:
    Rectangle() {};
    Rectangle(const Rectangle& rec);
    Rectangle(Coords& tl, Coords& tp, Coords& bl, Coords& br);
    Rectangle(int length, int height);
    ~Rectangle() { };
  

    bool containerCollision(Rectangle& rec);
    bool boxCollision(const Rectangle& rec);
    void placeInside(const Rectangle& rec);

    Rectangle changeCoordsPlacingTop(Rectangle& rec);
    Rectangle changeCoordsPlacingRHS( Rectangle& rec);

    bool isPossiblePlaceOnTopOfBox(Rectangle& rec);
    bool isPossiblePlaceOnRightHandSide(Rectangle& rec);


    Coords getTopLeft() { return topLeft; }
    Coords getTopRight() { return topRight; }
    Coords getBottomLeft() { return bottomLeft; }
    Coords getBottomRight() { return bottomRight; }
    int getLength(){ return topRight.getX(); }
    int getHeight() { return topRight.getY(); }


    bool containsBoxOnTop() { return boxOnTopSide; }
    bool containsBoxRHS() { return boxOnRhs; }

    void setTopLeft(Coords coords) { topLeft = coords; }
    void setTopRight(Coords coords) { topRight = coords; }
    void setBottomLeft(Coords coords) { bottomLeft = coords; }
    void setBottomRight(Coords coords) { bottomRight = coords; }
    void setBoxOnRHS(bool b) { boxOnRhs = b; }
    void setBoxOnTop(bool b) { boxOnTopSide = b; }

    void print();
    void printCoords();
};

#endif // RECTANGLE_H