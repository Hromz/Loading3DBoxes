#include "Container.h"
#include <algorithm>

Container::Container(int length, int height, int width) {
    container.setRectangle(length, height, width);
    place[0] = &Container::bs_FR;
    place[1] = &Container::bs_RF;
    place[2] = &Container::bs_FU;
    place[3] = &Container::bs_RU;
    place[4] = &Container::bs_UF;
    place[5] = &Container::bs_UR;

    check[0] = &Container::isFull_FR;
    check[1] = &Container::isFull_RF;
    check[2] = &Container::isFull_FU;
    check[3] = &Container::isFull_RU;
    check[4] = &Container::isFull_UF;
    check[5] = &Container::isFull_UR;
}

bool Container::containerCollision(Rectangle & rec) {
    return (container.getX() >= rec.getX() && container.getY() >= rec.getY() && container.getZ() >= rec.getZ());
}

bool Container::noCollision(Rectangle& a, Rectangle& b) {
    /*if (a.getMinX() >= b.getMaxX()) return true;
    if(b.getMinX() >= a.getMaxX()) return true;
    if (a.getMinY() >= b.getMaxY()) return true;
    if (b.getMinY() >= a.getMaxY()) return true;
    if (a.getMinZ() >= b.getMaxZ()) return true;
    if (b.getMinZ() >= a.getMaxZ()) return true;
    
    return false;*/
/* return (a.getMinX() >= b.getMaxX() || b.getMinX() >= a.getMaxX() ||
            a.getMinY() >= b.getMaxY() || b.getMinY() >= a.getMaxY() ||
            a.getMinZ() >= b.getMaxZ() || b.getMinZ() >= a.getMaxZ());*/
   return !(abs((a.getX() + a.getLength() / 2) - (b.getX() + b.getLength() / 2)) * 2 < (a.getLength() + b.getLength()) &&
        (abs((a.getY() + a.getHeight() / 2) - (b.getY() + b.getHeight() / 2)) * 2 < (a.getHeight() + b.getHeight()) &&
            abs((a.getZ() + a.getWidth() / 2) - (b.getZ() + b.getWidth() / 2)) * 2 < (a.getWidth() + b.getWidth())));
}

Rectangle Container::changeCoordsPlacingTop(Rectangle & rec, Rectangle & boxInContainer) {
    Rectangle* temp = new Rectangle;

    //Set LHS coordinates
    temp->bottomLeftLHS = boxInContainer.topLeftLHS;
    temp->bottomRightLHS = temp->bottomLeftLHS;
    temp->bottomRightLHS.moveLengthCoordinate(rec.getLength());

    temp->topLeftLHS = temp->bottomLeftLHS;
    temp->topLeftLHS.moveHeightCoordinate(rec.getHeight());
    temp->topRightLHS = temp->bottomRightLHS;
    temp->topRightLHS.moveHeightCoordinate(rec.getHeight());
    
    //Set RHS coordinates
    temp->bottomLeftRHS = temp->bottomLeftLHS;
    temp->bottomLeftRHS.moveWidthCoordinate(rec.getWidth());
    temp->bottomRightRHS = temp->bottomRightLHS;
    temp->bottomRightRHS.moveWidthCoordinate(rec.getWidth());

    temp->topLeftRHS = temp->topLeftLHS;
    temp->topLeftRHS.moveWidthCoordinate(rec.getWidth());
    temp->topRightRHS = temp->topRightLHS;
    temp->topRightRHS.moveWidthCoordinate(rec.getWidth()); 

    return *temp;
}

