#include <iostream>
#include "rectangle.h"
#include "Container.h"
#include <stdlib.h>
#include <chrono>
#include <algorithm>
using namespace std::chrono;

int main()
{
    int test = 2;
    double temp = 2;
    using std::cout;
    using std::cin;
    int length = 360, height = 160, width = 140;
    double carCube = ((double)length / 100.0) * ((double)width / 100.0) * ((double)height / 100.0);

    int wrong = 0, right = 0;

    double total = 0;

    while (test--) {
        std::vector<Container> subContainers;
        for (int i = 0; i < 1; i++) {
            Container cont(length, height, width);
            subContainers.push_back(cont);
        }

        int totalQuan = 0;
        double orderCube = 0;
        int qBox = 15;
        std::vector<Rectangle> boxes;
        while (qBox--) {
            int quantity = rand() % 45 + 10, boxLength = rand() % 70 + 15, boxHeight = rand() % 50 + 15, boxWidth = rand() % 50 + 15;

            for (int i = 0; i < quantity; i++) {
                boxes.push_back(Rectangle(boxLength, boxHeight, boxWidth));
            }
            totalQuan += quantity;
            orderCube += ((((double)boxLength / 100.0) * ((double)boxWidth / 100.0) * ((double)boxHeight / 100.0)) * quantity);
           // cout << "\n Quantity " << quantity << " length " << boxLength << " width " << boxWidth << " height " << boxHeight << '\n';
        }
        double totalVolume = 0;
        auto start = high_resolution_clock::now();
        for (int i = 0; i < 1; i++) {
            subContainers[i].loadBoxes(boxes);
           totalVolume += subContainers[i].getLoadedVolume();
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        cout << "Loaded volume is " << totalVolume << '\n';
        cout << "Initially were " << totalQuan << '\n';
        cout << "Car cube is " << carCube << " " << "initial order cube " << orderCube << '\n';
        cout << "Runtime is " <<  (double)duration.count() / 1e6 << "sec\n";

        for (int i = 0; i < 1; i++) {
            subContainers[i].printCoords();
        }
    }


    return 0;
}
