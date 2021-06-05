#include "Container.h"


Container::Container(int length, int height, int width)
{
    container.setRectangle(length, height, width);
}

bool Container::containerCollision(Rectangle& rec)
{
    return !(container.getX() >= rec.getX() && container.getY() >= rec.getY() && container.getZ() >= rec.getZ());
   /* return !(container.bottomLeft <= rec.bottomLeft && container.bottomRight.getX() >= rec.bottomRight.getX() &&
        container.topLeft.getY() >= rec.topLeft.getY() && container.topRight >= rec.topRight) &&
        (container.bottomLeftRight >= rec.bottomLeftRight && container.bottomRightRight >= rec.bottomRightRight &&
            container.topLeftLeft.getY() >= rec.topLeftLeft.getY() && container.topRightRight >= rec.topRightRight);*/
}


//Code for coordinate system using top-left coodinates on bounding boxes
bool Container::boxCollision(Rectangle& a, Rectangle& b)
{
    return (abs((a.getX() + a.getLength() / 2) - (b.getX() + b.getLength() / 2)) * 2 < (a.getLength() + b.getLength())) &&
        (abs((a.getY() + a.getHeight() / 2) - (b.getY() + b.getHeight() / 2)) * 2 < (a.getHeight() + b.getHeight()) &&
            abs((a.getZ() + a.getWidth() / 2) - (b.getZ() + b.getWidth() / 2)) * 2 < (a.getWidth() + b.getWidth()));
}

Rectangle Container::changeCoordsPlacingTop(Rectangle & rec, Rectangle & boxInContainer)
{
    Rectangle* temp = new Rectangle;

    temp->bottomLeft = boxInContainer.topLeft;
    temp->bottomRight = temp->bottomLeft;
    temp->bottomRight.moveLengthCoordinate(rec.getLength());

    temp->topLeft = temp->bottomLeft;
    temp->topLeft.moveHeightCoordinate(rec.getHeight());
    temp->topRight = temp->bottomRight;
    temp->topRight.moveHeightCoordinate(rec.getHeight());
    
    temp->bottomLeftRight = temp->bottomLeft;
    temp->bottomLeftRight.moveWidthCoordinate(rec.getWidth());
    temp->bottomRightRight = temp->bottomRight;
    temp->bottomRightRight.moveWidthCoordinate(rec.getWidth());

    temp->topLeftRight = temp->topLeft;
    temp->topLeftRight.moveWidthCoordinate(rec.getWidth());
    temp->topRightRight = temp->topRight;
    temp->topRightRight.moveWidthCoordinate(rec.getWidth()); 

    return *temp;
}

Rectangle Container::changeCoordsPlacingRHS(Rectangle& rec, Rectangle& boxInContainer)
{
    Rectangle* temp = new Rectangle;
    
    temp->bottomLeft = boxInContainer.bottomLeftRight;
    temp->bottomRight = temp->bottomLeft;
    temp->bottomRight.moveLengthCoordinate(rec.getLength());

    temp->topLeft = temp->bottomLeft;
    temp->topLeft.moveHeightCoordinate(rec.getHeight());
    temp->topRight = temp->topLeft;
    temp->topRight.moveLengthCoordinate(rec.getLength());

    temp->bottomLeftRight = temp->bottomLeft;
    temp->bottomLeftRight.moveWidthCoordinate(rec.getWidth());
    temp->bottomRightRight = temp->bottomLeftRight;
    temp->bottomRightRight.moveLengthCoordinate(rec.getLength());

    temp->topLeftRight = temp->bottomLeftRight;
    temp->topLeftRight.moveHeightCoordinate(rec.getHeight());
    temp->topRightRight = temp->topLeftRight;
    temp->topRightRight.moveLengthCoordinate(rec.getLength());

    return *temp;
}


Rectangle Container::changeCoordsPlacingFront(Rectangle& rec, Rectangle& boxInContainer)
{
    Rectangle* temp = new Rectangle;

    temp->bottomLeft = boxInContainer.bottomRight;
    temp->bottomRight = temp->bottomLeft;
    temp->bottomRight.moveLengthCoordinate(rec.getLength());
    temp->topLeft = temp->bottomLeft;
    temp->topLeft.moveHeightCoordinate(rec.getHeight());

    temp->topRight = temp->topLeft;
    temp->topRight.moveLengthCoordinate(rec.getLength());
    temp->bottomLeftRight = temp->bottomLeft;
    temp->bottomLeftRight.moveWidthCoordinate(rec.getWidth());

    temp->bottomRightRight = temp->bottomRight;
    temp->bottomRightRight.moveWidthCoordinate(rec.getWidth());

    temp->topLeftRight = temp->bottomLeftRight;
    temp->topLeftRight.moveHeightCoordinate(rec.getHeight());  
    temp->topRightRight = temp->topLeftRight;
    temp->topRightRight.moveLengthCoordinate(rec.getLength());

    return *temp;
}


void Container::placeInside(std::vector<Rectangle>& Boxes)
{
    if (loadingContainer.size() == 0)
    {
        loadingContainer.push_back(Boxes[0]);
        Boxes.erase(Boxes.begin());
    }

    int left = 0, right = (int)loadingContainer.size() - 1, middle = 0;

    int i = 0;
    for (auto box : Boxes)
    {
        Rectangle temp1 = box;
        bool isPossiblePlaceTop = false; 
        bool isPossiblePlaceFront = false;

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
               // isPossiblePlaceFront = true;
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
        cout << "TopLeft(" << loadingContainer[i].topLeft.getX() << "," << loadingContainer[i].topLeft.getY() << "," << loadingContainer[i].topLeft.getZ() << ")" << " "
            << "TopLeftRight(" << loadingContainer[i].topLeftRight.getX() << "," << loadingContainer[i].topLeftRight.getY() << "," << loadingContainer[i].topLeftRight.getZ() << ")" << "\n";

        cout << "TopRight(" << loadingContainer[i].topRight.getX() << "," << loadingContainer[i].topRight.getY() << "," << loadingContainer[i].topRight.getZ() << ")" << " "
            << "TopRightRight(" << loadingContainer[i].topRightRight.getX() << "," << loadingContainer[i].topRightRight.getY() << "," << loadingContainer[i].topRightRight.getZ() << ")" << "\n";

        cout << "BottomLeft(" << loadingContainer[i].bottomLeft.getX() << "," << loadingContainer[i].bottomLeft.getY() <<  "," << loadingContainer[i].bottomLeft.getZ() << ")" << " "
            << "BotomLeftRight(" << loadingContainer[i].bottomLeftRight.getX() << "," << loadingContainer[i].bottomLeftRight.getY() << "," << loadingContainer[i].bottomLeftRight.getZ() << ")" << "\n";

        cout << "BottomRight(" << loadingContainer[i].bottomRight.getX() << "," << loadingContainer[i].bottomRight.getY() << "," << loadingContainer[i].bottomRight.getZ() << ")" << " "
            << "BotomRightRight(" << loadingContainer[i].bottomRightRight.getX() << "," << loadingContainer[i].bottomRightRight.getY() << "," << loadingContainer[i].bottomRightRight.getZ() << ")" << "\n";
        cout << "________________________________________________________________________\n";
    }
}