Rectangle Container::changeCoordsPlacingRHS(Rectangle& rec, Rectangle& boxInContainer) {
    Rectangle* temp = new Rectangle;
    
    //Set LHS coordinates
    temp->bottomLeftLHS = boxInContainer.bottomLeftRHS;
    temp->bottomRightLHS = temp->bottomLeftLHS;
    temp->bottomRightLHS.moveLengthCoordinate(rec.getLength());

    temp->topLeftLHS = temp->bottomLeftLHS;
    temp->topLeftLHS.moveHeightCoordinate(rec.getHeight());
    temp->topRightLHS = temp->topLeftLHS;
    temp->topRightLHS.moveLengthCoordinate(rec.getLength());

    //Set RHS coordinates
    temp->bottomLeftRHS = temp->bottomLeftLHS;
    temp->bottomLeftRHS.moveWidthCoordinate(rec.getWidth());
    temp->bottomRightRHS = temp->bottomLeftRHS;
    temp->bottomRightRHS.moveLengthCoordinate(rec.getLength());

    temp->topLeftRHS = temp->bottomLeftRHS;
    temp->topLeftRHS.moveHeightCoordinate(rec.getHeight());
    temp->topRightRHS = temp->topLeftRHS;
    temp->topRightRHS.moveLengthCoordinate(rec.getLength());

    return *temp;
}

Rectangle Container::changeCoordsPlacingFront(Rectangle& rec, Rectangle& boxInContainer) {
    Rectangle* temp = new Rectangle;

    //Set LHS coordinates
    temp->bottomLeftLHS = boxInContainer.bottomRightLHS;
    temp->bottomRightLHS = temp->bottomLeftLHS;
    temp->bottomRightLHS.moveLengthCoordinate(rec.getLength());
    temp->topLeftLHS = temp->bottomLeftLHS;
    temp->topLeftLHS.moveHeightCoordinate(rec.getHeight());

    temp->topRightLHS = temp->topLeftLHS;
    temp->topRightLHS.moveLengthCoordinate(rec.getLength());

    //Set RHS coordinates
    temp->bottomLeftRHS = temp->bottomLeftLHS;
    temp->bottomLeftRHS.moveWidthCoordinate(rec.getWidth());

    temp->bottomRightRHS = temp->bottomRightLHS;
    temp->bottomRightRHS.moveWidthCoordinate(rec.getWidth());

    temp->topLeftRHS = temp->bottomLeftRHS;
    temp->topLeftRHS.moveHeightCoordinate(rec.getHeight());  
    temp->topRightRHS = temp->topLeftRHS;
    temp->topRightRHS.moveLengthCoordinate(rec.getLength());

    return *temp;
}

Rectangle Container::binarySearchRHS(Rectangle& rec, bool & flag) {
    Rectangle temp = rec;
    if (loadingContainer.size() == 1) {
        temp = changeCoordsPlacingRHS(rec, loadingContainer[0]);
        if (!collisionInsideContainer(temp, 0)) {
            flag = true;
            return temp;
        }
        else
            return rec;
    }

    int left = 0, right = (int)loadingContainer.size() - 1, middle = 0, prev = 0;

    while (left < right)
    {
        middle = (left + right) / 2;
        temp = changeCoordsPlacingRHS(rec, loadingContainer[middle]);
        if (collisionInsideContainer(temp, middle))
        {
            left = middle + 1;
            prev = middle;
        }
        else {
            left = middle;
            break;
        }        
    }

    temp = changeCoordsPlacingRHS(rec, loadingContainer[left]);
    if (!collisionInsideContainer(temp, left)) {
        for (int i = prev; i <= left; i++) {
            temp = changeCoordsPlacingRHS(rec, loadingContainer[i]);
            if (!collisionInsideContainer(temp, prev) && containerCollision(temp)) {
                flag = true;
                return temp;
            }
        }
    }
    return rec;
}

Rectangle Container::binarySearchTop(Rectangle& rec, bool & flag) {
    Rectangle temp = rec;
    if (loadingContainer.size() == 1) {
        temp = changeCoordsPlacingTop(rec, loadingContainer[0]);
        if (!collisionInsideContainer(temp, 0)) {
            flag = true;
            return temp;
        }            
        else
            return rec;
    }
    int left = 0, right = (int)loadingContainer.size() - 1, middle = 0, prev = 0;

    while (left < right)
    {
        middle = (right + left) / 2;
        temp = changeCoordsPlacingTop(rec, loadingContainer[middle]);
        if (collisionInsideContainer(temp, middle))
        {
            left = middle + 1;
            prev = middle;
        }
        else {
            left = middle;
            break;
        }

    }

    temp = changeCoordsPlacingTop(rec, loadingContainer[left]);
    if(!collisionInsideContainer(temp, left)) {
        for (int i = prev; i <= left; i++) {
            temp = changeCoordsPlacingTop(rec, loadingContainer[i]);
            if (!collisionInsideContainer(temp, prev) && containerCollision(temp)) {
                flag = true;
                return temp;
            }
        }
    }

  return rec;
}

