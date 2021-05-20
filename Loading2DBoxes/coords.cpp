#include "coords.h"

void Coords::resize(const Coords& c)
{
    if (x < c.x && y < c.y)
    {
        setX(c.x); setY(c.y);

    }
}
