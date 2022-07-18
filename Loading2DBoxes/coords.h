#pragma once
#ifndef COORDS_H
#define COORDS_H
#include <iostream>
class Coords
{
private:
    float x, y, z;
public:
    Coords() { x = 0; y = 0; z = 0; };
    Coords(float x, float y, float z) { this->x = x; this->y = y; this->z = z; };
    Coords(Coords& c) { x = c.x; y = c.y; z = c.z;};
    ~Coords() {};

    float getX() { return x; }
    float getY() { return y; }
    float getZ() { return z; }

    void setX(float x) { this->x = x; }
    void setY(float y) { this->y = y; }
    void setZ(float z) { this->z = z; }

    void moveLengthCoordinate(float x) { this->x += x; }
    void moveHeightCoordinate(float y) { this->y += y; }
    void moveWidthCoordinate(float z) { this->z += z; }

    void resize(const Coords& c);
    void setCoords(float length, float height, float width) { x = length, y = height, z = width; }

    Coords operator +(const Coords & c1){
        Coords * temp = new Coords;
        temp->x = x + c1.x;
        temp->y = y + c1.y;
        temp->z = z + c1.z;
        return *temp;
    }

    Coords operator +=(const Coords& c1) {
        
         x += c1.x;
         y += c1.y;
         z += c1.z;
        return *this;
    }

    Coords operator -(const Coords& c1) {
        Coords * temp = new Coords;
        temp->x = x - c1.x;
        temp->y = y - c1.y;
        temp->z = z - c1.z;
        return *temp;
    }

    Coords operator =(const Coords& c1){       
        x = c1.x;
        y = c1.y;
        z = c1.z;
        return *this;
    }

    friend bool operator==(const Coords& c1, const Coords& c2){
        return (c1.x == c2.x && c1.y == c2.y && c1.z == c2.z);
    }

    friend bool operator!=(const Coords& c1, const Coords& c2){
        return (c1.x != c2.x && c1.y != c2.y && c1.z != c2.z);
    }

    friend bool operator<=(const Coords& c1, const Coords& c2){
        return (c1.x <= c2.x && c1.y <= c2.y && c1.z <= c2.z);
    }

    friend bool operator>=(const Coords& c1, const Coords& c2) {
        return (c1.x >= c2.x && c1.y >= c2.y && c1.z >= c2.z);
    }

    friend bool operator<(const Coords& c1, const Coords& c2){
        return (c1.x < c2.x && c1.y < c2.y && c1.z < c2.z);
    }

    friend bool operator>(const Coords& c1, const Coords& c2) {
        return (c1.x > c2.x && c1.y > c2.y && c1.z > c2.z);
    }

    friend std::ostream & operator<<(std::ostream& os, const Coords& c) {
       os << '(' << c.x << ',' << c.y << ',' << c.z << ')';
        return os;
    }

    void swapCoords(Coords & c1, Coords & c2) {
        Coords temp;

        temp.x = c1.x;
        c1.x = c2.x;
        c2.x = temp.x;

        temp.y = c1.y;
        c1.y = c2.y;
        c2.y = temp.y;

        temp.z = c1.z;
        c1.z = c2.z;
        c2.z = temp.z;
    }

};

#endif // COORDS_H