Rectangle Container::binarySearchFront(Rectangle& rec, bool & flag) {
    Rectangle temp = rec;
    if (loadingContainer.size() == 1) {
        temp = changeCoordsPlacingFront(rec, loadingContainer[0]);
        if (!collisionInsideContainer(temp, 0)) {
            flag = true;
            return temp;
        }
        else
            return rec;
    }

    int left = 0, right = (int)loadingContainer.size()-1, middle = 0, prev = 0;

    while (left < right)
    {
        middle = (left + right) / 2;
        temp = changeCoordsPlacingFront(rec, loadingContainer[middle]);
        if (collisionInsideContainer(temp, middle))
        {
            left = middle + 1;
            prev = middle;
        }
        else {
            left = middle;
            break;
        }           
    }

    temp = changeCoordsPlacingFront(rec, loadingContainer[left]);
    if(!collisionInsideContainer(temp, left)) {
        for (int i = prev; i <= left; i++) {
            temp = changeCoordsPlacingFront(rec, loadingContainer[i]);
            if (!collisionInsideContainer(temp, prev) && containerCollision(temp)) {
                flag = true;
                return temp;
            }
        }
    }

   return rec;
}

void Container::placeInside(std::vector<Rectangle>& boxes) {
    if (loadingContainer.size() == 0 && boxes.size() > 0){
        loadingContainer.push_back(boxes[0]);
        boxes.erase(boxes.begin());
    }

        for (int i = 0; i < (int)boxes.size(); i++)
        {
            bool flag = false;
            bool placeFront = false;
            bool placeRHS = false;
            bool canBeLoaded = false;

            Rectangle temp = binarySearchTop(boxes[i], canBeLoaded);
            if (canBeLoaded) {
                loadingContainer.push_back(temp);
                i = 0;
                boxes.erase(boxes.begin());
                placeRHS = true; placeFront = true;
                flag = true;
            }

            if (!placeRHS) {
                Rectangle temp = binarySearchRHS(boxes[i], canBeLoaded);
                if (canBeLoaded) {
                    loadingContainer.push_back(temp);
                    i = 0;
                    boxes.erase(boxes.begin());
                    placeFront = true;
                    flag = true;
                }
            }

            if (!placeFront) {
                Rectangle temp = binarySearchFront(boxes[i], canBeLoaded);
                if (canBeLoaded) {
                    loadingContainer.push_back(temp);
                    i = 0;
                    boxes.erase(boxes.begin());
                    flag = true;
                }
            }
        }
}

bool Container::collisionInsideContainer(Rectangle & rec, int pos) {
   if (!containerCollision(rec))
        return true;
    int n = (int)loadingContainer.size() - 1;

    for (int i = 0; i <= n; i++) {
        if(!noCollision(rec, loadingContainer[i]))
          return true;
    }
    return false;
}

