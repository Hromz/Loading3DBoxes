#include <iostream>
#include "rectangle.h"
#include "Container.h"

using namespace std;

int main()
{
    int length = 134000, height = 25000;
   /* cout << "Enter 2D size of container\n";
    cout << "Length: "; cin >> length;
    cout << "Height: "; cin >> height;*/

    Coords tl(0, height);
    Coords bl(0, 0);
    Coords br(length, 0);
    Coords tr(length, height);

   // Rectangle temp(tl, tr, bl, br);
    Container cont(length, height);

    int quantity = 600000, boxLength = 3, boxHeight = 4;
   /* cout << "Enter 2D box quantity: "; cin >> quantity;
    cout << "Length: "; cin >> boxLength;
    cout << "Height: "; cin >> boxHeight;*/

    std::vector<Rectangle> boxes(quantity, Rectangle(boxLength, boxHeight));
    
    cont.placeInside(boxes);

    cont.printCoords();
    //cont.printBoxes();

    return 0;
}
