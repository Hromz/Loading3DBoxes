#pragma once
#ifndef CONTAINER_H
#define CONTAINER_H
#include "rectangle.h"


class Container : Rectangle
{
private:
    Rectangle container;
    std::vector<Rectangle> loadingContainer;
public:
    Container() {};
    Container(int length, int height, int width);
    ~Container() {};

    std::vector<Rectangle> boxesToBeLoaded;

    bool containerCollision(Rectangle& rec);
    bool collisionInsideContainer(Rectangle & rec);
    bool boxCollision(Rectangle & rec, Rectangle & boxInContainer);
    void placeInside(std::vector<Rectangle> & Boxes);

    Rectangle changeCoordsPlacingTop(Rectangle& rec, Rectangle & cont);
    Rectangle changeCoordsPlacingRHS(Rectangle& rec, Rectangle & cont);

    bool isPossiblePlaceOnTopOfBox(Rectangle& rec);//, Rectangle & cont);
    bool isPossiblePlaceOnRightHandSide(Rectangle& rec);//, Rectangle & cont);


    //void print();
    void printCoords();
};
#endif 