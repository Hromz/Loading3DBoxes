#include "Container.h"


Container::Container(int length, int height, int width)
{
    container.setRectangle(length, height, width);
}

bool Container::containerCollision(Rectangle& rec)
{
    return !(container.getX() >= rec.getX() && container.getY() >= rec.getY() && container.getZ() >= rec.getZ());

}


//Code for coordinate system using top-left coodinates on bounding boxes
bool Container::boxCollision(Rectangle& a, Rectangle& b)
{
    return (abs((a.getX() + a.getLength() / 2) - (b.getX() + b.getLength() / 2)) * 2 < (a.getLength() + b.getLength()) &&
        (abs((a.getY() + a.getHeight() / 2) - (b.getY() + b.getHeight() / 2)) * 2 < (a.getHeight() + b.getHeight()) &&
            abs((a.getZ() + a.getWidth() / 2) - (b.getZ() + b.getWidth() / 2)) * 2 < (a.getWidth() + b.getWidth())));
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


void Container::placeInside(std::vector<Rectangle>& Boxes)
{
    if (loadingContainer.size() == 0)
    {
        loadingContainer.push_back(Boxes[0]);
        Boxes.erase(Boxes.begin());
    }

    for (auto box : Boxes)
    {
        Rectangle temp1 = box;
        bool isPossiblePlaceTop = false; 
        bool isPossiblePlaceFront = false;
        int left = 0, right = (int)loadingContainer.size() - 1, middle = 0;
        while (left < right)
        {
            middle = (left + right) / 2;

            temp1 = changeCoordsPlacingRHS(box, loadingContainer[middle]);
            if (boxCollision(temp1, loadingContainer[middle]) && containerCollision(temp1) && !isPossiblePlaceOnRightHandSide(temp1))
            {
                right = middle - 1;
            }
            else
                left = middle + 1;
        }

        temp1 = changeCoordsPlacingRHS(box, loadingContainer[left]);
        if (!boxCollision(temp1, loadingContainer[left]) && !containerCollision(temp1) && isPossiblePlaceOnRightHandSide(temp1))
        {
            loadingContainer.push_back(temp1);
            isPossiblePlaceTop = true;
            isPossiblePlaceFront = true;
        }

        if (!isPossiblePlaceTop)
        {
            left = 0; right = (int)loadingContainer.size() - 1; middle = 0;

            while (left < right)
            {
                middle = (left + right) / 2;
                temp1 = changeCoordsPlacingTop(box, loadingContainer[middle]);
                if (boxCollision(temp1, loadingContainer[middle]) && containerCollision(temp1) && !isPossiblePlaceOnTopOfBox(temp1))
                {
                    right = middle - 1;
                }
                else
                    left = middle + 1;
            }

            temp1 = changeCoordsPlacingTop(box, loadingContainer[left]);
            if (!boxCollision(temp1, loadingContainer[left]) && !containerCollision(temp1) && isPossiblePlaceOnTopOfBox(temp1))
            {
                loadingContainer.push_back(temp1);
                isPossiblePlaceFront = true;
               
            }

        }

        if (!isPossiblePlaceFront)
        {
            left = 0; right = (int)loadingContainer.size() - 1; middle = 0;

            while (left < right)
            {
                middle = (left + right) / 2;
                temp1 = changeCoordsPlacingFront(box, loadingContainer[middle]);
                if (boxCollision(temp1, loadingContainer[middle]) && containerCollision(temp1) && !isPossiblePlaceInfront(temp1))
                {
                    right = middle - 1;
                }
                else
                    left = middle + 1;
            }

            temp1 = changeCoordsPlacingFront(box, loadingContainer[left]);
            if (!boxCollision(temp1, loadingContainer[left]) && !containerCollision(temp1) && isPossiblePlaceInfront(temp1))
            {
                loadingContainer.push_back(temp1);
            }

        }
    }

}


bool Container::isPossiblePlaceInfront(Rectangle& rec)
{
    return (!collisionInsideContainer(rec));
}

bool Container::isPossiblePlaceOnTopOfBox(Rectangle & rec)
{
    return (!collisionInsideContainer(rec));
}


bool Container::isPossiblePlaceOnRightHandSide(Rectangle & rec)
{
    return (!collisionInsideContainer(rec));
}

//Binary search for collision inside container
bool Container::collisionInsideContainer(Rectangle & rec)
{

    int left = 0, right = (int)loadingContainer.size()-1, middle = 0;

    while (left < right)
    {
        middle = (left + right) / 2;

        if (boxCollision(rec, loadingContainer[left]))
            right = middle-1;
        else
            left = middle+1;
    }

    return (boxCollision(rec, loadingContainer[left]));

}



void Container::printCoords()
{
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
    cout << loadingContainer.size() << " boxes were loaded!\n";
}

