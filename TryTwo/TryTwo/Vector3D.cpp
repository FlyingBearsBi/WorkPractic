#include "Vector3D.h"


//�����޲ι��캯�����вι��캯��
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


//�ӷ�
Vector3D Vector3D::operator+(const Vector3D& other) const
{
	return Vector3D(x + other.x, y + other.y, z + other.z);
}

//����
Vector3D Vector3D::operator-(const Vector3D& other) const
{
	return Vector3D(x - other.x, y - other.y, z - other.z);
}

//�˷�
Vector3D Vector3D::operator*(float scalar) const
{
	return Vector3D(x * scalar, y * scalar, z * scalar);
}

//�������
float Vector3D::dot(const Vector3D& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

//���
Vector3D Vector3D::cross(const Vector3D& other) const {
	return Vector3D(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	);
}

//��������
float Vector3D::length() const {
	return std::sqrt(x * x + y * y + z * z);
}

//��һ��
Vector3D Vector3D::normalize() const {
	float len = length();
	return Vector3D(x / len, y / len, z / len);
}

//���㻯
void Vector3D::ToiPoint()
{
	x = int(x + 0.5);
	x = float(x);
	y = int(y + 0.5);
	y = float(y);
	z = int(z + 0.5);
	z = float(z);
}