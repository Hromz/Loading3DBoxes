#pragma once
#ifndef COORDS_H
#define COORDS_H
class Coords
{
private:
    int x, y, z;
public:
    Coords() { x = 0; y = 0; z = 0; };
    Coords(int x, int y, int z) { this->x = x; this->y = y; this->z = z; };
    Coords(Coords& c) { x = c.x; y = c.y; z = c.z;};
    ~Coords() {};

    int getX() { return x; }
    int getY() { return y; }
    int getZ() { return z; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void setZ(int z) { this->z = z; }

    void resize(const Coords& c);
    void setCoords(int length, int width, int height) { x = length, y = height, z = width; }

    Coords operator +(const Coords & c1)
    {
        Coords * temp = new Coords;
        temp->x = x + c1.x;
        temp->y = y + c1.y;
        temp->z = z + c1.z;
        return *temp;
    }

    Coords operator -(const Coords& c1)
    {
        Coords * temp = new Coords;
        temp->x = x - c1.x;
        temp->y = y - c1.y;
        temp->z = z - c1.z;
        return *temp;
    }

    Coords operator =(const Coords& c1)
    {
        
        x = c1.x;
        y = c1.y;
        z = c1.z;
        return *this;
    }

    friend bool operator==(const Coords& c1, const Coords& c2)
    {
        return (c1.x == c2.x && c1.y == c2.y && c1.z == c2.z);
    }

    friend bool operator!=(const Coords& c1, const Coords& c2)
    {
        return (c1.x != c2.x && c1.y != c2.y && c1.z != c2.z);
    }

    friend bool operator<=(const Coords& c1, const Coords& c2)
    {
        return (c1.x <= c2.x && c1.y <= c2.y && c1.z <= c2.z);
    }

    friend bool operator>=(const Coords& c1, const Coords& c2)
    {
        return (c1.x >= c2.x && c1.y >= c2.y && c1.z >= c2.z);
    }

    friend bool operator<(const Coords& c1, const Coords& c2)
    {
        return (c1.x < c2.x && c1.y < c2.y && c1.z < c2.z);
    }

    friend bool operator>(const Coords& c1, const Coords& c2)
    {
        return (c1.x > c2.x && c1.y > c2.y && c1.z > c2.z);
    }

};

#endif // COORDS_H