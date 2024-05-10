#pragma once
class Vector2D
{
public:
	float x;
	float y;

	Vector2D();
	Vector2D(float _x, float _y);
	~Vector2D();

	Vector2D operator+(const Vector2D& other) const;
	Vector2D operator-(const Vector2D& other) const;
	Vector2D operator*(const float schlar) const;

	void ToiPoint();
};