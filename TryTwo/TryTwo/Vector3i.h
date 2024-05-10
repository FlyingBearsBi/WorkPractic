#pragma once

#include "Vector3D.h";

class Vector3i
{
public:
    int x, y, z;

    Vector3i();
    Vector3i(int _x, int _y, int _z);
    Vector3i(Vector3D _other);
    ~Vector3i();
};
