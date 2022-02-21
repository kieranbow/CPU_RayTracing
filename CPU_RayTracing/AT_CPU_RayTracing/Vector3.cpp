#include "Vector3.h"

Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3 Vector3::operator=(const Vector3& _rhs)
{
	Vector3 vector;
	vector.x = _rhs.x;
	vector.y = _rhs.y;
	vector.z = _rhs.z;
	return vector;
}

Vector3 Vector3::operator+(const Vector3& _rhs)
{
	Vector3 vector;
	vector.x = this->x + _rhs.x;
	vector.y = this->y + _rhs.y;
	vector.z = this->z + _rhs.z;
	return vector;
}

Vector3 Vector3::operator+(const float& _rhs)
{
	Vector3 vector;
	vector.x = this->x + _rhs;
	vector.y = this->x + _rhs;
	vector.z = this->x + _rhs;
	return vector;
}

Vector3 Vector3::operator+=(const Vector3& _rhs)
{
	this->x += _rhs.x;
	this->y += _rhs.y;
	this->z += _rhs.z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& _rhs)
{
	Vector3 vector;
	vector.x = this->x - _rhs.x;
	vector.y = this->y - _rhs.y;
	vector.z = this->z - _rhs.z;
	return vector;
}

Vector3 Vector3::operator-=(const Vector3& _rhs)
{
	this->x -= _rhs.x;
	this->y -= _rhs.y;
	this->z -= _rhs.z;
	return *this;
}

Vector3 Vector3::operator*(const Vector3& _rhs)
{
	Vector3 vector;
	vector.x = this->x * _rhs.x;
	vector.y = this->y * _rhs.y;
	vector.z = this->z * _rhs.z;
	return vector;
}

Vector3 Vector3::operator*=(const Vector3& _rhs)
{
	this->x *= _rhs.x;
	this->y *= _rhs.y;
	this->z *= _rhs.z;
	return *this;
}

Vector3 Vector3::operator/(const Vector3& _rhs)
{
	Vector3 vector;
	vector.x = this->x / _rhs.x;
	vector.y = this->y / _rhs.y;
	vector.z = this->z / _rhs.z;
	return vector;
}

Vector3 Vector3::cross(const Vector3& _lhs, const Vector3& _rhs)
{
	float x = (_lhs.y * _rhs.z) - (_lhs.z * _rhs.y);
	float y = (_lhs.z * _rhs.x) - (_lhs.x * _rhs.z);
	float z = (_lhs.x * _rhs.y) - (_lhs.y * _rhs.x);
	return Vector3(x, y, z);
}

float Vector3::dot(const Vector3& _lhs, const Vector3& _rhs)
{
	return (_lhs.x * _rhs.x) + (_lhs.y * _rhs.y) + (_lhs.z * _rhs.z);
}

float Vector3::magnitude(const Vector3& _rhs)
{
	return sqrtf((_rhs.x * _rhs.x) + (_rhs.y * _rhs.y) + (_rhs.z * _rhs.z));
}

Vector3 Vector3::normalize(const Vector3& _rhs)
{
	float mag = magnitude(_rhs);

	if (mag < epsilon) return Vector3(0.0f, 0.0f, 0.0f);
	return Vector3(_rhs.x / mag, _rhs.y / mag, _rhs.z / mag);
}