void Container::printCoords() {
    using std::cout;
    for (int i = 0; i < (int)loadingContainer.size(); i++)
    {
        cout << "Box number " << i+1 << '\n';
        cout << "TopLeftLHS(" << loadingContainer[i].topLeftLHS.getX() << "," << loadingContainer[i].topLeftLHS.getY() << "," << loadingContainer[i].topLeftLHS.getZ() << ")" << " "
            << "TopLeftRHS(" << loadingContainer[i].topLeftRHS.getX() << "," << loadingContainer[i].topLeftRHS.getY() << "," << loadingContainer[i].topLeftRHS.getZ() << ")" << "\n";

        cout << "TopRightLHS(" << loadingContainer[i].topRightLHS.getX() << "," << loadingContainer[i].topRightLHS.getY() << "," << loadingContainer[i].topRightLHS.getZ() << ")" << " "
            << "TopRightRHS(" << loadingContainer[i].topRightRHS.getX() << "," << loadingContainer[i].topRightRHS.getY() << "," << loadingContainer[i].topRightRHS.getZ() << ")" << "\n";

        cout << "BottomLeftLHS(" << loadingContainer[i].bottomLeftLHS.getX() << "," << loadingContainer[i].bottomLeftLHS.getY() <<  "," << loadingContainer[i].bottomLeftLHS.getZ() << ")" << " "
            << "BotomLeftRHS(" << loadingContainer[i].bottomLeftRHS.getX() << "," << loadingContainer[i].bottomLeftRHS.getY() << "," << loadingContainer[i].bottomLeftRHS.getZ() << ")" << "\n";

        cout << "BottomRightLHS(" << loadingContainer[i].bottomRightLHS.getX() << "," << loadingContainer[i].bottomRightLHS.getY() << "," << loadingContainer[i].bottomRightLHS.getZ() << ")" << " "
            << "BotomRightRHS(" << loadingContainer[i].bottomRightRHS.getX() << "," << loadingContainer[i].bottomRightRHS.getY() << "," << loadingContainer[i].bottomRightRHS.getZ() << ")" << "\n";
        cout << "________________________________________________________________________\n";
    }
}


int Container::getQuanAlongSide(int side1, int side2){
    return (container.getLength() / side1) * (container.getWidth() / side2);
}

//leave this function for pallet distrubtion loading
void Container::setOptimalLoadingMap(int length, int width, int height) {
    struct boxHoarding {
        int height;
        int qty;
    };

    std::vector<boxHoarding> boxes;
    std::vector<int> dp(container.getHeight()+1, INT_MIN);
    dp[0] = 0;

    boxes.push_back(boxHoarding{ height, getQuanAlongSide(length, width) });
    boxes.push_back(boxHoarding{ height, getQuanAlongSide(width, length)});
    boxes.push_back(boxHoarding{ length, getQuanAlongSide(height, width) });
    boxes.push_back(boxHoarding{ length, getQuanAlongSide(width, height) });
    boxes.push_back(boxHoarding{ width, getQuanAlongSide(height, length) });
    boxes.push_back(boxHoarding{ width, getQuanAlongSide(length, height) });

    int totalLoadingHeight = 0;
    for (int i = 0; i <= container.getHeight(); i++) {
        for (auto box : boxes) {
            if (i - box.height >= 0 && dp[i- box.height] != INT_MIN) {
                dp[i] < dp[i - box.height] + box.qty ? totalLoadingHeight = i : totalLoadingHeight = totalLoadingHeight;
                dp[i] = std::max(dp[i], box.qty + dp[i - box.height]);
            }
        }
        
    }
    int totalQuantity = 0;

    //Restoring best loading option for placing inside loading container via coordinates
    for (int i = totalLoadingHeight; i > 0;) {
        for(auto box : boxes)
        if (i - box.height >= 0 && dp[i - box.height] != INT_MIN && dp[i] - box.qty == dp[i-box.height]) {
           std::cout << "At length " << i << " " << box.qty << " boxes were loaded" << " height of box hoarding is " << box.height<<'\n';
           totalQuantity += box.qty;
           i -= box.height;
        }
    }
    std::cout << totalQuantity << " boxes were loaded!\n";
}

bool Container::isLoadingCorrect() {
    for (int i = 0; i < (int)loadingContainer.size(); i++) {
        for (int j = i+1; j < (int)loadingContainer.size(); j++) {
           if (i == j)
                continue;
            if (!noCollision(loadingContainer[i], loadingContainer[j])) {
                std::cout << loadingContainer[i] << "collides with\n";
                std::cout << loadingContainer[j] << "\n";
                return false;
            }
        }
    }
    return true;
}

