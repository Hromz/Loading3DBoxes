#include <iostream>
#include "rectangle.h"
#include "Container.h"

using namespace std;


int main(int argc, char** argv)
{
    int length = 150, height = 150;
   /* cout << "Enter 2D size of container\n";
    cout << "Length: "; cin >> length;
    cout << "Height: "; cin >> height;*/

    Coords tl(0, height);
    Coords bl(0, 0);
    Coords br(length, 0);
    Coords tr(length, height);

   // Rectangle temp(tl, tr, bl, br);
    Container cont(length, height);

    int quantity = 25, boxLength = 4, boxHeight = 3;
   /* cout << "Enter 2D box quantity: "; cin >> quantity;
    cout << "Length: "; cin >> boxLength;
    cout << "Height: "; cin >> boxHeight;*/

    std::vector<Rectangle> boxes(quantity, Rectangle(boxLength, boxHeight));
    
    cont.placeInside(boxes);

    cont.printCoords();

    return 0;
}
