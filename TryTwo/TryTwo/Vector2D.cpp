#include <math.h>
#include "Vector2D.h"

Vector2D::Vector2D()
    : x(0), y(0)
{/*empty*/
}

Vector2D::Vector2D(float _x, float _y)
    : x(_x),
    y(_y)
{/*empty*/
}

Vector2D::~Vector2D()
{/*empty*/
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
    Vector2D ansVec(x + other.x, y + other.y);
    return ansVec;
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
    Vector2D ansVec(x - other.x, y - other.y);
    return ansVec;
}

Vector2D Vector2D::operator*(const float schlar) const
{
    Vector2D ansVec(x * schlar, y * schlar);
    return ansVec;
}

void Vector2D::ToiPoint()
{
    x = int(x + 0.5);
    x = float(x);
    y = int(y + 0.5);
    y = float(y);
}