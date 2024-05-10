#include "Vector3D.h"


//定义无参构造函数和有参构造函数
Vector3D::Vector3D()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3D::Vector3D(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3D::~Vector3D()
{/*empty*/
}


//加法
Vector3D Vector3D::operator+(const Vector3D& other) const
{
	return Vector3D(x + other.x, y + other.y, z + other.z);
}

//减法
Vector3D Vector3D::operator-(const Vector3D& other) const
{
	return Vector3D(x - other.x, y - other.y, z - other.z);
}

//乘法
Vector3D Vector3D::operator*(float scalar) const
{
	return Vector3D(x * scalar, y * scalar, z * scalar);
}

//向量点积
float Vector3D::dot(const Vector3D& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

//叉积
Vector3D Vector3D::cross(const Vector3D& other) const {
	return Vector3D(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	);
}

//向量长度
float Vector3D::length() const {
	return std::sqrt(x * x + y * y + z * z);
}

//归一化
Vector3D Vector3D::normalize() const {
	float len = length();
	return Vector3D(x / len, y / len, z / len);
}

//顶点化
void Vector3D::ToiPoint()
{
	x = int(x + 0.5);
	x = float(x);
	y = int(y + 0.5);
	y = float(y);
	z = int(z + 0.5);
	z = float(z);
}