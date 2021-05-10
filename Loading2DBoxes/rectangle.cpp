#include "rectangle.h"


Rectangle::Rectangle(const Rectangle & rec)
{
    topLeft = rec.topLeft;
    bottomLeft = rec.bottomLeft;
    topRight = rec.bottomRight;
    bottomRight = rec.bottomRight;
}


Rectangle::Rectangle(Coords& tl, Coords& tr, Coords& bl, Coords& br)
{
    topLeft.setX(tl.getX());
    topLeft.setY(tl.getY());

    topRight.setX(tr.getX());
    topRight.setY(tr.getY());

    bottomLeft.setX(bl.getX());
    bottomLeft.setY(bl.getY());

    bottomRight.setX(br.getX());
    bottomRight.setY(br.getY());

}

Rectangle::Rectangle(float length, float height)
{
    topLeft.setX(0); topLeft.setY(height);

    topRight.setX(length); topRight.setY(height);

    bottomLeft.setX(0); bottomLeft.setY(0);

    bottomRight.setX(length); bottomRight.setY(0);
}

bool Rectangle::containerCollision(const Rectangle& rec)
{
    if (bottomLeft <= rec.bottomLeft
        && bottomRight <= rec.bottomRight
        && topLeft >= rec.topLeft
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



void Rectangle::placeInside(Rectangle& rec)
{
    if (container.size() == 0)
    {
        container.push_back(rec);
        return;
    }

    for (int i = 0; i < (int)container.size(); i++)
    {
        if (!containerCollision(rec) && !container[i].boxCollision(rec))
        {
            rec.movePosition(container[i]);
            container.push_back(rec);
        }
    }
}

void Rectangle::movePosition(const Rectangle neighbourRec)
{
    if (isPossiblePlaceOnTopOfBox(neighbourRec))
    {
        placeOnTopOfBox(neighbourRec);
    }
    else if (isPossiblePlaceOnRightHandSide(neighbourRec))
    {
        placeOnRightHandSide(neighbourRec);
    }

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
                    cout << ' ';
            }
            cout << "\n";
        }
    }


}


bool Rectangle::isPossiblePlaceOnTopOfBox(const Rectangle& rec)
{

    return true;
}

void Rectangle::placeOnTopOfBox(const Rectangle& rec)
{

}


bool Rectangle::isPossiblePlaceOnRightHandSide(const Rectangle& rec)
{
    return true;
}

void Rectangle::placeOnRightHandSide(const Rectangle& rec)
{

}
