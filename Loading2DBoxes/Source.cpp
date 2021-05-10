#include <iostream>
#include "rectangle.h"

using namespace std;

int main()
{
    float length, height;
    cout << "Enter 2D size of container\n";
    cout << "Length: "; cin >> length;
    cout << "Height: "; cin >> height;

    Coords tl(0, height);
    Coords bl(0, 0);
    Coords br(length, 0);
    Coords tr(length, height);

    Rectangle cont(tl, tr, bl, br);

    int quantity, boxLength, boxHeight;
    cout << "Enter 2D box quantity: "; cin >> quantity;
    cout << "Length: "; cin >> boxLength;
    cout << "Height: "; cin >> boxHeight;

    Rectangle box(boxLength, boxHeight);

    for (int i = 0; i < quantity; i++)
    {
        cont.placeInside(box);
    }

    cont.print();

    return 0;
}
