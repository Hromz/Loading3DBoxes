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
    int test = 6, length = 1360, height = 200, width = 240;
    double carCube = ((double)length / 100.0) * ((double)width / 100.0) * ((double)height / 100.0);
    cout << "Car cube is " << carCube << "\n";

    while (test--) {
        int totalQuan = 0, boxLeft = 0, totalBoxes = 0, qBox = 14;
        double orderCube = 0, totalCubes = 0;
        //Rectangle, quanity and is merged box
        std::vector<std::pair<Rectangle, std::pair<int, bool>>> boxes;

        while (qBox--) {
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(25, 60);
            std::uniform_int_distribution<std::mt19937::result_type> dist5(50, 90);
            int quantity = dist5(rng), boxLength = dist6(rng), boxHeight = dist6(rng), boxWidth = dist6(rng);

            if (boxHeight > boxLength) {
                std::swap(boxHeight, boxLength);
            }
            if (boxWidth > boxLength) {
                std::swap(boxWidth, boxLength);
            }


            Rectangle temp(boxLength, boxHeight, boxWidth);

            boxes.push_back({ temp, {quantity, false } });
            totalQuan += quantity;
            orderCube += (((double)boxLength * (double)boxWidth * (double)boxHeight) / 1000000.0) * quantity;

        }

        std::vector<Container> subContainer(4, Container(length / 2, height / 2, width));
        for (int i = 0; i < 4; i++) {
            int check = 55 * (i+2);

            std::vector<std::pair<double, int>> vec;

            while (check--) {
                std::vector<std::pair<Rectangle, std::pair<int, bool>>> tempBoxes;

                Container tCont(length / 2, height / 2, width);
                tCont.loadBoxes(boxes);

                double totalVolume = tCont.getLoadedVolume();

                if (tCont.container.getCube() / 1000000.0 >= totalVolume) {
                    if (vec.size() > 0 && vec[0].first < totalVolume) {
                        vec.pop_back();
                        vec.push_back({ totalVolume, (int)tCont.loadingContainer.size() });
                        subContainer[i] = tCont;
                    }
                    if (vec.size() == 0) {
                        vec.push_back({ totalVolume, (int)tCont.loadingContainer.size() });
                        subContainer[i] = tCont;
                    }
                }
            }
            totalBoxes += vec[0].second;
            boxes = subContainer[i].boxesLeft;
        }

        for (auto& b : boxes) {
              for (auto& cont : subContainer) {
                  int q = b.second.first;
                  while(q--) {
                      bool flag = false;
                      cont.bruteForce_Loading(b.first, flag);
                      if (flag) {
                          totalBoxes++;
                          b.second.first--;
                      }
                  }  
             } 
        }

        for (auto& cont : subContainer) {
            cout.precision(4);
            cout << "Subcontainer cubes are " << cont.container.getCube() / 1000000.0 << " ";
            cout << "Subcontainer is loaded for " << cont.getLoadedVolume() << "\n";
            totalCubes += cont.getLoadedVolume();
        }


        double cubes_left = 0;
        int boxes_left = 0;
        for (auto box : boxes) {
            if (box.second.first > 0) {
                boxes_left += box.second.first;
            }
        }
        cout.precision(3);
        cout << "Order cube is " << orderCube << "\n";
        cout << "Total loaded cubes are " << totalCubes << " " << "quantity of boxes are " << totalBoxes << "\n";
        cout << "Boxes left are " << boxes_left << " left and their volume is " << orderCube - totalCubes << "\n";
        cout << "Resuidal sapce is " << carCube - totalCubes << "\n";

        cout << "------------------------------------------------\n";
    }

    return 0;
}
