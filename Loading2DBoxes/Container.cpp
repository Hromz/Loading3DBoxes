#include "Container.h"


Container::Container(int length, int height, int width)
{
    container.setRectangle(length, height, width);
}

bool Container::containerCollision(Rectangle& rec)
{
    return !(container.bottomLeft <= rec.bottomLeft && container.bottomRight.getX() >= rec.bottomRight.getX() &&
        container.topLeft.getY() >= rec.topLeft.getY() && container.topRight >= rec.topRight);
}


//Code for coordinate system using top-left coodinates on bounding boxes
bool Container::boxCollision(Rectangle& a, Rectangle& b)
{
    return (abs((a.getX() + a.getWidth() / 2) - (b.getX() + b.getWidth() / 2)) * 2 < (a.getWidth() + b.getWidth())) &&
        (abs((a.getY() + a.getHeight() / 2) - (b.getY() + b.getHeight() / 2)) * 2 < (a.getHeight() + b.getHeight()));
}

Rectangle Container::changeCoordsPlacingTop(Rectangle& rec, Rectangle& boxInContainer)
{
    Rectangle* temp = new Rectangle;

    temp->bottomLeft = boxInContainer.topLeft;
    temp->bottomRight = boxInContainer.topRight;
    temp->topLeft = boxInContainer.topLeft;
    temp->topLeft.setY(rec.getHeight() + boxInContainer.topLeft.getY());
    temp->topRight = boxInContainer.topRight;
    temp->topRight.setY(rec.getHeight() + boxInContainer.topRight.getY());

    return *temp;
}

Rectangle Container::changeCoordsPlacingRHS(Rectangle& rec, Rectangle& boxInContainer)
{
    Rectangle* temp = new Rectangle;

    temp->bottomLeft = boxInContainer.bottomRight;
    temp->bottomRight = boxInContainer.bottomRight;
    temp->bottomRight.setX(rec.getWidth() + boxInContainer.bottomRight.getX());
    temp->topLeft = boxInContainer.topRight;
    temp->topRight = boxInContainer.topRight;
    temp->topRight.setX(rec.getWidth() + boxInContainer.topRight.getX());

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
        //Rectangle temp = box;
        Rectangle temp1 = box;
        bool isPossiblePlaceTop = false;
        while (left < right)
        {
            middle = (left + right) / 2;
            //Rectangle temp1 = box;
            temp1 = changeCoordsPlacingRHS(box, loadingContainer[middle]);
            if (boxCollision(temp1, loadingContainer[middle]) && containerCollision(temp1) && !isPossiblePlaceOnRightHandSide(temp1, loadingContainer[middle]))
            {
                right = middle - 1;
            }
            else
                left = middle + 1;
        }

        temp1 = changeCoordsPlacingRHS(box, loadingContainer[left]);
        if (!boxCollision(temp1, loadingContainer[left]) && !containerCollision(temp1) && isPossiblePlaceOnRightHandSide(temp1, loadingContainer[left]))
        {
            loadingContainer.push_back(temp1);
            isPossiblePlaceTop = true;
        }

        /*for (int j = i; j >= 0; j--)
        {
            temp1 = changeCoordsPlacingRHS(box, loadingContainer[i]);
            if (!boxCollision(temp1, loadingContainer[i]) && !containerCollision(temp1) && isPossiblePlaceOnRightHandSide(temp1, loadingContainer[i]))
            {
                //temp = changeCoordsPlacingRHS(temp, loadingContainer[i]);
                loadingContainer.push_back(temp1);
                i++;
                isPossiblePlaceTop = true;
                break;
            }
        }*/

        if (!isPossiblePlaceTop)
        {
            left = 0; right = (int)loadingContainer.size() - 1; middle = 0;

            while (left < right)
            {
                middle = (left + right) / 2;
                temp1 = changeCoordsPlacingTop(box, loadingContainer[middle]);
                if (boxCollision(temp1, loadingContainer[middle]) && containerCollision(temp1) && !isPossiblePlaceOnTopOfBox(temp1, loadingContainer[middle]))
                {
                    right = middle - 1;
                }
                else
                    left = middle + 1;
            }

            temp1 = changeCoordsPlacingTop(box, loadingContainer[left]);
            if (!boxCollision(temp1, loadingContainer[left]) && !containerCollision(temp1) && isPossiblePlaceOnTopOfBox(temp1, loadingContainer[left]))
            {
                loadingContainer.push_back(temp1);
            }


           /* for (int j = i; j >= 0; j--)
            {
                temp1 = changeCoordsPlacingTop(box, loadingContainer[i]);
                if (!containerCollision(temp1) && isPossiblePlaceOnTopOfBox(temp1, loadingContainer[i]))
                {
                    //temp = changeCoordsPlacingTop(temp, loadingContainer[i]);
                    loadingContainer.push_back(temp1);
                    i++;
                    break;
                }
            }*/
        }
    }

}

bool Container::isPossiblePlaceOnTopOfBox(Rectangle & rec)//, Rectangle & boxInContainer)
{
    //Rectangle temp = changeCoordsPlacingTop(rec, boxInContainer);
    return (!collisionInsideContainer(rec));
}


bool Container::isPossiblePlaceOnRightHandSide(Rectangle & rec)//, Rectangle & boxInContainer)
{
   // Rectangle temp = changeCoordsPlacingRHS(rec, boxInContainer);
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
    for (int i = 0; i < loadingContainer.size(); i++)
    {
        cout << "TopLeft(" << loadingContainer[i].topLeft.getX() << "," << loadingContainer[i].topLeft.getY() << ")" << " "
            << "TopRight(" << loadingContainer[i].topRight.getX() << "," << loadingContainer[i].topRight.getY() << ")" << "\n";
        cout << "BottomLeft(" << loadingContainer[i].bottomLeft.getX() << "," << loadingContainer[i].bottomLeft.getY() << ")" << " "
            << "BotomRight(" << loadingContainer[i].bottomRight.getX() << "," << loadingContainer[i].bottomRight.getY() << ")" << "\n";
        cout << "_______________\n";
    }
}

