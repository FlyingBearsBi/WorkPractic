#pragma once
#include <iostream>
#include <cmath>

class Vector3D {
public:
    float x, y, z;

    // ���캯��
    Vector3D();
    Vector3D(float _x, float _y, float _z);
    ~Vector3D();
    // �����ӷ�
    Vector3D operator+(const Vector3D& other) const;

    // ��������
    Vector3D operator-(const Vector3D& other) const;

    // ����������ĳ˷������ţ�
    Vector3D operator*(float scalar) const;

    // �������
    float dot(const Vector3D& other) const;

    // �������
    Vector3D cross(const Vector3D& other) const;

    // �������ȣ�ģ��
    float length() const;

    // ������һ��
    Vector3D normalize() const;

    // ���㻯
    void ToiPoint();
};
