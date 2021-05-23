#include "Container.h"


Container::Container(int length, int height)
{
    container.setRectangle(length, height);
}

bool Container::containerCollision(Rectangle & rec)
{
    return !(container.bottomLeft <= rec.bottomLeft && container.bottomRight.getX() >= rec.bottomRight.getX() && 
        container.topLeft.getY() >= rec.topLeft.getY() && container.topRight >= rec.topRight);
}


//Code for coordinate system using top-left coodinates on bounding boxes
bool Container::boxCollision(Rectangle & a, Rectangle & b)
{
    return (abs((a.getX() + a.getWidth() / 2) - (b.getX() + b.getWidth() / 2)) * 2 < (a.getWidth() + b.getWidth())) &&
        (abs((a.getY() + a.getHeight() / 2) - (b.getY() + b.getHeight() / 2)) * 2 < (a.getHeight() + b.getHeight()));
}

Rectangle Container::changeCoordsPlacingTop(Rectangle& rec, Rectangle & boxInContainer)
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

Rectangle Container::changeCoordsPlacingRHS(Rectangle& rec, Rectangle & boxInContainer)
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


void Container::placeInside(const Rectangle& rec)
{
    Rectangle temp = rec;
    Rectangle temp1 = rec;

    if (loadingContainer.size() == 0)
    {
        loadingContainer.push_back(temp);
        return;
    }

    for (int i = (int)loadingContainer.size()-1; i >=0 ; i--)
    {
        temp1 = changeCoordsPlacingRHS(temp, loadingContainer[i]);
        if (!boxCollision(temp1, loadingContainer[i]) && !containerCollision(temp1) && isPossiblePlaceOnRightHandSide(temp, loadingContainer[i]))
        {
            temp = changeCoordsPlacingRHS(temp, loadingContainer[i]);
            loadingContainer.push_back(temp);
            return;
        }
    }


        for (int i = (int)loadingContainer.size()-1; i >= 0; i--)
        {
           temp1 = changeCoordsPlacingTop(temp, loadingContainer[i]);
            if (!containerCollision(temp1) && isPossiblePlaceOnTopOfBox(temp, loadingContainer[i]))
            {
                temp = changeCoordsPlacingTop(temp, loadingContainer[i]);
                loadingContainer.push_back(temp);
                return;
            }
        }

}

bool Container::isPossiblePlaceOnTopOfBox(Rectangle & rec, Rectangle & boxInContainer)
{
    Rectangle temp = changeCoordsPlacingTop(rec, boxInContainer);
    return (!collisionInsideContainer(temp));
}


bool Container::isPossiblePlaceOnRightHandSide(Rectangle & rec, Rectangle & boxInContainer)
{
    Rectangle temp = changeCoordsPlacingRHS(rec, boxInContainer);
    return (!collisionInsideContainer(temp));
}

bool Container::collisionInsideContainer(Rectangle & rec)
{
    for (int i = (int)loadingContainer.size()-1; i >= 0; i--)
    {
        if (boxCollision(rec, loadingContainer[i]))
            return true;
    }

    return false;
}


void Container::print()
{
    using std::cout;
    for (int j = (int)container.topRight.getY() + 1; j >= 0; j--)
    {
        if (j == 0 || j == (int)container.topRight.getY() + 1)
        {
            for (int i = 0; i < (int)container.topRight.getX() + 1; i++)
            {
                cout << '@';
            }
            cout << "\n";
        }
        else
        {
            for (int i = 0; i < (int)container.topRight.getX() + 1; i++)
            {
                if (i == 0 || i == (int)container.topRight.getX())
                    cout << '@';
                else
                {
                    
                    cout << ' ';
                }

            }
            cout << "\n";
        }
    }


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


void Container::printBoxes()
{
    int boxNumber = 1;

   
        for (int x = container.getWidth(); x >= 0; x--)
        {
            for (int y = (int)container.getWidth(); y >= 0; y--)
            {
                for (int i = 0; i < (int)loadingContainer.size(); i++)
                {
                    if ((x >= loadingContainer[i].bottomLeft.getX() && x <= loadingContainer[i].bottomRight.getX() &&
                        y >= loadingContainer[i].bottomLeft.getY() && y <= loadingContainer[i].bottomRight.getY()) ||
                        (x >= loadingContainer[i].topLeft.getX() && x <= loadingContainer[i].topRight.getX()) &&
                        y >= loadingContainer[i].topLeft.getY() && y <= loadingContainer[i].topRight.getY())
                        std::cout << '*';
                    else if ((y == loadingContainer[i].bottomLeft.getY() || y == loadingContainer[i].bottomRight.getY()))
                        std::cout << '*';
                    else if (x == loadingContainer[i].bottomLeft.getX() / 2 && y == loadingContainer[i].bottomLeft.getY() / 2)
                    {
                        std::cout << boxNumber;
                        boxNumber++;
                    }
                }

            }
            std::cout << '\n';
        }
}
