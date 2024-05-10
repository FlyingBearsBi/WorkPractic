#include <math.h>
#include "Vector4D.h"

Vector4D::Vector4D()
    : x(0), y(0), z(0), w(0)
{/*empty*/
}

Vector4D::Vector4D(float _x, float _y, float _z, float _w)
    : x(_x), y(_y), z(_z), w(_w)
{/*empty*/
}

Vector4D::Vector4D(const Vector4D& other)
    : x(other.x),
    y(other.y),
    z(other.z),
    w(other.w)
{/*empty*/
}

Vector4D::~Vector4D()
{/*empty*/
}

//重载运算法，加减法，乘法和赋值
Vector4D Vector4D::operator=(const Vector4D& other) const
{
    if (this == &other)
    {
        return *this;
    }
    else
    {
        Vector4D ansVec(other.x, other.y, other.z, other.w);
        return ansVec;
    }
}

Vector4D Vector4D::operator+(const Vector4D& other) const
{
    Vector4D ansVec(x + other.x, y + other.y, z + other.z, w + other.z);
    return ansVec;
}

Vector4D Vector4D::operator-(const Vector4D& other) const
{
    Vector4D ansVec(x - other.x, y - other.y, z - other.z, w - other.z);
    return ansVec;
}

Vector4D Vector4D::operator*(float _f) const
{
    Vector4D ansVec(x * _f, y * _f, z * _f, w);
    return ansVec;
}

//点乘
float Vector4D::Dot(const Vector4D& other) const
{
    float ans;
    ans = x * other.x + y * other.y + z * other.z;
    return ans;
}

//向量与向量间叉乘
Vector4D Vector4D::CrossProduct(const Vector4D& other) const
{
    Vector4D ansVec(y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x,
        w);
    return ansVec;
}

//获取长度和归一化
float Vector4D::GetLength() const
{
    return sqrt(x * x + y * y + z * z);
}

Vector4D Vector4D::Normalize()
{
    float len = GetLength();
    return Vector4D(x / len, y / len, z / len, w);
}