void Container::Insert(Rectangle & rec) {
    if (loadingContainer.size() == 0) {
        loadingContainer.push_back(rec);
        return;
    }

        bool canBeLoaded = false;
        Rectangle temp = binarySearchTop(rec, canBeLoaded);
        if (canBeLoaded)
        {
                loadingContainer.push_back(temp);
                return;
        }

        if (!canBeLoaded) {
            Rectangle temp = binarySearchFront(rec, canBeLoaded);
            if (canBeLoaded) {
                loadingContainer.push_back(temp); 
            }
        }
      
        if (!canBeLoaded) {
            Rectangle temp = binarySearchRHS(rec, canBeLoaded);
            if(canBeLoaded)
            loadingContainer.push_back(temp);
        }
}

bool Container::isFull(Rectangle & rec) {
       
 if (loadingContainer.size() == 0) {
        return false;
 }

    bool canBeLoaded = false;
    Rectangle temp = binarySearchRHS(rec, canBeLoaded);
    if (canBeLoaded) {

        return false;
    }

    temp = binarySearchTop(rec, canBeLoaded);
    if (canBeLoaded) {
      
        return false;
     }

    temp = binarySearchFront(rec, canBeLoaded);
    if (canBeLoaded) {
        return false;
    }
    
    return true;
}


void Container::bruteForce_Loading(Rectangle& rec, bool & flag) {

    if (loadingContainer.size() == 0) {
        loadingContainer.push_back(rec);
    }
    int right = (int)loadingContainer.size()-1;
    Rectangle temp;
    
        for (int i = 0; i <= right; i++) {
            temp = changeCoordsPlacingRHS(rec, loadingContainer[i]);
            if (!collisionInsideContainer(temp, i)) {
                loadingContainer.push_back(temp);
                flag = true;
                return;
            }
        }
  
    for (int i = 0; i <= right; i++) {
        temp = changeCoordsPlacingFront(rec, loadingContainer[i]);
        if (!collisionInsideContainer(temp, i)) {
            loadingContainer.push_back(temp);
            flag = true;
            return;
        }
    }
   
    for (int i = 0; i <= right; i++) {
        temp = changeCoordsPlacingTop(rec, loadingContainer[i]);
        if (!collisionInsideContainer(temp, i)) {
            loadingContainer.push_back(temp);
            flag = true;
            return;
        }
    }
   
}

std::vector<std::pair<Rectangle, int>> Container::merge_boxes(std::vector<std::pair<Rectangle, int>>& boxes) {
    std::vector<std::pair<Rectangle, int>> ans;

    for (auto r : boxes) {
        Rectangle temp(r.first.getLength()*4, r.first.getHeight(), r.first.getWidth()*2);
        
        int qty = r.second / 8;
        int left_qty = r.second % 8;

        if (qty > 0 )ans.push_back({ temp, qty });
        if (left_qty > 0) ans.push_back({ r.first, left_qty });
    }
    return ans;
}

