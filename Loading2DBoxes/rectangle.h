#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "coords.h"
#include <vector>
#include <utility>
#include <iostream>
#include <functional>

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


    Rectangle() {
        rotate[0] = &Rectangle::turnBottomFront;
        rotate[1] = &Rectangle::turnBottomUpFront;
        rotate[2] = &Rectangle::turnSideDown;
        rotate[3] = &Rectangle::turnSideFront;
        rotate[4] = &Rectangle::turnSideUpFront;
    };
    Rectangle(const Rectangle & rec);
    Rectangle(Coords& tl, Coords& tp, Coords& bl, Coords& br, Coords& tlr, Coords& tpr, Coords& blr, Coords& brr);
    Rectangle(float length,float height, float width);
    ~Rectangle() { };

    Coords gettopLeftLHS() { return topLeftLHS; }
    Coords getTopRight() { return topRightLHS; }
    Coords getBottomLeft() { return bottomLeftLHS; }
    Coords getBottomRight() { return bottomRightLHS; }

    float getLength(){ return bottomRightLHS.getX() - bottomLeftLHS.getX(); }
    float getHeight() { return topRightLHS.getY() - bottomRightLHS.getY(); }
    float getWidth() { return topRightRHS.getZ() - topRightLHS.getZ(); }
    float getCube() { return (getLength() * getHeight() * getWidth());  }
    float getArea() { return (getLength() * getWidth()); }

    float getX() { return topRightLHS.getX(); }
    float getY() { return topRightLHS.getY(); }
    float getZ() { return topRightRHS.getZ(); }

    float getMinY() { return bottomLeftLHS.getY(); }
    float getMinZ() { return bottomLeftLHS.getZ(); }
    float getMinX() { return bottomLeftLHS.getX(); }

    float getMaxX() { return topRightRHS.getX(); }
    float getMaxY() { return topRightRHS.getY(); }
    float getMaxZ() { return topRightRHS.getZ(); }


    void settopLeftLHS(Coords & coords) { topLeftLHS = coords; }
    void setTopRight(Coords & coords) { topRightLHS = coords; }
    void setBottomLeft(Coords & coords) { bottomLeftLHS = coords; }
    void setBottomRight(Coords & coords) { bottomRightLHS = coords; }

    void setTopLeftLHS(Coords & coords) { topLeftLHS = coords; }
    void setTopRightRight(Coords & coords) { topRightRHS = coords; }
    void setBottomLeftRight(Coords & coords) { bottomLeftRHS = coords; }
    void setBottomRightRight(Coords & coords) { bottomRightRHS = coords; }

    friend bool operator>(Rectangle & rec1, Rectangle& rec2) {
        return (rec1.topLeftLHS > rec2.topLeftLHS && rec1.topLeftRHS > rec2.topLeftRHS && rec1.topRightLHS > rec2.topRightLHS && rec1.topRightRHS > rec2.topRightRHS &&
            rec1.bottomLeftLHS > rec2.bottomLeftLHS && rec1.bottomLeftRHS > rec2.bottomLeftRHS && rec1.bottomRightLHS > rec2.bottomRightLHS && rec1.bottomRightRHS > rec2.bottomRightRHS);
       // return (rec1.getX() > rec2.getX() && rec1.getY() > rec2.getY() && rec1.getZ() > rec2.getZ());
    }

    friend bool operator<(Rectangle& rec1, Rectangle& rec2) {
        return (rec1.topLeftLHS < rec2.topLeftLHS&& rec1.topLeftRHS < rec2.topLeftRHS&& rec1.topRightLHS < rec2.topRightLHS&& rec1.topRightRHS < rec2.topRightRHS&&
            rec1.bottomLeftLHS < rec2.bottomLeftLHS && rec1.bottomLeftRHS < rec2.bottomLeftRHS && rec1.bottomRightLHS < rec2.bottomRightLHS && rec1.bottomRightRHS < rec2.bottomRightRHS);
        //return (rec1.getX() < rec2.getX() && rec1.getY() < rec2.getY() && rec1.getZ() < rec2.getZ());
    }

    friend bool operator==(Rectangle& rec1, Rectangle& rec2) {
        return (rec1.topLeftLHS == rec2.topLeftLHS && rec1.topLeftRHS == rec2.topLeftRHS && rec1.topRightLHS == rec2.topRightLHS && rec1.topRightRHS == rec2.topRightRHS &&
            rec1.bottomLeftLHS == rec2.bottomLeftLHS && rec1.bottomLeftRHS == rec2.bottomLeftRHS && rec1.bottomRightLHS == rec2.bottomRightLHS && rec1.bottomRightRHS == rec2.bottomRightRHS);
       // return (rec1.getX() == rec2.getX() && rec1.getY() == rec2.getY() && rec1.getZ() == rec2.getZ());
    }

    // length - x, height - y, width - z
    void setRectangle(float length,float height, float width);

   friend std::ostream & operator<<(std::ostream & os, const Rectangle& rec) {
       os << "LHS\n";
       os << "topLeft " << rec.topLeftLHS << " topRight " << rec.topRightLHS << '\n';
       os << "bottomLeft " << rec.bottomLeftLHS << " bottomRight " << rec.bottomRightLHS << '\n';
       os << "RHS\n";
       os << "topLeft " << rec.topLeftRHS << " topRight " << rec.topRightRHS << '\n';
       os << "bottomLeft " << rec.bottomLeftRHS << " bottomRight " << rec.bottomRightRHS << '\n';

       return os;
    }

   void leaveBoxBe() {}
   void turnSideFront();
   void turnBottomFront();
   void turnSideDown();
   void turnSideUpFront();
   void turnBottomUpFront();

   typedef void(Rectangle::*rotator)();
   rotator rotate[6];
};
#endif // RECTANGLE_H