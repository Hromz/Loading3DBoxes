#include "Container.h"

Container::Container(float length, float height, float width) {
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
    return (container.getMaxX() >= rec.getMaxX() && container.getMaxY() >= rec.getMaxY() && container.getMaxZ() >= rec.getMaxZ() &&
        container.getMinX() <= rec.getMinX() && container.getMinY() <= rec.getMinY() && container.getMinZ() <= rec.getMinZ());
}

bool Container::noCollision(Rectangle& a, Rectangle& b) {

 /*return (a.getMinX() >= b.getMaxX() || b.getMinX() >= a.getMaxX() ||
            a.getMinY() >= b.getMaxY() || b.getMinY() >= a.getMaxY() ||
            a.getMinZ() >= b.getMaxZ() || b.getMinZ() >= a.getMaxZ());*/
 return (abs((a.getX() + a.getLength() / 2.0f) - (b.getX() + b.getLength() / 2.0f)) * 2.0f < (a.getLength() + b.getLength()) &&
        (abs((a.getY() + a.getHeight() / 2.0f) - (b.getY() + b.getHeight() / 2.0f)) * 2.0f < (a.getHeight() + b.getHeight()) &&
            abs((a.getZ() + a.getWidth() / 2.0f) - (b.getZ() + b.getWidth() / 2.0f)) * 2.0f < (a.getWidth() + b.getWidth())));
   /* return ((a.getMinX() <= b.getMaxX() && a.getMaxX() >= b.getMinX()) &&
        (a.getMinY() <= b.getMaxY() && a.getMaxY() >= b.getMinY()) &&
        (a.getMinZ() <= b.getMaxZ() && a.getMaxZ() >= b.getMinZ()));*/
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
        flag = true;
        return;
    }
    int right = (int)loadingContainer.size()-1;
    Rectangle temp;
    
    for (int i = 0; i < 6; i++) {
        (rec.*rotate[i])();
        for (int i = right; i >= 0; i--) {
            temp = changeCoordsPlacingRHS(rec, loadingContainer[i]);
            if (!collisionInsideContainer(temp, i) && loadedVolume + (temp.getCube()) / 1000000.0f <= getContainerCube()) {
                loadingContainer.push_back(temp);
                loadedVolume += temp.getCube() / 1000000.0f;
                flag = true;
                return;
            }
        }

        for (int i = right; i >= 0; i--) {
            temp = changeCoordsPlacingFront(rec, loadingContainer[i]);
            if (!collisionInsideContainer(temp, i) && loadedVolume + (temp.getCube()) / 1000000.0f <= getContainerCube()) {
                loadingContainer.push_back(temp);
                loadedVolume += temp.getCube() / 1000000.0f;
                flag = true;
                return;
            }
        }

        for (int i = right; i >= 0; i--) {
            temp = changeCoordsPlacingTop(rec, loadingContainer[i]);
            if (!collisionInsideContainer(temp, i) && loadedVolume + (temp.getCube()) / 1000000.0f <= getContainerCube()) {
                loadingContainer.push_back(temp);
                loadedVolume += temp.getCube() / 1000000.0f;
                flag = true;
                return;
            }
        }
    }
   
}

void Container::merge_boxes(std::vector<std::pair<Rectangle, std::pair<int, bool>>>& boxes) {
    std::vector<std::pair<Rectangle, std::pair<int, bool>>> ans;

    for (auto r : boxes) {

        Rectangle temp(r.first.getLength()*2.0f, r.first.getHeight(), r.first.getWidth() * 2.0f);
        
        int qty = r.second.first / 4;
        int left_qty = r.second.first % 4;

        if (qty > 0)ans.push_back({ temp, {qty, true } });
        if (left_qty > 0) ans.push_back({ r.first, {left_qty, false } });
    }
    boxes = ans;
}

void Container::loadBoxes(std::vector<std::pair<Rectangle, std::pair<int, bool>>> boxes) {
    float cubes = 0;
        for (auto& box : boxes) {
            Rectangle tempBox = box.first;
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 4);
            int rotate_box = dist6(rng), place_style = dist6(rng);
            int q = box.second.first;

            (tempBox.*rotate[rotate_box])();
            while (q--) {
               if (!isFull(tempBox)) {
                    Insert(tempBox);
                    cubes += (tempBox.getCube()) / 1000000.0f;
                    box.second.first--;
                }
               else {
                   break;
               }
            }
        }
        loadedVolume = cubes;
        boxesLeft = boxes;
}

void Container::unmerge_loadBoxes(std::vector<std::pair<Rectangle, std::pair<int, bool>>> & boxes) {
    std::vector<std::pair<Rectangle, std::pair<int, bool>>> temp;

    for (int i = 0; i < boxes.size(); i++) {
        if (boxes[i].second.first > 0 && boxes[i].second.second) {
            int q = boxes[i].second.first * 4;
            float l = boxes[i].first.getLength();
            float h = boxes[i].first.getHeight();
            float w = boxes[i].first.getWidth();

           // l = std::max(l, std::max(h, w));
           // w = std::min(l, std::max(h, w));
            l /= 2;
            w /= 2;
            Rectangle rec(l, h, w);
            temp.push_back({ rec, {q, false} });
        }
        else if(boxes[i].second.first > 0){
            temp.push_back(boxes[i]);
        }
    }
    boxes = temp;
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