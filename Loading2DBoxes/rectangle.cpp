#include "rectangle.h"


Rectangle::Rectangle(const Rectangle& rec)
{
    this->topLeft = rec.topLeft;
    this->bottomLeft = rec.bottomLeft;
    this->topRight = rec.topRight;
    this->bottomRight = rec.bottomRight;

}


Rectangle::Rectangle(Coords& tl, Coords& tr, Coords& bl, Coords& br)
{
    topLeft.setX(tl.getX());  topLeft.setY(tl.getY());  topRight.setX(tr.getX());    topRight.setY(tr.getY());
    bottomLeft.setX(bl.getX());  bottomLeft.setY(bl.getY());  bottomRight.setX(br.getX());  bottomRight.setY(br.getY());
}

Rectangle::Rectangle(int length, int height)
{
    topLeft.setX(0); topLeft.setY(height);  topRight.setX(length); topRight.setY(height);
    bottomLeft.setX(0); bottomLeft.setY(0);  bottomRight.setX(length); bottomRight.setY(0);
}

bool Rectangle::containerCollision(const Rectangle& rec)
{
    if (bottomLeft <= rec.bottomLeft
        && bottomRight <= rec.bottomRight
        && topLeft >= rec.topLeft
        && topRight >= rec.topRight) {
        return true;
    }
    return false;
}

bool Rectangle::boxCollision(const Rectangle& rec)
{
    if ((topLeft <= rec.bottomLeft && topRight <= rec.bottomRight)
        || (bottomRight <= rec.bottomLeft && topRight <= rec.topLeft)) {
        return false;
    }

    return true;
}


Rectangle Rectangle::changeCoordsPlacingTop(const Rectangle& rec)
{
    Rectangle* temp = new Rectangle;

    temp->bottomLeft = this->topLeft;
    temp->bottomRight = this->topRight;
    temp->topLeft = (this->topLeft + rec.topLeft);
    temp->topRight = (this->topRight + rec.topRight);

    return *temp;
}

Rectangle Rectangle::changeCoordsPlacingRHS(const Rectangle& rec)
{
    Rectangle* temp = new Rectangle;

    temp->bottomLeft = this->bottomRight;
    temp->bottomRight = this->bottomRight + rec.bottomRight;
    temp->topLeft = this->topRight;
    temp->topRight = this->topRight + rec.topLeft;


    return *temp;
}


void Rectangle::placeInside(const Rectangle& rec)
{
    Rectangle temp = rec;

    if (container.size() == 0)
    {
        container.push_back(temp);
        return;
    }

    for (int i = 0; i < (int)container.size(); i++)
    {
        if (container[i].isPossiblePlaceOnTopOfBox(temp) && !containerCollision(temp))
        {
            temp = container[i].changeCoordsPlacingTop(temp);
            container.push_back(temp);
            container[i].setBoxOnTop(true);
            break;
        }
        else if (container[i].isPossiblePlaceOnRightHandSide(temp) && !containerCollision(temp))
        {
            temp = container[i].changeCoordsPlacingRHS(temp);
            container.push_back(temp);
            container[i].setBoxOnRHS(true);
            break;
        }
        else
        {
            break;
        }


    }

}

bool Rectangle::isPossiblePlaceOnTopOfBox(const Rectangle& rec)
{

    if (!containsBoxOnTop() && !containerCollision(changeCoordsPlacingTop(rec)))
        return true;
    else
        return false;
}


bool Rectangle::isPossiblePlaceOnRightHandSide(const Rectangle& rec)
{
    if (!containsBoxRHS() && !containerCollision(changeCoordsPlacingRHS(rec)))
        return true;
    else
        return false;
}



void Rectangle::print()
{
    using std::cout;
    for (int j = (int)topRight.getY() + 1; j >= 0; j--)
    {
        if (j == 0 || j == (int)topRight.getY() + 1)
        {
            for (int i = 0; i < (int)topRight.getX() + 1; i++)
            {
                cout << '@';
            }
            cout << "\n";
        }
        else
        {
            for (int i = 0; i < (int)topRight.getX() + 1; i++)
            {
                if (i == 0 || i == (int)topRight.getX())
                    cout << '@';
                else
                {
                    /* for (int i = 0; i < container.size(); i++)
                     {

                     }*/
                    cout << ' ';
                }

            }
            cout << "\n";
        }
    }


}


void Rectangle::printCoords()
{
    using std::cout;
    for (int i = 0; i < container.size(); i++)
    {
        cout << "(" << container[i].topLeft.getX() << "," << container[i].topLeft.getY() << ")" << " "
            << "(" << container[i].topRight.getX() << "," << container[i].topRight.getY() << ")" << "\n";
        cout << "(" << container[i].bottomLeft.getX() << "," << container[i].bottomLeft.getY() << ")" << " "
            << "(" << container[i].bottomRight.getX() << "," << container[i].bottomRight.getY() << ")" << "\n";
        cout << "_______________\n";
    }
}