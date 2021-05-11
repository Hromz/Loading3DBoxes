#pragma once
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
public:
    Rectangle() {};
    Rectangle(const Rectangle& rec);
    Rectangle(Coords& tl, Coords& tp, Coords& bl, Coords& br);
    Rectangle(float length, float height);

    bool containerCollision(const Rectangle& rec);
    bool boxCollision(const Rectangle& rec);
    bool contains(const Rectangle& rec);

    void placeInside(Rectangle& rec);
    void movePosition(const Rectangle & neighbourRec);
    void changeCoords(Coords& tl, Coords& tp, Coords& bl, Coords& br);


    bool isPossiblePlaceOnTopOfBox(const Rectangle& rec);
    void placeOnTopOfBox(const Rectangle& rec);


    bool isPossiblePlaceOnRightHandSide(const Rectangle& rec);
    void placeOnRightHandSide(const Rectangle& rec);

    std::vector<Rectangle> container;


    Coords getTopLeft() { return topLeft; }
    Coords getTopRight() { return topRight; }
    Coords getBottomLeft() { return bottomLeft; }
    Coords getBottomRight() { return bottomRight; }

    void setTopLeft(Coords coords) { topLeft = coords; }
    void setTopRight(Coords coords) { topRight = coords; }
    void setBottomLeft(Coords coords) { bottomLeft = coords; }
    void setBottomRight(Coords coords) { bottomRight = coords; }

    void print();


};

#endif // RECTANGLE_H