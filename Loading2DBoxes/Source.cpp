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
    int test = 12; float length = 1360, height = 200, width = 240;
    float carCube = (length / 100.0f) * (width / 100.0f) * (height / 100.0f);
    cout << "Car cube is " << carCube << "\n";

    while (test--) {
        int totalQuan = 0, boxLeft = 0, totalBoxes = 0, qBox = 35;
        float orderCube = 0, totalCubes = 0;
        //Rectangle, quanity and is merged box
        std::vector<std::pair<Rectangle, std::pair<int, bool>>> boxes;

        while (qBox--) {
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(20, 71);
            std::uniform_int_distribution<std::mt19937::result_type> dist5(15, 25);
            int quantity = dist5(rng); float boxLength = dist6(rng), boxHeight = dist6(rng), boxWidth = dist6(rng);

            Rectangle temp(boxLength, boxHeight, boxWidth);

            boxes.push_back({ temp, {quantity, false } });
            totalQuan += quantity;
            orderCube += ((boxLength * boxWidth * boxHeight) / 1000000.0f) * quantity;

        }

        std::vector<Container> subContainer(4, Container(length/2.0f , height, width/ 2.0f));
        subContainer[0].merge_boxes(boxes);
        for (int i = 0; i < (int)subContainer.size(); i++) {
            int check = 701;

            std::vector<std::pair<double, int>> vec;
            Container tCont(length / 2.0f, height, width / 2.0f);
            while (check--) {
                std::random_shuffle(boxes.begin(), boxes.end());
                tCont.loadBoxes(boxes);
                float totalVolume = tCont.getLoadedVolume();

                    if (vec.size() > 0 && vec[0].first < totalVolume) {
                        vec.pop_back();
                        vec.push_back({ totalVolume, (int)tCont.getLoadingContainerSize() });
                        subContainer[i] = tCont;
                    }
                    if (vec.size() == 0) {
                        vec.push_back({ totalVolume, (int)tCont.getLoadingContainerSize() });
                        subContainer[i] = tCont;
                    }
                    if (vec[0].first >= tCont.getContainerCube() * 0.97f) {
                        break;
                    }
                tCont.clearContainer();
            }
            totalBoxes += vec[0].second;
            boxes = subContainer[i].getBoxesLeft();
        }

        subContainer[0].unmerge_loadBoxes(boxes);
        sort(boxes.begin(), boxes.end(), [](std::pair<Rectangle, std::pair<int, bool>>& rec1, std::pair <Rectangle, std::pair<int, bool>>& rec2) {
            return rec1.first > rec2.first;       
        });

        for (auto& b : boxes) {
              for (auto& cont : subContainer) {
                  while(b.second.first) {
                      bool flag = false;
                      cont.bruteForce_Loading(b.first, flag);
                      if (flag) {
                          totalBoxes++;
                          b.second.first--;
                      }else {
                          break;
                      }
                  }
                  if (b.second.first == 0) break;
             } 
        }
        cout << "\n";
        
        for (auto& cont : subContainer) {
           // if (!cont.isLoadingCorrect()) cout << "Fail\n";
            cout.precision(5);
            cout << "Subcontainer cubes are " << cont.getContainerCube() << " ";
            cout << "Subcontainer is loaded for " << cont.getLoadedVolume() << "\n";
            totalCubes += cont.getLoadedVolume();
        }


        float cubes_left = 0;
        int boxes_left = 0;
        for (auto box : boxes) {
            if (box.second.first > 0) {
                boxes_left += box.second.first;
                cubes_left += (box.first.getCube() / 1000000.0f)* box.second.first;
            }
        }
        cout.precision(3);
        cout << "Order cube is " << orderCube << "\n";
        cout << "Total loaded cubes are " << totalCubes << " " << "quantity of boxes are " << totalBoxes << "\n";
        cout << "Boxes left are " << boxes_left << " left and their volume is " << cubes_left << "\n";
        cout << "Resuidal space is " << carCube - totalCubes << "\n";

        cout << "------------------------------------------------\n";
    }

    return 0;
}
