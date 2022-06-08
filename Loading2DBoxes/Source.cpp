#include <iostream>
#include "rectangle.h"
#include "Container.h"
#include <stdlib.h>
#include <chrono>
#include <algorithm>
using namespace std::chrono;
using std::cout;
using std::cin;

int main()
{
    int test = 20;
    int length = 1360, height = 190, width = 240;
    double carCube = ((double)length / 100.0) * ((double)width / 100.0) * ((double)height / 100.0);
    Container cont;
    cout << "Car cube is " << carCube << "\n";
    while (test--) {
        int check = 201;
        std::vector<std::pair<double, int>> vec;
        int totalQuan = 0;
        double orderCube = 0;
        int qBox = 8;
        std::vector<Rectangle> boxes;
       
        while (qBox--) {
            int quantity = rand() % 85 + 60, boxLength = rand() % 60 + 20, boxHeight = rand() % 60 + 20, boxWidth = rand() % 60 + 20;

            for (int i = 0; i < quantity; i++) {
                boxes.push_back(Rectangle(boxLength, boxHeight, boxWidth));
            }
            totalQuan += quantity;
            orderCube += (((double)boxLength * (double)boxWidth * (double)boxHeight) / 1000000.0) * quantity;
        }

        while (check--) {

            std::vector<Container> subContainers;
            for (int i = 0; i < 1; i++) {
                Container cont(length, height, width);
                subContainers.push_back(cont);
            }

            long double totalVolume = 0;
            auto start = high_resolution_clock::now();
            for (int i = 0; i < 1; i++) {
                subContainers[i].loadBoxes(boxes);
                totalVolume += subContainers[i].getLoadedVolume();
            }
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            if (carCube >= totalVolume) {
                if (vec.size() > 0 && vec[0].first < totalVolume) {
                    vec.pop_back();
                    totalVolume += 0.005;
                    vec.push_back({ totalVolume, totalQuan });
                    cont = subContainers[0];
                }
                if(vec.size() == 0) vec.push_back({ totalVolume, totalQuan });

            }
        }
        cout << cont.isLoadingCorrect() << "\n";
        cout.precision(3);
        cout << "Order cube is " << orderCube << "\n";
            cout << "Total loaded cubes are " << vec[0].first << " " << "quantity of boxes are " << cont.loadingContainer.size() * 2 << "\n";
            cout << "Boxes left are " << cont.boxes_left << " resiudal space is " << carCube - vec[0].first << "\n";
       
        cout << "------------------------------------------------\n";
       //cont.printCoords();
    }


    return 0;
}
