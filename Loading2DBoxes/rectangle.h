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
    Rectangle(int length,int height, int width);
    ~Rectangle() { };

    Coords gettopLeftLHS() { return topLeftLHS; }
    Coords getTopRight() { return topRightLHS; }
    Coords getBottomLeft() { return bottomLeftLHS; }
    Coords getBottomRight() { return bottomRightLHS; }

    int getLength(){ return bottomRightLHS.getX() - bottomLeftLHS.getX(); }
    int getHeight() { return topRightLHS.getY() - bottomRightLHS.getY(); }
    int getWidth() { return topRightRHS.getZ() - topRightLHS.getZ(); }
    int getCube() { return (getLength() * getHeight() * getWidth());  }
    int getArea() { return (getLength() * getWidth()); }

    int getX() { return topRightLHS.getX(); }
    int getY() { return topRightLHS.getY(); }
    int getZ() { return topRightRHS.getZ(); }

    int getMinY() { return bottomLeftLHS.getY(); }
    int getMinZ() { return bottomLeftLHS.getZ(); }
    int getMinX() { return bottomLeftLHS.getX(); }

    int getMaxX() { return topRightRHS.getX(); }
    int getMaxY() { return topRightRHS.getY(); }
    int getMaxZ() { return topRightRHS.getZ(); }


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
    void setRectangle(int length,int height, int width);

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
   /*
   * 
   * // shorter
std::vector<int (*)(int)> v;
v.push_back(mult);
b = v[0](2);        // The value of b is 4.
     int Function(int Arg)
   {
       // ...
   }

   int(*Ptr[3])(int);

   Ptr[0] = &Function;

   // Call the function:
   Ptr[0](10);


    RotateBox[0] = &turnSideFront;
   RotateBox[1] = &turnBottomFront;
   RotateBox[2] = &turnSideDown;
   RotateBox[3] = &turnSideUpFront;
   RotateBox[4] = &turnBottomUpFront;
	std::vector<std::function<void()> > funcs;

	funcs.push_back(f1);
	funcs.push_back(f2);
	funcs.push_back(f3);

	for(size_t f = 0; f < funcs.size(); ++f)
		funcs[f]();

	return 0;
   */

  // Rectangle *(*RotateBox[])(int length, int width, int height) = { turnSideFront, turnBottomFront, turnSideDown, turnSideUpFront, turnBottomUpFront };


   /*
 void test1();
void test2();        
   void test3();

  
   void (*functptr[])() = { test1, test2, test3 };

void main()
{
    void (*functptr[])() = { test1, test2, test3 } ;

void main()
{
   (*functptr[0])();  
   (*functptr[1])();   
   (*functptr[2])();    
}
}
   */



   /*void rotateBox(Rectangle& rec, int contLength) {
       Rectangle temp = rec;
       int len = contLength;
       int cur = len / rec.getLength();
       int l = rec.getLength(), w = rec.getWidth(), h = rec.getHeight();

       Rectangle temp1, temp2, temp3, temp4, temp5;
       temp1 = temp2 = temp3 = temp4 = temp5 = temp;
       int cur1, cur2, cur3, cur4, cur5;

       temp1 = temp1.turnBottomFront(l,w,h);
       cur1 = len / temp1.getLength();

       temp2 = temp2.turnSideDown(l, w, h);
       cur2 = len / temp2.getLength();

       temp3 = temp3.turnSideFront(l, w, h);
       cur3 = len / temp3.getLength();

       temp4 = temp4.turnSideUpFront(l, w, h);
       cur4 = len / temp4.getLength();

       temp5 = temp5.turnBottomUpFront(l, w, h);
       cur5 = len / temp5.getLength();

       if (cur1 >= cur && cur1 >= cur2 && cur1 >= cur3 && cur1 >= cur4 && cur1 >= cur5) {
          rec.turnBottomFront(l, w, h);
       }
       else if (cur2 >= cur && cur2 >= cur1 && cur2 >= cur3 && cur2 >= cur4 && cur2 >= cur5) {
           rec.turnSideDown(l, w, h);
       }
       else if (cur3 >= cur && cur3 >= cur1 && cur3 >= cur2 && cur3 >= cur4 && cur3 >= cur5) {
           rec.turnSideFront(l, w, h);
       }
       else if (cur4 >= cur && cur4 >= cur1 && cur4 >= cur2 && cur4 >= cur3 && cur4 >= cur5) {
           rec.turnSideUpFront(l, w, h);
       }
       else if (cur5 >= cur && cur5 >= cur1 && cur5 >= cur2 && cur5 >= cur3 && cur5 >= cur4) {
           rec.turnBottomUpFront(l, w, h);
       }

   }*/
