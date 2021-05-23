#pragma once
#ifndef COORDS_H
#define COORDS_H
class Coords
{
private:
    int x, y;
public:
    Coords() { x = 0; y = 0; };
    Coords(int x, int y) { this->x = x; this->y = y; };
    Coords(Coords& c) { x = c.x; y = c.y; };
    ~Coords() {};

    int getX() { return x; }
    int getY() { return y; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }

    void resize(const Coords& c);
    void setCoords(int width, int height) { x = width, y = height; }

    Coords operator +(const Coords & c1)
    {
        Coords * temp = new Coords;
        temp->x = x + c1.x;
        temp->y = y + c1.y;
     
        return *temp;
    }

    Coords operator -(const Coords& c1)
    {
        Coords * temp = new Coords;
        temp->x = x - c1.x;
        temp->y = y - c1.y;

        return *temp;
    }

    Coords operator =(const Coords& c1)
    {
        
        x = c1.x;
        y = c1.y;

        return *this;
    }

    friend bool operator==(const Coords& c1, const Coords& c2)
    {
        return (c1.x == c2.x && c1.y == c2.y);
    }

    friend bool operator!=(const Coords& c1, const Coords& c2)
    {
        return (c1.x != c2.x && c1.y != c2.y);
    }

    friend bool operator<=(const Coords& c1, const Coords& c2)
    {
        return (c1.x <= c2.x && c1.y <= c2.y);
    }

    friend bool operator>=(const Coords& c1, const Coords& c2)
    {
        return (c1.x >= c2.x && c1.y >= c2.y);
    }

    friend bool operator<(const Coords& c1, const Coords& c2)
    {
        return (c1.x < c2.x && c1.y < c2.y);
    }

    friend bool operator>(const Coords& c1, const Coords& c2)
    {
        return (c1.x > c2.x && c1.y > c2.y);
    }

};

#endif // COORDS_H