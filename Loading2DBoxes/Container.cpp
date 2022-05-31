#include "Container.h"
#include <algorithm>

Container::Container(int length, int height, int width)
{
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

bool Container::containerCollision(Rectangle & rec)
{
    return (container.getX() >= rec.getX() && container.getY() >= rec.getY() && container.getZ() >= rec.getZ());
}

bool Container::noCollision(Rectangle& a, Rectangle& b)
{
    if (a.getMinX() >= b.getMaxX()) return true;
    if(b.getMinX() >= a.getMaxX()) return true;
    if (a.getMinY() >= b.getMaxY()) return true;
    if (b.getMinY() >= a.getMaxY()) return true;
    if (a.getMinZ() >= b.getMaxZ()) return true;
    if (b.getMinZ() >= a.getMaxZ()) return true;

    return false;
/* return (a.getMinX() >= b.getMaxX() || b.getMinX() >= a.getMaxX() ||
            a.getMinY() >= b.getMaxY() || b.getMinY() >= a.getMaxY() ||
            a.getMinZ() >= b.getMaxZ() || b.getMinZ() >= a.getMaxZ());
   /* return (abs((a.getX() + a.getLength() / 2) - (b.getX() + b.getLength() / 2)) * 2 < (a.getLength() + b.getLength()) &&
        (abs((a.getY() + a.getHeight() / 2) - (b.getY() + b.getHeight() / 2)) * 2 < (a.getHeight() + b.getHeight()) &&
            abs((a.getZ() + a.getWidth() / 2) - (b.getZ() + b.getWidth() / 2)) * 2 < (a.getWidth() + b.getWidth())));*/


}

Rectangle Container::changeCoordsPlacingTop(Rectangle & rec, Rectangle & boxInContainer)
{
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

Rectangle Container::changeCoordsPlacingRHS(Rectangle& rec, Rectangle& boxInContainer)
{
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

Rectangle Container::changeCoordsPlacingFront(Rectangle& rec, Rectangle& boxInContainer)
{
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
            if (!collisionInsideContainer(temp, i) && containerCollision(temp)) {
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
            if (!collisionInsideContainer(temp, i) && containerCollision(temp)) {
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
            if (!collisionInsideContainer(temp, i) && containerCollision(temp)) {
                flag = true;
                return temp;
            }
        }
    }

   return rec;
}


void Container::placeInside(std::vector<Rectangle>& boxes)
{
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

bool Container::collisionInsideContainer(Rectangle & rec, int pos)
{
   if (!containerCollision(rec))
        return true;
    int n = (int)loadingContainer.size() - 1;
    int i = 0;

    for (; i <= n; i++) {
        if(!noCollision(rec, loadingContainer[i]))
          return true;
    }

    return false;
}


void Container::printCoords()
{
    using std::cout;
    /*for (int i = 0; i < (int)loadingContainer.size(); i++)
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
    }*/
    double cube = 0;
    for (int i = 0; i < (int)loadingContainer.size(); i++) {
        Rectangle rec = loadingContainer[i];
        cube += ((double)rec.getHeight() / 100.0) * ((double)rec.getLength() / 100.0) * ((double)rec.getWidth() / 100.0);
    }
    cout << "Total amount of loaded cube is " << cube << '\n';
    cout << loadingContainer.size() << " boxes were loaded!\n";
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

bool Container::isLoadingCorrect()
{
    for (int i = 0; i < (int)loadingContainer.size(); i++) {
        for (int j = 0; j < (int)loadingContainer.size(); j++) {
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

        if (!canBeLoaded) {
            Rectangle temp = binarySearchFront(rec, canBeLoaded);
            if (canBeLoaded) {
                loadingContainer.push_back(temp); 
            }
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


void Container::sortBoxes(std::vector<Rectangle>& boxes) {
    struct CMP_SORT {
        bool operator() (const std::tuple<int, int, int> t1, const std::tuple<int, int, int> t2) const {
            return t1 > t2;
        }
    };
    std::map<std::tuple<int, int, int>, int, CMP_SORT> load;

    for (auto& b : boxes) {
        load[std::make_tuple(b.getLength(), b.getHeight(), b.getWidth())]++;
    }

    int contArea = container.getArea();

    std::vector<std::vector<Rectangle>> lairs;

    while (load.size() > 0) {
        std::vector<std::pair<int, Rectangle>> dp(contArea + 1);
        std::vector<Rectangle> vec;
        dp[0].first = 1;

        for (int i = 1; i <= contArea; i++) {
            for (auto& b : load) {
                std::tuple<int, int, int> temp = b.first;
                int l = std::get<0>(temp), h = std::get<1>(temp), w = std::get<2>(temp);
                int area = l * w;
                if (i - area >= 0 && b.second > 0 && dp[i - area].first > 0) {
                    Rectangle rec(l, h, w);
                    dp[i].first = dp[i - area].first;
                    dp[i].second = rec;
                }
            }
        }

        int n = contArea;
        while (dp[n].first != 1) {
            n--;
        }

        for (int i = n; i >= 0; ) {
            std::tuple<int, int, int> temp = std::make_tuple(dp[i].second.getLength(), dp[i].second.getHeight(), dp[i].second.getWidth());
            if (load[temp] > 0) {
                vec.push_back(dp[i].second);
                i -= dp[i].second.getArea();
                load[temp]--;
            }
            else {
                break;
            }
        }

        for (auto it = load.begin(); it != load.end();) {
            if (it->second <= 0) {
                auto temp = it->first;
                load.erase(temp);
                it = load.begin();
            }
            if (it != load.end())
                it++;
        }
        lairs.push_back(vec);
    }

    std::vector<Rectangle> vec;
    std::vector<std::pair<double, int>> index;
    for (int i = 0; i < (int)lairs.size(); i++) {
        double cube = 0;
        for (int j = 0; j < (int)lairs[i].size(); j++) {
            cube += ((double)lairs[i][j].getCube() / 1000000.0);
        }
        index.push_back(std::make_pair(cube, i));
    }

    sort(index.rbegin(), index.rend());
    for (int i = 0; i < (int)index.size(); i++) {
        for (int j = 0; j < (int)lairs[index[i].second].size(); j++) {
            vec.push_back(lairs[index[i].second][j]);
        }
    }

    boxes = vec;
}


void Container::generateBottomBox(std::vector<Rectangle>& temp) {

    std::map<std::tuple<int, int, int>, int> load;

    for(auto & b : temp) {
        load[std::make_tuple(b.getLength(), b.getHeight(), b.getWidth())]++;
    }

    //Generate simple box bottom
    std::vector<Rectangle> simpleBoxes;
    for (auto& t : load) {
        if (t.second % 4 == 0) {
            std::tuple<int, int, int> temp = t.first;
            int l = std::get<0>(temp), w = std::get<2>(temp), h = std::get<1>(temp);
            Rectangle rec(l,h*2,w*2);
            for (int i = 0; i < t.second / 4; i++) {
                simpleBoxes.push_back(rec);
            }
        }
        else if (t.second % 2 == 0) {
            std::tuple<int, int, int> temp = t.first;
            int l = std::get<0>(temp), w = std::get<2>(temp), h = std::get<1>(temp);
            Rectangle rec(l, h, w*2);
            for (int i = 0; i < t.second / 2; i++) {
                simpleBoxes.push_back(rec);
            }
        }
    }
    temp = simpleBoxes;
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
        Rectangle temp(r.first.getLength(), r.first.getHeight(), r.first.getWidth() * 2);
        
        int qty = r.second / 2;
        int left_qty = r.second % 2;

        if (qty > 0) ans.push_back({ temp, qty });
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


    sort(boxesForLoading.begin(), boxesForLoading.end(), [](std::pair<Rectangle, int>& rec1, std::pair<Rectangle, int>& rec2) {
        return rec1.second > rec2.second;
     });

    int contIndex = 0;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 5);

    for (auto& cont : containers) {
       
        for (auto& box : boxesForLoading) {
            int rotate_box = dist6(rng), place_style = dist6(rng);
            int q = box.second;
            (box.first.*rotate[rotate_box])();
            while (q--) {
                if (!(cont.*check[place_style])(box.first)) {
                    (cont.*place[place_style])(box.first);
                }
                else {
                    for(int i = 0; i < q; i++)
                      unusedBoxes[contIndex].push_back(box.first);
                    break;
                }
            }
        }
        //std::random_shuffle(boxesForLoading.begin(), boxesForLoading.end());
        contIndex++;
    }


    int i = 0; int j = 0; double cubes = 0, ans = 0; int row = 0;

        /*for (auto& cont : containers) {
            //cubes = 0;
            for (int k = 0; k < (int)cont.loadingContainer.size(); k++) {
                cubes += ((double)cont.loadingContainer[k].getCube() / 1000000.0);
            }
            if (ans < cubes) {
                ans = cubes;
                maxBoxes = cont.getLoadedQuan();
                i = j;
            }
            j++;
        }*/
        //cubes = 0;

        if(unusedBoxes[i].size() > 0)
        sort(unusedBoxes[i].begin(), unusedBoxes[i].end(), [](Rectangle& rec1, Rectangle& rec2) {
            return rec1.getCube() < rec2.getCube();
        });

        for (int z = 0; z < unusedBoxes[i].size(); z++) {
            
            bool flag = false;
           containers[i].bruteForce_Loading(unusedBoxes[i][z], flag);
           if (flag) { cubes += unusedBoxes[i][z].getCube() / 1000000.0; }
        }

        for (int k = 0; k < (int)containers[i].loadingContainer.size(); k++) {
            cubes += ((double)containers[i].loadingContainer[k].getCube() / 1000000.0);
        }

        std::cout << '\n';
        std::cout << containers[i].getLoadedQuan() << " cubes " << cubes << '\n';    
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
  

  /*temp = binarySearchTop(rec, canBeLoaded);
        if (canBeLoaded) {
            return false;
        }*/
 

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
   
        /* temp = binarySearchFront(rec, canBeLoaded);
        if (canBeLoaded) {
            return false;
        }*/

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

        /* temp = binarySearchRHS(rec, canBeLoaded);
        if (canBeLoaded) {
           return false;
        }*/
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
  
    
        /* temp = binarySearchFront(rec, canBeLoaded);
        if (canBeLoaded) {
            return false;
        }*/

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


        /* temp = binarySearchTop(rec, canBeLoaded);
        if (canBeLoaded) {
            return false;
        }*/
 
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
   

   
        /*temp = binarySearchRHS(rec, canBeLoaded);
        if (canBeLoaded) {
            return false;
        }*/
   

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

    /* if (!canBeLoaded)
    {
        Rectangle temp = binarySearchTop(rec, canBeLoaded);
        if (canBeLoaded) {
            loadingContainer.push_back(temp);
            return;
        }
    }*/
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

    /*if (!canBeLoaded) {
        Rectangle temp = binarySearchFront(rec, canBeLoaded);
        if (canBeLoaded) {
            loadingContainer.push_back(temp);
            return;
        }
    }*/
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

        /*if (!canBeLoaded)
        {
            Rectangle temp = binarySearchRHS(rec, canBeLoaded);
            if (canBeLoaded) {
                loadingContainer.push_back(temp);
                return;
            }
        }*/
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
    /*if (!canBeLoaded) {
        Rectangle temp = binarySearchFront(rec, canBeLoaded);
        if (canBeLoaded) {
            loadingContainer.push_back(temp);
            return;
        }
    }*/
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

        /*if (!canBeLoaded) {
            Rectangle temp = binarySearchTop(rec, canBeLoaded);
            if (canBeLoaded) {
                loadingContainer.push_back(temp);
                return;
            }
        }*/

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

    /*if (!canBeLoaded)
    {
        Rectangle temp = binarySearchRHS(rec, canBeLoaded);
        if (canBeLoaded) {
            loadingContainer.push_back(temp);
            return;
        }
    }*/
}


   // sortBoxes(boxes);
    //generateBottomBox(boxes);

    //Container root(container.getLength(), container.getHeight(), container.getWidth());
    /*Node<Container> treeXYZ(root);  treeXYZ.insertNode(root);
    Node<Container> treeXZY(root);  treeXZY.insertNode(root);
    Node<Container> treeYXZ(root);  treeYXZ.insertNode(root);
    Node<Container> treeYZX(root);  treeYZX.insertNode(root);
    Node<Container> treeZYX(root);  treeZYX.insertNode(root);
    Node<Container> treeZXY(root);  treeZXY.insertNode(root);*/
    //std::vector<std::vector<Node<Container>>> nodesXYZ;
   /* std::vector<Node<Container>> roots;

    for (int i = 0; i < 6; i++) {
       Container root(container.getLength(), container.getHeight(), container.getWidth());
       Node<Container> tree(root);  tree.insertNode(root);
       roots.push_back(tree);
    }

    int maxLoad = 0;

    for (int i = 0; i < (int)boxes.size(); i++) {
        int l = boxes[i].getLength(), w = boxes[i].getWidth(), h = boxes[i].getHeight();
        Rectangle rec = boxes[i];
        
        if (!roots[0].val.isFull(rec)) {
            Container temp = roots[0].val;
            temp.Insert(rec);
            maxLoad = (maxLoad, temp.getLoadedQuan());
            roots[0].insertNode(temp);
            roots[0] = roots[0].children[0]->val;
        }
        rec = boxes[i].turnBottomFront(l, h, w);
        if (!roots[1].val.isFull(rec)) {
            Container temp = roots[1].val;
            temp.Insert(rec);
            maxLoad = (maxLoad, temp.getLoadedQuan());
            roots[1].insertNode(temp);
            roots[1] = roots[1].children[0]->val;
        }
        rec = boxes[i].turnBottomUpFront(l, h, w);
        if (!roots[2].val.isFull(rec)) {
            Container temp = roots[2].val;
            temp.Insert(rec);
            maxLoad = (maxLoad, temp.getLoadedQuan());
            roots[2].insertNode(temp);
            roots[2] = roots[2].children[0]->val;
        }
        rec = boxes[i].turnSideDown(l, h, w);
        if (!roots[3].val.isFull(rec)) {
            Container temp = roots[3].val;
            temp.Insert(rec);
            maxLoad = (maxLoad, temp.getLoadedQuan());
            roots[3].insertNode(temp);
            roots[3] = roots[3].children[0]->val;
        }
        rec = boxes[i].turnSideFront(l, h, w);
        if (!roots[4].val.isFull(rec)) {
            Container temp = roots[4].val;
            temp.Insert(rec);
            maxLoad = (maxLoad, temp.getLoadedQuan());
            roots[4].insertNode(temp);
            roots[4] = roots[4].children[0]->val;
        }
        rec = boxes[i].turnSideUpFront(l, h, w);
        if (!roots[5].val.isFull(rec)) {
            Container temp = roots[5].val;
            temp.Insert(rec);
            maxLoad = (maxLoad, temp.getLoadedQuan());
            roots[5].insertNode(temp);
            roots[5] = roots[5].children[0]->val;
        }
      
    }
    std::cout << "Max load is " << maxLoad << '\n';*/

   /* tree.insertNode(root);
    std::queue<Node<Container>> q1, q2;
    q1.push(root);

    for (auto & b : boxes) {              

        while (!q1.empty()) {
            auto cur = q1.front();
            q1.pop();
            std::vector<Rectangle> rotations;
            rotations.push_back(b);
            rotations.push_back(b.turnBottomFront(b.getLength(), b.getHeight(), b.getWidth()));
            rotations.push_back(b.turnBottomUpFront(b.getLength(), b.getHeight(), b.getWidth()));
            rotations.push_back(b.turnSideDown(b.getLength(), b.getHeight(), b.getWidth()));
            rotations.push_back(b.turnSideFront(b.getLength(), b.getHeight(), b.getWidth()));
            rotations.push_back(b.turnSideUpFront(b.getLength(), b.getHeight(), b.getWidth()));

            for (int i = 0; i < (int)rotations.size(); i++) {
                if (!cur.val.isFull(rotations[i])) {
                    cur.insertNode(cur.val);
                    cur.children.back()->val.Insert(rotations[i]);
                    q2.push(*cur.children.back());
                }
            }
            
        }
        q1 = std::move(q2);
        q2 = std::queue<Node<Container>>();
    }

    std::vector<Rectangle> ans;
    while (!q1.empty()) {
        if ((int)ans.size() < q1.front().val.getLoadedQuan()) {
            ans = q1.front().val.getConainer();
        }
        q1.pop();
    }*/

/* for (auto& b : boxes) {
     b.rotateBox(b, container.getLength());
 }

 sort(boxes.begin(), boxes.end(), [](Rectangle& rec1, Rectangle& rec2) {
     return rec1.getLength() > rec2.getLength();
     });*/

/*void Container::generateLoadingMap(std::vector<Rectangle>& boxes) {
    struct RectCMP_SORT {
        bool operator() (const Rectangle& rec1, const Rectangle& rec2) const {
            return (rec1.topLeftLHS > rec2.topLeftLHS && rec1.topLeftRHS > rec2.topLeftRHS && rec1.topRightLHS > rec2.topRightLHS && rec1.topRightRHS > rec2.topRightRHS &&
                rec1.bottomLeftLHS > rec2.bottomLeftLHS && rec1.bottomLeftRHS > rec2.bottomLeftRHS && rec1.bottomRightLHS > rec2.bottomRightLHS && rec1.bottomRightRHS > rec2.bottomRightRHS);
        }
    };

    std::vector<Rectangle> ans;
    std::map<Rectangle, int, RectCMP_SORT> boxMap;
    for (int i = 0; i < (int)boxes.size(); i++) {
        boxMap[boxes[i]]++;
    }

    struct lbx {
        Rectangle box;
        int quantity;
    };
    std::vector<lbx> temp;

    for (auto& b : boxMap) {
        temp.push_back({ b.first, b.second });
    }

    int n = container.getLength();
    int m = container.getWidth();
    const int contHeight = container.getHeight();
    loadingMap.resize(n + 1, std::vector<std::pair<int, int>>(m + 1));
    
    loadingMap[0][0].first = 1;

    int totalBoxes = 0;
    int I, J;
  

        for (int j = 0; j <= m; j++) {
            for (int i = 0; i <= n; i++) {
            for (auto& b : temp) {
                int boxLen = b.box.getLength(), boxWidth = b.box.getWidth(), boxHeight = b.box.getHeight();
                if (b.quantity > 0) {
                    if (i - boxLen >= 0 && j - boxWidth >= 0 && loadingMap[i][j].second + boxHeight <= contHeight) {
                        loadingMap[i][j].first = loadingMap[i - boxLen][j - boxWidth].first + 1;
                        loadingMap[i][j].second += boxHeight;
                        loadingMap[j][i].second += boxHeight;
                    }
                    if (i - boxLen >= 0 && j - boxHeight >= 0 && loadingMap[i][j].second + boxWidth <= contHeight) {
                        loadingMap[i][j].first = loadingMap[i - boxLen][j - boxHeight].first + 1;
                        loadingMap[i][j].second += boxWidth;
                        loadingMap[j][i].second += boxWidth;
                    }
                    if (i - boxWidth >= 0 && j - boxLen >= 0 && loadingMap[i][j].second + boxHeight <= contHeight) {
                        loadingMap[i][j].first = loadingMap[i - boxWidth][j - boxLen].first + 1;
                        loadingMap[i][j].second += boxHeight;
                        loadingMap[j][i].second += boxHeight;
                    }
                    if (i - boxWidth >= 0 && j - boxHeight >= 0 && loadingMap[i][j].second + boxLen <= contHeight) {
                        loadingMap[i][j].first = loadingMap[i - boxWidth][j - boxHeight].first + 1;
                        loadingMap[i][j].second += boxLen;
                        loadingMap[j][i].second += boxLen;
                    }
                    if (i - boxHeight >= 0 && j - boxWidth >= 0 && loadingMap[i][j].second + boxLen <= contHeight) {
                        loadingMap[i][j].first = loadingMap[i - boxHeight][j - boxWidth].first + 1;
                        loadingMap[i][j].second += boxLen;
                        loadingMap[j][i].second += boxLen;
                    }
                    if (i - boxHeight >= 0 && j - boxLen >= 0 && loadingMap[i][j].second + boxWidth <= contHeight) {
                        loadingMap[i][j].first = loadingMap[i - boxHeight][j - boxLen].first + 1;
                        loadingMap[i][j].second += boxWidth;
                        loadingMap[j][i].second += boxWidth;
                    }
                    if (totalBoxes < loadingMap[i][j].first) {
                        I = i; J = j;
                        totalBoxes = loadingMap[i][j].first;
                    }
                }
            }
        }
    }

        std::cout << totalBoxes << '\n';
}*/


/*
*
* if (rec == b) {
        bxRt = 0, ldgApp = 0;
    }
    else {
        i++;
        bxRt = 4, ldgApp = 5;
    }
* if ((i & 1)) {
            if (ldgApp == 6) {
                if (bxRt == 4) {
                    bxRt = -1;
                }
                ldgApp = 0;
                bxRt++;
            }//(b.*rotate[j])();

            (b.*rotate[bxRt])();
            (cont.*place[ldgApp])(b);
            ldgApp++;
        }
        else {
            if (ldgApp == 0) {
                if (bxRt == 0) {
                    bxRt = 4;
                }
                ldgApp = 5;
                bxRt--;
            }//(b.*rotate[j])();

            (b.*rotate[bxRt])();
            (cont.*place[ldgApp])(b);
            ldgApp--;
        }
    }
*
*/

/*
            *       for (int i = 0; i < 6; i++) {
            if (!(containers[i].*check[i])(b)) {
                (containers[i].*place[i])(b);
            }
            else {
                bool flag = false;
                for (int j = 0; j < 5; j++) {
                    (b.*rotate[j])();
                    if (!(containers[i].*check[i])(b)) {
                        (containers[i].*place[i])(b);
                        flag = true;
                        break;
                    }
                }
            }
            }*/

            //std::vector<std::pair<double,int>> index;


          /* for (int i = 0; i < (int)lairs.size(); i++) {
                double cube = 0;
                for (int j = 0; j < (int)lairs[i].size(); j++) {
                    cube += ((double)lairs[i][j].getCube() / 1000000.0);
                }
                index.push_back(std::make_pair(cube, i));
            }*/

            //std::reverse(vec.begin(), vec.end());

            //std::vector<Rectangle> vec;


            /*bxTps = load.size();

            int xyWise, xzWise, zyWise;
            int len = container.getLength(), height = container.getHeight(), width = container.getWidth();
            for (auto& b : load) {
                std::tuple<int, int, int> temp = b.first;
                int l = std::get<0>(temp), h = std::get<1>(temp), w = std::get<2>(temp), quantity;
                xyWise = b.second - (b.second % (len / l + height / h));
                xzWise = b.second - (b.second % (len / l + width / w));
                zyWise = b.second - (b.second % (height / h + width / w));
                quantity = std::min(std::min(xyWise, xzWise), zyWise);
                b.second -= quantity;

                Rectangle rec(l, h, w);
                for (int j = 0; j < quantity; j++) {
                    vec.push_back(rec);
                }

            }
           // std::vector<Rectangle> unused;
            for (auto& b : load) {
                std::tuple<int, int, int> temp = b.first;
                int l = std::get<0>(temp), h = std::get<1>(temp), w = std::get<2>(temp), quantity = b.second;
                Rectangle rec(l, h, w);
                for (int j = 0; j < quantity; j++) {
                    vec.push_back(rec);
                }
            }*/


            /* struct RectCMP_SORT {
                 bool operator() (const Rectangle& rec1, const Rectangle& rec2) const {
                     return (rec1.topLeftLHS > rec2.topLeftLHS && rec1.topLeftRHS > rec2.topLeftRHS && rec1.topRightLHS > rec2.topRightLHS && rec1.topRightRHS > rec2.topRightRHS &&
                         rec1.bottomLeftLHS > rec2.bottomLeftLHS && rec1.bottomLeftRHS > rec2.bottomLeftRHS && rec1.bottomRightLHS > rec2.bottomRightLHS && rec1.bottomRightRHS > rec2.bottomRightRHS);
                     //return rec1 > rec2;
                 }
             };

             std::map<Rectangle, RectCMP_SORT, std::pair<Rectangle, int>> loadMap;

             for (auto & b : boxes) {
                 loadMap[b].second++;
                 loadMap[b].first = b;
             }

             auto it = loadMap.begin();
             std::vector<int> dp(container.getCube()+1);
             std::vector<Rectangle> ans;
             int len = container.getCube(), i = it->second.first.getCube();
             ans.push_back(it->second.first);  it->second.second--;
             dp[0] = 1;

             for (; i <= len; i++) {
                 for (auto& b : loadMap) {
                     if (i - b.second.first.getCube() >= 0 && dp[i - b.second.first.getCube()] > 0 && b.second.second > 0) {
                         b.second.second--;
                         ans.push_back(b.second.first);
                     }

                 }

             }*/


             /* std::vector<Rectangle> vec;
              struct CMP_SORT {
                  bool operator() (const std::tuple<int, int, int> t1, const std::tuple<int, int, int> t2) const {
                      return t1 > t2;
                  }
              };
              std::map<std::tuple<int, int, int>, int, CMP_SORT> load;

              for (auto& b : boxes) {
                  load[std::make_tuple(b.getLength(), b.getHeight(), b.getWidth())]++;
              }

              int xyWise, xzWise, zyWise;
              int len = container.getLength(), height = container.getHeight(), width = container.getWidth();
              for (auto& b : load) {
                  std::tuple<int, int, int> temp = b.first;
                  int l = std::get<0>(temp), h = std::get<1>(temp), w = std::get<2>(temp), quantity;
                  xyWise = b.second - (b.second % (len / l + height / h));
                  xzWise = b.second - (b.second % (len / l + width / w));
                  zyWise = b.second - (b.second % (height / h + width / w));
                  quantity = std::max(std::max(xyWise, xzWise), zyWise);
                  b.second -= quantity;

                  Rectangle rec(l, h, w);
                  for (int j = 0; j < quantity; j++) {
                      vec.push_back(rec);
                  }

              }

              for (auto& b : load) {
                  std::tuple<int, int, int> temp = b.first;
                  int l = std::get<0>(temp), h = std::get<1>(temp), w = std::get<2>(temp), quantity = b.second;
                  Rectangle rec(l, h, w);
                  for (int j = 0; j < quantity; j++) {
                      vec.push_back(rec);
                  }
              }

              boxes = vec;*/
              // int contLen = container.getLength();
              //  int contHeight = container.getHeight();
               // int curArea = 0, totalCube = 0;
               /* for (auto& b : boxes) {
                   // b.rotateBox(b, contLen);
                    totalCube += b.getCube();
                }*/



                /*  std::queue<Rectangle> temp;


                  for (auto& b : boxes) {
                      if (curArea * contHeight <= totalCube) {
                          curArea += b.getLength() * b.getWidth();
                          temp.push(b);  boxes.erase(boxes.begin());
                      }
                      else {
                          break;
                      }
                  }
                  generateBottomBox(temp);
                  std::vector<Rectangle> tempCont; //temp container to store boxes
                  while (!temp.empty()) {

                      Container subCont(temp.front().getLength(), contHeight, temp.front().getWidth()); // small container for calcaulating loading order;
                      //tempCont.push_back(temp.front());
                      temp.pop();

                      for (auto& b : boxes) {
                          if (subCont.isFull(b)) {
                             // tempCont.push_back(b); //if box available for storage push it for storage sequence
                              subCont.Insert(b);
                              boxes.erase(boxes.begin());
                          }
                          else {
                              //Rectangle stackedBoxes(subCont.getLength(), subCont.getHeight(), subCont.getWidth());
                              tempCont.push_back(subCont.container);
                              break;
                          }
                      }
                      if (boxes.size() == 0)
                          break;
                  }

                  while (!temp.empty()) {
                      tempCont.push_back(temp.front());
                      temp.pop();
                  }

                  for (auto& b : boxes) {
                      tempCont.push_back(b);
                  }

                  boxes = tempCont;*/

   
// std::vector<Rectangle> unloadedBoxes;
// Rectangle rec = boxes[0];
  //std::random_shuffle(boxesForLoading.begin(), boxesForLoading.end());
  //std::random_shuffle(boxesForLoading.begin(), boxesForLoading.end());
 /* for (int k = 0; k < (int)containers.size(); k++) {
      int j = 0;
      for (auto & box : boxesForLoading) {
          if (j == 4)
              j = -1;
          j++;
          int q = box.second;
          (box.first.*rotate[j])();
          while (q--) {
              bxRt = 0, ldgApp = 0;
              int i = 0;
              for (auto& cont : containers[k]) {
                  //(b.*rotate[j])();
                  if (i == 6)
                      i = 0;

                  if (!(cont.*check[i])(box.first)) {
                      (cont.*place[i])(box.first);
                  }
                 // else {
                     // unloadedBoxes[i].push_back(box.first);
                  //}
                  i++;
                   else {
                       for (int i = 0; i < 5; i++) {
                           (b.*rotate[i])();
                           if (!(cont.*check[ldgApp])(b)) {
                               (cont.*place[ldgApp])(b);
                               break;
                           }
                       }
                   }
                   //  ldgApp++;

              }

          }
      }
      std::random_shuffle(boxesForLoading.begin(), boxesForLoading.end());
  }*/