#include <iostream>
#include "rectangle.h"
#include "Container.h"
#include <stdlib.h>
#include <chrono>
#include <algorithm>
using namespace std::chrono;

int main()
{
    int test = 15;
    double temp = 2;
    using std::cout;
    using std::cin;
    int length = 360, height = 170, width = 150;
    double carCube = ((double)length / 100.0) * ((double)width / 100.0) * ((double)height / 100.0);

    int wrong = 0, right = 0;

    double total = 0;
    cout << "Car cube is " << carCube << "\n";
    while (test--) {
        int check = 101;
        std::vector<std::pair<double, int>> vec;
        while (check--) {

            std::vector<Container> subContainers;
            for (int i = 0; i < 1; i++) {
                Container cont(length, height, width);
                subContainers.push_back(cont);
            }

            int totalQuan = 0;
            double orderCube = 0;
            int qBox = 6;
            std::vector<Rectangle> boxes;
            while (qBox--) {
                int quantity = rand() % 45 + 20, boxLength = rand() % 40 + 15, boxHeight = rand() % 40 + 15, boxWidth = rand() % 40 + 15;

                for (int i = 0; i < quantity; i++) {
                    boxes.push_back(Rectangle(boxLength, boxHeight, boxWidth));
                }
                totalQuan += quantity;
                orderCube += ((((double)boxLength / 100.0) * ((double)boxWidth / 100.0) * ((double)boxHeight / 100.0)) * quantity);
                // cout << "\n Quantity " << quantity << " length " << boxLength << " width " << boxWidth << " height " << boxHeight << '\n';
            }
            long double totalVolume = 0;
            auto start = high_resolution_clock::now();
            for (int i = 0; i < 1; i++) {
                subContainers[i].loadBoxes(boxes);
                totalVolume += subContainers[i].getLoadedVolume();
            }
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            /*cout << "Loaded volume is " << totalVolume << '\n';
            cout << "Initially were " << totalQuan << '\n';
            cout << "Car cube is " << carCube << " " << "initial order cube " << orderCube << '\n';
            cout << "Runtime is " << (double)duration.count() / 1e6 << "sec\n";
            */

            if (carCube >= totalVolume) {
                if (vec.size() > 0 && vec[0].first < totalVolume) {
                    vec.pop_back();
                    totalVolume += 0.005;
                    vec.push_back({ totalVolume, totalQuan });
                }
                if(vec.size() == 0) vec.push_back({ totalVolume, totalQuan });

            }
        }
        cout.precision(3);
            cout << "Total loaded cubes are " << vec[0].first << " " << "quantity of boxes are " << vec[0].second << "\n";
       
        cout << "------------------------------------------------\n";
    }


    return 0;
}
