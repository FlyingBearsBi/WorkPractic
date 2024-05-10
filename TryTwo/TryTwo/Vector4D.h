#pragma once

#include <iostream>
#include <cmath>

class Vector4D
{
public:
	float x, y, z, w;

	//定义构造函数与析构函数
	Vector4D();
	Vector4D(float _x, float _y, float _z, float _k);
	Vector4D(const Vector4D& other);
	~Vector4D();

	//赋值
	Vector4D operator=(const Vector4D& other) const;
	//加法
	Vector4D operator+(const Vector4D& other) const;
	//减法
	Vector4D operator-(const Vector4D& other) const;
	//乘法
	Vector4D operator*(float scalar) const;

	//点乘和叉乘
	float Dot(const Vector4D& _other) const;//点积
	Vector4D CrossProduct(const Vector4D& _other) const;//叉积  

	//获取长度和归一化
	float GetLength() const;
	Vector4D Normalize();

	//与矩阵的乘法
	//Vector4D MatrixMulti(Matrix4x4& _matrix);//左乘一个矩阵 
};