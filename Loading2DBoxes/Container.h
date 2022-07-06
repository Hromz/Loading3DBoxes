#pragma once
#ifndef CONTAINER_H
#define CONTAINER_H
#include "rectangle.h"
#include <algorithm>
#include <functional>
#include <random>
#include <cmath>

class Container : Rectangle
{   
public:
    std::vector<Rectangle> loadingContainer;
    Rectangle container;
    std::vector<Rectangle> boxesToBeLoaded;
    std::vector<std::pair<Rectangle, std::pair<int, bool>>> boxesLeft;

    double loadedVolume = 0;
    int boxes_left = 0;

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

    bool containerCollision(Rectangle& rec);
    bool collisionInsideContainer(Rectangle & rec, int pos);
    bool noCollision(Rectangle & rec, Rectangle & boxInContainer);
    bool isFull(Rectangle & rec);
    bool isLoadingCorrect();


    std::vector<Rectangle> getConainer() { return loadingContainer; }
    void merge_boxes(std::vector<std::pair<Rectangle, std::pair<int, bool>>>& vec);

    Rectangle changeCoordsPlacingTop(Rectangle& rec, Rectangle & cont);
    Rectangle changeCoordsPlacingRHS(Rectangle& rec, Rectangle & cont);
    Rectangle changeCoordsPlacingFront(Rectangle& rec, Rectangle& cont);
 
    void printCoords();
    void bruteForce_Loading(Rectangle& rec, bool& flag);
    void loadBoxes(std::vector<std::pair<Rectangle, std::pair<int, bool>>> boxes);
    void unmerge_loadBoxes(std::vector<std::pair<Rectangle, std::pair<int, bool>>> & boxes);
    void Insert(Rectangle& rec);

    Rectangle binarySearchRHS(Rectangle& rec, bool & flag);
    Rectangle binarySearchTop(Rectangle& rec, bool & flag);
    Rectangle binarySearchFront(Rectangle& rec, bool & flag);

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

    Container & operator=(const Container& cont) {
        loadingContainer = cont.loadingContainer;
        container = cont.container;
        boxesToBeLoaded = cont.boxesToBeLoaded;
        boxesLeft = cont.boxesLeft;

        loadedVolume = cont.loadedVolume;
        boxes_left = cont.boxes_left;

        return *this;
    }
};
#endif 