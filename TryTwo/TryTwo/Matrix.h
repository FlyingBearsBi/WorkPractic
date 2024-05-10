#pragma once
#pragma once
#include "Vector4D.h"
const float PIOver180 = 3.1415926535 / 180.0;

class Matrix4x4
{
public:
	float data[4][4];

	Matrix4x4();
	Matrix4x4(const Matrix4x4& _other);
	~Matrix4x4();


	//矩阵间的加减法
	Matrix4x4 operator+(Matrix4x4& _other);
	Matrix4x4 operator-(Matrix4x4& _other);
	//矩阵之间的乘法
	Matrix4x4 operator*(const Matrix4x4& other) const;
	Matrix4x4 LeftCrossProduct(const Matrix4x4& other) const;

	//矩阵与向量之间的乘法
	Vector4D operator*(const Vector4D& vec) const;

	//归零
	void Zero();
	//设为单位阵
	void Identity();

	//平移旋转缩放
	static Matrix4x4 CreateScale(const Vector4D& _scale);
	static Matrix4x4 CreateTrans(const Vector4D& _trans);
	//旋转均用角度表示
	static Matrix4x4 CreateRotateX(float _angle);
	static Matrix4x4 CreateRotateY(float _angle);
	static Matrix4x4 CreateRotateZ(float _angle);

	//MVP变换
	static Matrix4x4 BuildWorldTransform(
		const Vector4D& _postion,
		const Vector4D& _scale,
		float _xAngle,
		float _yAngle,
		float _zAngle);

	//static Matrix4x4 BuildLookAtLH(
	//	const Vector4D& _position,
	//	const Vector4D& _upVector,
	//	const Vector4D& _right);

	//static Matrix4x4 BuildPerspectiveLH(
	//	float _fovY,
	//	float _aspect,
	//	float _zNear,
	//	float _zFar);

	Matrix4x4 BuildViewPort(
		float _x,
		float _y,
		float _width,
		float _height,
		float depth);

};