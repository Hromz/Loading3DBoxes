#pragma once
#ifndef COORDS_H
#define COORDS_H
class Coords
{
private:
    float x, y;
public:
    Coords() { };
    Coords(float x, float y) { this->x = x; this->y = y; };
    Coords(Coords& c) { x = c.x; y = c.y; };

    float getX() { return x; }
    float getY() { return y; }

    void setX(float x) { this->x = x; }
    void setY(float y) { this->y = y; }

    void resize(const Coords& c);

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

};

#endif // COORDS_H