
#include "Vector3i.h"

Vector3i::Vector3i()
{
	x = 0;
	y = 0;
	z = 1;
}

Vector3i::Vector3i(int _x, int _y, int _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3i::Vector3i(Vector3D _other)
{
	x = int(_other.x);
	y = int(_other.y);
	z = int(_other.z);
}

Vector3i::~Vector3i()
{

}