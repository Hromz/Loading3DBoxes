#pragma once
#ifndef CONTAINER_H
#define CONTAINER_H
#include "rectangle.h"
#include <map>
#include <queue>
#include <algorithm>
#include <functional>
#include "N-AryTree.h"
#include <random>
#include <cmath>

class Container : Rectangle
{
private:  
    
public:
    std::vector<Rectangle> loadingContainer;
    Rectangle container;
    std::vector<Rectangle> boxesToBeLoaded;

    double loadedVolume = 0;

    void setLoadedVolume(double vol) { loadedVolume = vol; }
    double getLoadedVolume() { return loadedVolume; }

    Container() {};
    Container(int length, int height, int width);
    ~Container() {};

    int getLoadedQuan() { return (int)loadingContainer.size(); }
    typedef void (Container::* placer)(Rectangle& rec);
    placer place[6];

    typedef bool(Container::* checker)(Rectangle& rec);
    checker check[6];

    void loadBoxes(std::vector<Rectangle> & boxes);
    void generateBottomBox(std::vector<Rectangle>& temp);
    bool containerCollision(Rectangle& rec);
    bool collisionInsideContainer(Rectangle & rec, int pos);
    bool noCollision(Rectangle & rec, Rectangle & boxInContainer);
    void placeInside(std::vector<Rectangle> & Boxes);
    bool isFull(Rectangle & rec);
    void Insert(Rectangle & rec);
    std::vector<Rectangle> getConainer() { return loadingContainer; }

    std::vector<std::pair<Rectangle, int>> merge_boxes(std::vector<std::pair<Rectangle, int>>& vec);


    Rectangle changeCoordsPlacingTop(Rectangle& rec, Rectangle & cont);
    Rectangle changeCoordsPlacingRHS(Rectangle& rec, Rectangle & cont);
    Rectangle changeCoordsPlacingFront(Rectangle& rec, Rectangle& cont);

    bool isLoadingCorrect();

    void sortBoxes(std::vector<Rectangle> & boxes);
    int getQuanAlongSide(int side1, int side2);
    void setOptimalLoadingMap(int length, int width, int height);
    void printCoords();

    Rectangle binarySearchRHS(Rectangle& rec, bool & flag);
    Rectangle binarySearchTop(Rectangle& rec, bool & flag);
    Rectangle binarySearchFront(Rectangle& rec, bool & flag);

    void bruteForce_Loading(Rectangle& rec, bool & flag);

    void bs_RF(Rectangle& rec);
    void bs_RU(Rectangle& rec);
    void bs_UF(Rectangle& rec);
    void bs_UR(Rectangle& rec);
    void bs_FR(Rectangle& rec);
    void bs_FU(Rectangle& rec);

    bool isFull_RF(Rectangle& rec);
    bool isFull_RU(Rectangle& rec);
    bool isFull_UF(Rectangle& rec);
    bool isFull_UR(Rectangle& rec);
    bool isFull_FR(Rectangle& rec);
    bool isFull_FU(Rectangle& rec);
};
#endif 