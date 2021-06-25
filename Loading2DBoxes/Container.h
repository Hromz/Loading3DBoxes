#pragma once
#ifndef CONTAINER_H
#define CONTAINER_H
#include "rectangle.h"

class Container : Rectangle
{
private:
    Rectangle container;
    std::vector<std::vector<Rectangle>> loadingMap;
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

    //Searching place where to palce box inside container
    Rectangle changeCoordsPlacingTop(Rectangle& rec, Rectangle & cont);
    Rectangle changeCoordsPlacingRHS(Rectangle& rec, Rectangle & cont);
    Rectangle changeCoordsPlacingFront(Rectangle& rec, Rectangle& cont);

    bool isPossiblePlaceOnTopOfBox(Rectangle& rec);//, Rectangle & cont);
    bool isPossiblePlaceOnRightHandSide(Rectangle& rec);//, Rectangle & cont);
    bool isPossiblePlaceInfront(Rectangle & rec);

    //void print();
    int getQuanAlongSide(int side1, side2);
    void setOptimalLoading(int& length, int& width, int& height);
    void setOptimalLoadingMap(int length, int width, int height);
    void printCoords();
};
#endif 