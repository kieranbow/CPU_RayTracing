#include "Vector2.h"

Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2 Vector2::operator=(const Vector2& _rhs)
{
	Vector2 vector;
	vector.x = _rhs.x;
	vector.y = _rhs.y;
	return vector;
}

Vector2 Vector2::operator+(const Vector2& _rhs)
{
	Vector2 vector;
	vector.x = this->x + _rhs.x;
	vector.y = this->y + _rhs.y;
	return vector;
}

Vector2 Vector2::operator+(const float& _rhs)
{
	Vector2 vector;
	vector.x = this->x + _rhs;
	vector.y = this->x + _rhs;
	return vector;
}

Vector2 Vector2::operator+=(const Vector2& _rhs)
{
	this->x += _rhs.x;
	this->y += _rhs.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& _rhs)
{
	Vector2 vector;
	vector.x = this->x - _rhs.x;
	vector.y = this->y - _rhs.y;
	return vector;
}

Vector2 Vector2::operator-=(const Vector2& _rhs)
{
	this->x -= _rhs.x;
	this->y -= _rhs.y;
	return *this;
}

Vector2 Vector2::operator*(const Vector2& _rhs)
{
	Vector2 vector;
	vector.x = this->x * _rhs.x;
	vector.y = this->y * _rhs.y;
	return vector;
}

Vector2 Vector2::operator*=(const Vector2& _rhs)
{
	this->x *= _rhs.x;
	this->y *= _rhs.y;
	return *this;
}

Vector2 Vector2::operator/(const Vector2& _rhs)
{
	Vector2 vector;
	vector.x = this->x / _rhs.x;
	vector.y = this->y / _rhs.y;
	return vector;
}

float Vector2::dot(const Vector2& _lhs, const Vector2& _rhs)
{
	return (_lhs.x * _rhs.x) + (_lhs.y * _rhs.y);
}

float Vector2::magnitude(const Vector2& _rhs)
{
	return sqrtf((_rhs.x * _rhs.x) + (_rhs.y * _rhs.y));
}

Vector2 Vector2::normalize(const Vector2& _rhs)
{
	float mag = magnitude(_rhs);

	if (mag < epsilon) return Vector2(0.0f, 0.0f);
	return Vector2(_rhs.x / mag, _rhs.y / mag);
}