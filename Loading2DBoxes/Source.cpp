#include <iostream>
#include "rectangle.h"
#include "Container.h"

int main()
{
    int length = 200, height = 140, width = 180;
   /* cout << "Enter 2D size of container\n";
    cout << "Length: "; cin >> length;
    cout << "Height: "; cin >> height;*/

    /*Coords tl(0, height);
    Coords bl(0, 0);
    Coords br(length, 0);
    Coords tr(length, height);*/

   // Rectangle temp(tl, tr, bl, br);
    Container cont(length, height, width);

    int quantity = 416, boxLength =33, boxHeight = 25, boxWidth = 15;
   /* cout << "Enter 2D box quantity: "; cin >> quantity;
    cout << "Length: "; cin >> boxLength;
    cout << "Height: "; cin >> boxHeight;*/

   // cont.setOptimalLoading(boxLength, boxHeight, boxWidth);
    std::vector<Rectangle> boxes(quantity, Rectangle(boxLength, boxHeight, boxWidth));
    
    cont.placeInside(boxes);

    cont.printCoords();

    return 0;
}