void Container::loadBoxes(std::vector<Rectangle>& boxes) {
   struct CMP_SORT {
       bool operator() (const std::tuple<int, int, int> t1, const std::tuple<int, int, int> t2) const {
           return t1 > t2;
       }
   };
   std::map<std::tuple<int, int, int>, int, CMP_SORT> loadMap;

   for (auto& b : boxes) {
       loadMap[std::make_tuple(b.getLength(), b.getHeight(), b.getWidth())]++;
   }

   std::vector<std::pair<Rectangle, int>> boxesForLoading;

   for (auto& load : loadMap) {
       std::tuple<int, int, int> temp = load.first;
       int l = std::get<0>(temp), h = std::get<1>(temp), w = std::get<2>(temp);
       Rectangle box(l, h, w);
       int q = load.second;
       boxesForLoading.push_back(std::make_pair(box, q));
   }

    int maxBoxes = 0;

    std::vector<Container> containers(1);
        for (int i = 0; i < 1; i++) {
            int l = container.getLength(), h = container.getHeight(), w = container.getWidth();
            Container temp(l, h, w);
            containers[i] = temp;
        }
  

    boxesForLoading = merge_boxes(boxesForLoading);
    std::vector<std::vector<Rectangle>> unusedBoxes(1);
    double cubes = 0;

    /*sort(boxesForLoading.begin(), boxesForLoading.end(), [](std::pair<Rectangle, int>& rec1, std::pair<Rectangle, int>& rec2) {
        return rec1.second > rec2.second;
     });*/

    int contIndex = 0;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 5);

    std::random_shuffle(boxesForLoading.begin(), boxesForLoading.end());
    for (auto& cont : containers) {
       
        for (auto& box : boxesForLoading) {
            int rotate_box = dist6(rng), place_style = dist6(rng);
            int q = box.second;
            (box.first.*rotate[rotate_box])();
            while (q--) {
                if (!(cont.*check[place_style])(box.first)) {
                    (cont.*place[place_style])(box.first);
                    //cubes += ((double)containers[0].loadingContainer.back().getCube() / 1000000.0);
                }
                /*if (cont.isFull(box.first)) {
                    cont.Insert(box.first);
                    cubes += ((double)containers[0].loadingContainer.back().getCube() / 1000000.0);
                }*/
                else {
                    for(int i = 0; i < q; i++)
                      unusedBoxes[contIndex].push_back(box.first);
                    break;
                }
            }
        }
        contIndex++;
    }


    int i = 0;

        if(unusedBoxes[i].size() > 0)
        sort(unusedBoxes[i].begin(), unusedBoxes[i].end(), [](Rectangle& rec1, Rectangle& rec2) {
            return rec1.getCube() < rec2.getCube();
        });

        for (int z = 0; z < unusedBoxes[i].size(); z++) {
            
           bool flag = false;
           containers[i].bruteForce_Loading(unusedBoxes[i][z], flag);
           if (flag) {
              // cubes += (double)unusedBoxes[i][z].getCube() / 1000000.0; 
           }
           else {
               boxes_left++;
           }
        }

        loadingContainer = containers[0].loadingContainer;
        for (int k = 0; k < (int)containers[i].loadingContainer.size(); k++) {
            cubes += ((double)containers[i].loadingContainer[k].getCube() / 1000000.0);
        }
        loadedVolume = cubes;    
}


bool Container::isFull_RF(Rectangle& rec) {
    if (loadingContainer.size() == 0) {
        return false;
    }

    bool canBeLoaded = false;
    Rectangle temp = binarySearchRHS(rec, canBeLoaded);
    if (canBeLoaded) {
        return false;
    }

  temp = binarySearchFront(rec, canBeLoaded);
        if (canBeLoaded) {
            return false;
        }
    return true;
}

bool Container::isFull_RU(Rectangle& rec) {
    if (loadingContainer.size() == 0) {
        return false;
    }

    bool canBeLoaded = false;
    Rectangle temp = binarySearchRHS(rec, canBeLoaded);
    if (canBeLoaded) {
        return false;
    }
  
    temp = binarySearchTop(rec, canBeLoaded);
     if (canBeLoaded) {
         return false;
     }
  
    return true;
}

bool Container::isFull_UF(Rectangle& rec) {
    if (loadingContainer.size() == 0) {
        return false;
    }

    bool canBeLoaded = false;

    Rectangle temp = binarySearchTop(rec, canBeLoaded);
    if (canBeLoaded) {
        return false;
    }

         temp = binarySearchFront(rec, canBeLoaded);
        if (canBeLoaded) {
            return false;
        }

    return true;
}

bool Container::isFull_UR(Rectangle& rec) {
    if (loadingContainer.size() == 0) {
        return false;
    }

    bool canBeLoaded = false;
    Rectangle temp = binarySearchTop(rec, canBeLoaded);
    if (canBeLoaded) {
        return false;
    }
         temp = binarySearchRHS(rec, canBeLoaded);
        if (canBeLoaded) {
            return false;
        }

    return true;
}

bool Container::isFull_FR(Rectangle& rec) {
    if (loadingContainer.size() == 0) {
        return false;
    }

    bool canBeLoaded = false;


    Rectangle temp = binarySearchFront(rec, canBeLoaded);
    if (canBeLoaded) {
        return false;
    }

         temp = binarySearchRHS(rec, canBeLoaded);
        if (canBeLoaded) {
            return false;
        }
 
    return true;
}

