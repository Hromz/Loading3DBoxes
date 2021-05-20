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

bool Rectangle::containerCollision(Rectangle& rec)
{
    if (bottomLeft <= rec.bottomLeft
        && bottomRight.getX() >= rec.bottomRight.getX()
        && topLeft.getY() >= rec.topLeft.getY()
        && topRight >= rec.topRight) {
        return false;
    }
    return true;
}

bool Rectangle::boxCollision(const Rectangle& rec)
{
    if ((topLeft <= rec.bottomLeft && topRight <= rec.bottomRight)
        || (bottomRight <= rec.bottomLeft && topRight <= rec.topLeft)) {
        return false;
    }

    return true;
}


Rectangle Rectangle::changeCoordsPlacingTop(Rectangle& rec)
{
    Rectangle* temp = new Rectangle;

    temp->bottomLeft = this->topLeft;
    temp->bottomRight = this->topRight;
    temp->topLeft = this->topLeft;
    temp->topLeft.setY(rec.getHeight() + temp->topLeft.getY());
    temp->topRight = this->topRight;
    temp->topRight.setY(rec.getHeight() + temp->topRight.getY());

    return *temp;
}

Rectangle Rectangle::changeCoordsPlacingRHS(Rectangle& rec)
{
    Rectangle* temp = new Rectangle;

    temp->bottomLeft = this->bottomRight;
    temp->bottomRight = this->bottomRight;
    temp->bottomRight.setX(rec.getLength() + temp->bottomRight.getX());

    temp->topLeft = this->topRight;
    temp->topRight = this->topRight;
    temp->topRight.setX(rec.getLength() + temp->topRight.getX());


    return *temp;
}


void Rectangle::placeInside(const Rectangle& rec)
{
    Rectangle temp = rec;
    Rectangle temp1 = rec;
    bool check = false;
    bool place = true;

    if (container.size() == 0)
    {
        container.push_back(temp);
        return;
    }

    for (int i = 0; i < (int)container.size(); i++)
    {
        temp1 = container[i].changeCoordsPlacingTop(temp);
        if (!containerCollision(temp1) && container[i].isPossiblePlaceOnTopOfBox(temp))
        {
            temp = container[i].changeCoordsPlacingTop(temp);
            container.push_back(temp);
            container[i].setBoxOnTop(place);
            check = true;
            break;
        }
    }

    if (!check) {
        for (int i = 0; i < (int)container.size(); i++)
        {
            temp1 = container[i].changeCoordsPlacingRHS(temp);
            if (container[i].isPossiblePlaceOnRightHandSide(temp) && !containerCollision(temp1))
            {
                temp = container[i].changeCoordsPlacingRHS(temp);
                container.push_back(temp1);
                container[i].setBoxOnTop(place);
                container[i].setBoxOnRHS(place);
                break;
            }
            else
            {
                break;
            }
        }
    }


}

bool Rectangle::isPossiblePlaceOnTopOfBox(Rectangle& rec)
{

    if (!containsBoxOnTop() && !boxCollision(changeCoordsPlacingTop(rec)))
        return true;
    else
        return false;
}


bool Rectangle::isPossiblePlaceOnRightHandSide(Rectangle& rec)
{
    if (!containsBoxRHS() && !boxCollision(changeCoordsPlacingRHS(rec)))
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
        cout << "TopLeft(" << container[i].topLeft.getX() << "," << container[i].topLeft.getY() << ")" << " "
            << "TopRight(" << container[i].topRight.getX() << "," << container[i].topRight.getY() << ")" << "\n";
        cout << "BottomLeft(" << container[i].bottomLeft.getX() << "," << container[i].bottomLeft.getY() << ")" << " "
            << "BotomRight(" << container[i].bottomRight.getX() << "," << container[i].bottomRight.getY() << ")" << "\n";
        cout << "_______________\n";
    }
}