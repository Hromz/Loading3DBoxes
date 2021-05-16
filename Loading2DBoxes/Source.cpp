#include <iostream>
#include "rectangle.h"

using namespace std;

int main()
{
    int length = 4, height = 4;
   /* cout << "Enter 2D size of container\n";
    cout << "Length: "; cin >> length;
    cout << "Height: "; cin >> height;*/

    Coords tl(0, height);
    Coords bl(0, 0);
    Coords br(length, 0);
    Coords tr(length, height);

    Rectangle cont(tl, tr, bl, br);

    int quantity = 4, boxLength = 2, boxHeight = 2;
   /* cout << "Enter 2D box quantity: "; cin >> quantity;
    cout << "Length: "; cin >> boxLength;
    cout << "Height: "; cin >> boxHeight;*/

    Rectangle box(boxLength, boxHeight);

    for (int i = 0; i < quantity; i++)
    {
        cont.placeInside(box);
    }

    cont.printCoords();

    return 0;
}