bool Container::isFull_FU(Rectangle& rec) {
    if (loadingContainer.size() == 0) {
        return false;
    }

    bool canBeLoaded = false;
    Rectangle temp = binarySearchFront(rec, canBeLoaded);
    if (canBeLoaded) {
        return false;
    }
        temp = binarySearchTop(rec, canBeLoaded);
        if (canBeLoaded) {
            return false;
        }
  
    return true;
}

void Container::bs_RF(Rectangle& rec) {
    if (loadingContainer.size() == 0) {
        loadingContainer.push_back(rec);
        return;
    }

    bool canBeLoaded = false;
    Rectangle temp = binarySearchRHS(rec, canBeLoaded);
    if (canBeLoaded) {
        loadingContainer.push_back(temp);
        return;
    }

    if (!canBeLoaded) {
        Rectangle temp = binarySearchFront(rec, canBeLoaded);
        if (canBeLoaded) {
            loadingContainer.push_back(temp);
            return;
        }
    }
}

void Container::bs_RU(Rectangle& rec) {
    if (loadingContainer.size() == 0) {
        loadingContainer.push_back(rec);
        return;
    }

    bool canBeLoaded = false;
    Rectangle temp = binarySearchRHS(rec, canBeLoaded);
    if (canBeLoaded) {
        loadingContainer.push_back(temp);
        return;
    }

    if (!canBeLoaded)
    {
        Rectangle temp = binarySearchTop(rec, canBeLoaded);
        if (canBeLoaded) {
            loadingContainer.push_back(temp);
            return;
        }
    }
}

void Container::bs_UF(Rectangle& rec) {
    if (loadingContainer.size() == 0) {
        loadingContainer.push_back(rec);
        return;
    }

    bool canBeLoaded = false;

        Rectangle temp = binarySearchTop(rec, canBeLoaded);
        if (canBeLoaded) {
            loadingContainer.push_back(temp);
            return;
        }

        if (!canBeLoaded) {
            Rectangle temp = binarySearchFront(rec, canBeLoaded);
            if (canBeLoaded) {
                loadingContainer.push_back(temp);
                return;
            }
        }
}

void Container::bs_UR(Rectangle& rec) {
    if (loadingContainer.size() == 0) {
        loadingContainer.push_back(rec);
        return;
    }

    bool canBeLoaded = false;

    Rectangle temp = binarySearchTop(rec, canBeLoaded);
    if (canBeLoaded) {
        loadingContainer.push_back(temp);
        return;
    }

    if (!canBeLoaded)
    {
        Rectangle temp = binarySearchRHS(rec, canBeLoaded);
        if (canBeLoaded) {
            loadingContainer.push_back(temp);
            return;
        }
    }
}

void Container::bs_FR(Rectangle& rec) {
    if (loadingContainer.size() == 0) {
        loadingContainer.push_back(rec);
        return;
    }

    bool canBeLoaded = false;
        Rectangle temp = binarySearchFront(rec, canBeLoaded);
        if (canBeLoaded) {
            loadingContainer.push_back(temp);
            return;
        }

        if (!canBeLoaded)
        {
            Rectangle temp = binarySearchRHS(rec, canBeLoaded);
            if (canBeLoaded) {
                loadingContainer.push_back(temp);
                return;
            }
        }
}

void Container::bs_FU(Rectangle& rec) {
    if (loadingContainer.size() == 0) {
        loadingContainer.push_back(rec);
        return;
    }

    bool canBeLoaded = false;
    Rectangle temp = binarySearchFront(rec, canBeLoaded);
    if (canBeLoaded) {
        loadingContainer.push_back(temp);
        return;
    }

    if (!canBeLoaded) {
        Rectangle temp = binarySearchTop(rec, canBeLoaded);
        if (canBeLoaded) {
            loadingContainer.push_back(temp);
            return;
        }
    }
}