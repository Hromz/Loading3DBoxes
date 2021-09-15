#include "rectangle.h"

Rectangle::Rectangle(const Rectangle & rec){
    this->topLeftLHS = rec.topLeftLHS;
    this->bottomLeftLHS = rec.bottomLeftLHS;
    this->topRightLHS = rec.topRightLHS;
    this->bottomRightLHS = rec.bottomRightLHS;

    this->topLeftRHS = rec.topLeftRHS;
    this->bottomLeftRHS = rec.bottomLeftRHS;
    this->topRightRHS = rec.topRightRHS;
    this->bottomRightRHS = rec.bottomRightRHS;

    rotate[0] = &Rectangle::leaveBoxBe;
    rotate[1] = &Rectangle::turnBottomFront;
    rotate[2] = &Rectangle::turnBottomUpFront;
    rotate[3] = &Rectangle::turnSideDown;
    rotate[4] = &Rectangle::turnSideFront;
    rotate[5] = &Rectangle::turnSideUpFront;
}

Rectangle::Rectangle(Coords& tl, Coords& tr, Coords& bl, Coords& br, Coords & tlr, Coords& tpr, Coords& blr, Coords& brr){
    topLeftLHS = tl;
    topRightLHS = tr;
    bottomLeftLHS = bl;
    bottomRightLHS = br;

    topLeftRHS = tlr;
    bottomLeftRHS = blr;
    topRightRHS = tpr;
    bottomRightRHS = brr;

    rotate[0] = &Rectangle::leaveBoxBe;
    rotate[1] = &Rectangle::turnBottomFront;
    rotate[2] = &Rectangle::turnBottomUpFront;
    rotate[3] = &Rectangle::turnSideDown;
    rotate[4] = &Rectangle::turnSideFront;
    rotate[5] = &Rectangle::turnSideUpFront;
}

Rectangle::Rectangle(int length, int height,int width){
    topLeftLHS.setCoords(0, height, 0);
    topRightLHS.setCoords(length, height, 0);
    bottomLeftLHS.setCoords(0, 0, 0);
    bottomRightLHS.setCoords(length, 0, 0);

    topLeftRHS.setCoords(0, height, width);
    topRightRHS.setCoords(length, height, width);
    bottomLeftRHS.setCoords(0, 0, width);
    bottomRightRHS.setCoords(length, 0, width);

    rotate[0] = &Rectangle::leaveBoxBe;
    rotate[1] = &Rectangle::turnBottomFront;
    rotate[2] = &Rectangle::turnBottomUpFront;
    rotate[3] = &Rectangle::turnSideDown;
    rotate[4] = &Rectangle::turnSideFront;
    rotate[5] = &Rectangle::turnSideUpFront;
}

// length - x, height - y, width - z
void Rectangle::setRectangle(int length,int height, int width){
    topLeftLHS.setCoords(0, height, 0);
    topRightLHS.setCoords(length, height, 0);
    bottomLeftLHS.setCoords(0, 0, 0);
    bottomRightLHS.setCoords(length, 0, 0);

    topLeftRHS.setCoords(0, height, width);
    bottomLeftRHS.setCoords(0, 0, width);
    topRightRHS.setCoords(length, height, width);
    bottomRightRHS.setCoords(length, 0, width);

    rotate[0] = &Rectangle::leaveBoxBe;
    rotate[1] = &Rectangle::turnBottomFront;
    rotate[2] = &Rectangle::turnBottomUpFront;
    rotate[3] = &Rectangle::turnSideDown;
    rotate[4] = &Rectangle::turnSideFront;
    rotate[5] = &Rectangle::turnSideUpFront;
}


void Rectangle::turnSideFront() {
    Rectangle temp;
    //width, length, height
    temp.setRectangle(this->getWidth(), this->getLength(), this->getHeight());
    
    this->bottomLeftLHS = temp.bottomLeftLHS;  this->bottomLeftRHS = temp.bottomLeftRHS;
    this->bottomRightLHS = temp.bottomRightLHS; this->bottomRightRHS = temp.bottomRightRHS;
    
    this->topLeftLHS = temp.topLeftLHS;  this->topLeftRHS = temp.topLeftRHS;
    this->topRightLHS = temp.topRightLHS; this->topRightRHS = temp.topRightRHS;
}

void Rectangle::turnSideUpFront() {
    Rectangle temp;
    //width, height, length
    temp.setRectangle(this->getWidth(), this->getHeight(), this->getLength());
    this->bottomLeftLHS = temp.bottomLeftLHS;  this->bottomLeftRHS = temp.bottomLeftRHS;
    this->bottomRightLHS = temp.bottomRightLHS; this->bottomRightRHS = temp.bottomRightRHS;

    this->topLeftLHS = temp.topLeftLHS;  this->topLeftRHS = temp.topLeftRHS;
    this->topRightLHS = temp.topRightLHS; this->topRightRHS = temp.topRightRHS;
}

void Rectangle::turnBottomFront() {
    Rectangle temp;
    //height, width, length
    temp.setRectangle(this->getHeight(), this->getWidth(), this->getLength());
    this->bottomLeftLHS = temp.bottomLeftLHS;  this->bottomLeftRHS = temp.bottomLeftRHS;
    this->bottomRightLHS = temp.bottomRightLHS; this->bottomRightRHS = temp.bottomRightRHS;

    this->topLeftLHS = temp.topLeftLHS;  this->topLeftRHS = temp.topLeftRHS;
    this->topRightLHS = temp.topRightLHS; this->topRightRHS = temp.topRightRHS;
}

void Rectangle::turnBottomUpFront() {
    Rectangle temp;
    //height, length, width
    temp.setRectangle(this->getHeight(),this->getLength(), this->getWidth());
    this->bottomLeftLHS = temp.bottomLeftLHS;  this->bottomLeftRHS = temp.bottomLeftRHS;
    this->bottomRightLHS = temp.bottomRightLHS; this->bottomRightRHS = temp.bottomRightRHS;

    this->topLeftLHS = temp.topLeftLHS;  this->topLeftRHS = temp.topLeftRHS;
    this->topRightLHS = temp.topRightLHS; this->topRightRHS = temp.topRightRHS;
}

void Rectangle::turnSideDown() {
    Rectangle temp;
    //length, width, height
    temp.setRectangle(this->getLength(), this->getWidth(), this->getHeight());
    this->bottomLeftLHS = temp.bottomLeftLHS;  this->bottomLeftRHS = temp.bottomLeftRHS;
    this->bottomRightLHS = temp.bottomRightLHS; this->bottomRightRHS = temp.bottomRightRHS;

    this->topLeftLHS = temp.topLeftLHS;  this->topLeftRHS = temp.topLeftRHS;
    this->topRightLHS = temp.topRightLHS; this->topRightRHS = temp.topRightRHS;
}