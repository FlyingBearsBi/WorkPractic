#pragma once
#include <iostream>
#include <cmath>

class Vector3D {
public:
    float x, y, z;

    // 构造函数
    Vector3D();
    Vector3D(float _x, float _y, float _z);
    ~Vector3D();
    // 向量加法
    Vector3D operator+(const Vector3D& other) const;

    // 向量减法
    Vector3D operator-(const Vector3D& other) const;

    // 向量与标量的乘法（缩放）
    Vector3D operator*(float scalar) const;

    // 向量点积
    float dot(const Vector3D& other) const;

    // 向量叉积
    Vector3D cross(const Vector3D& other) const;

    // 向量长度（模）
    float length() const;

    // 向量归一化
    Vector3D normalize() const;

    // 顶点化
    void ToiPoint();
};
