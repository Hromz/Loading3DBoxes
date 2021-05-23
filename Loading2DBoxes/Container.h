#pragma once
#include "rectangle.h"


class Container : Rectangle
{
private:
    Rectangle container;
    std::vector<Rectangle> loadingContainer;
public:
    Container() {};
    Container(int length, int height);
    ~Container() {};

    bool containerCollision(Rectangle& rec);
    bool collisionInsideContainer(Rectangle & rec);
    bool boxCollision(Rectangle & rec, Rectangle & boxInContainer);
    void placeInside(const Rectangle& rec);

    Rectangle changeCoordsPlacingTop(Rectangle& rec, Rectangle & cont);
    Rectangle changeCoordsPlacingRHS(Rectangle& rec, Rectangle & cont);

    bool isPossiblePlaceOnTopOfBox(Rectangle& rec, Rectangle & cont);
    bool isPossiblePlaceOnRightHandSide(Rectangle& rec, Rectangle & cont);


    void print();
    void printCoords();
    void printBoxes();
};