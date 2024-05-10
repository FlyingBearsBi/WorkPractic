#pragma once

#include <iostream>
#include <cmath>

class Vector4D
{
public:
	float x, y, z, w;

	//���幹�캯������������
	Vector4D();
	Vector4D(float _x, float _y, float _z, float _k);
	Vector4D(const Vector4D& other);
	~Vector4D();

	//��ֵ
	Vector4D operator=(const Vector4D& other) const;
	//�ӷ�
	Vector4D operator+(const Vector4D& other) const;
	//����
	Vector4D operator-(const Vector4D& other) const;
	//�˷�
	Vector4D operator*(float scalar) const;

	//��˺Ͳ��
	float Dot(const Vector4D& _other) const;//���
	Vector4D CrossProduct(const Vector4D& _other) const;//���  

	//��ȡ���Ⱥ͹�һ��
	float GetLength() const;
	Vector4D Normalize();

	//�����ĳ˷�
	//Vector4D MatrixMulti(Matrix4x4& _matrix);//���һ������ 
};