#include "mathematics.hpp"

Coordinate2::Coordinate2():
    x(0),
    y(0)
{
}

Coordinate2::Coordinate2(int inX, int inY):
    x(inX),
    y(inY)
{
}

void Coordinate2::set(int inX, int inY)
{
    x = inX;
    y = inY;
}