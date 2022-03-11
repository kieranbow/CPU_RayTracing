#include "Vector3.h"

Vector3::Vector3()
{
	value.at(Maths::coord::x) = 0.0f;
	value.at(Maths::coord::y) = 0.0f;
	value.at(Maths::coord::z) = 0.0f;
}

Vector3& Vector3::operator=(const Vector3& _rhs)
{
	this->value.at(Maths::coord::x) = _rhs.value.at(Maths::coord::x);
	this->value.at(Maths::coord::y) = _rhs.value.at(Maths::coord::y);
	this->value.at(Maths::coord::z) = _rhs.value.at(Maths::coord::z);
	return *this;
}

Vector3 Vector3::operator+(const Vector3& _rhs)
{
	Vector3 vector;
	vector.value.at(Maths::coord::x) = this->value.at(Maths::coord::x) + _rhs.value.at(Maths::coord::x);
	vector.value.at(Maths::coord::y) = this->value.at(Maths::coord::y) + _rhs.value.at(Maths::coord::y);
	vector.value.at(Maths::coord::z) = this->value.at(Maths::coord::z) + _rhs.value.at(Maths::coord::z);
	return vector;
}

Vector3 Vector3::operator+(const float& _rhs)
{
	Vector3 vector;
	vector.value.at(Maths::coord::x) = this->value.at(Maths::coord::x) + _rhs;
	vector.value.at(Maths::coord::y) = this->value.at(Maths::coord::y) + _rhs;
	vector.value.at(Maths::coord::z) = this->value.at(Maths::coord::z) + _rhs;
	return vector;
}

Vector3 Vector3::operator+=(const Vector3& _rhs)
{
	this->value.at(Maths::coord::x) += _rhs.value.at(Maths::coord::x);
	this->value.at(Maths::coord::y) += _rhs.value.at(Maths::coord::y);
	this->value.at(Maths::coord::z) += _rhs.value.at(Maths::coord::z);
	return *this;
}

Vector3 Vector3::operator-(const Vector3& _rhs)
{
	Vector3 vector;
	vector.value.at(Maths::coord::x) = this->value.at(Maths::coord::x) - _rhs.value.at(Maths::coord::x);
	vector.value.at(Maths::coord::y) = this->value.at(Maths::coord::y) - _rhs.value.at(Maths::coord::y);
	vector.value.at(Maths::coord::z) = this->value.at(Maths::coord::z) - _rhs.value.at(Maths::coord::z);
	return vector;
}

Vector3 Vector3::operator-=(const Vector3& _rhs)
{
	this->value.at(Maths::coord::x) -= _rhs.value.at(Maths::coord::x);
	this->value.at(Maths::coord::y) -= _rhs.value.at(Maths::coord::y);
	this->value.at(Maths::coord::z) -= _rhs.value.at(Maths::coord::z);
	return *this;
}

Vector3 Vector3::operator*(const Vector3& _rhs)
{
	Vector3 vector;
	vector.value.at(Maths::coord::x) = this->value.at(Maths::coord::x) * _rhs.value.at(Maths::coord::x);
	vector.value.at(Maths::coord::y) = this->value.at(Maths::coord::y) * _rhs.value.at(Maths::coord::y);
	vector.value.at(Maths::coord::z) = this->value.at(Maths::coord::z) * _rhs.value.at(Maths::coord::z);
	return vector;
}

Vector3 Vector3::operator*=(const Vector3& _rhs)
{
	this->value.at(Maths::coord::x) *= _rhs.value.at(Maths::coord::x);
	this->value.at(Maths::coord::y) *= _rhs.value.at(Maths::coord::y);
	this->value.at(Maths::coord::z) *= _rhs.value.at(Maths::coord::z);
	return *this;
}

Vector3 Vector3::operator/=(const Vector3& _rhs)
{
	this->value.at(Maths::coord::x) /= _rhs.value.at(Maths::coord::x);
	this->value.at(Maths::coord::y) /= _rhs.value.at(Maths::coord::y);
	this->value.at(Maths::coord::z) /= _rhs.value.at(Maths::coord::z);
	return *this;
}

Vector3 Vector3::operator/(const Vector3& _rhs)
{
	Vector3 vector;
	vector.value.at(Maths::coord::x) = this->value.at(Maths::coord::x) / _rhs.value.at(Maths::coord::x);
	vector.value.at(Maths::coord::y) = this->value.at(Maths::coord::y) / _rhs.value.at(Maths::coord::y);
	vector.value.at(Maths::coord::z) = this->value.at(Maths::coord::z) / _rhs.value.at(Maths::coord::z);
	return vector;
}

bool Vector3::operator>(const Vector3& _rhs)
{
	return (this->value.at(Maths::coord::x) > _rhs.value.at(Maths::coord::x) && this->value.at(Maths::coord::y) > _rhs.value.at(Maths::coord::y) && this->value.at(Maths::coord::z) > _rhs.value.at(Maths::coord::z));
}

bool Vector3::operator<(const Vector3& _rhs)
{
	return (this->value.at(Maths::coord::x) < _rhs.value.at(Maths::coord::x) && this->value.at(Maths::coord::y) < _rhs.value.at(Maths::coord::y) && this->value.at(Maths::coord::z) < _rhs.value.at(Maths::coord::z));
}

bool Vector3::operator>=(const Vector3& _rhs)
{
	return (this->value.at(Maths::coord::x) >= _rhs.value.at(Maths::coord::x) && this->value.at(Maths::coord::y) >= _rhs.value.at(Maths::coord::y) && this->value.at(Maths::coord::z) >= _rhs.value.at(Maths::coord::z));
}

bool Vector3::operator<=(const Vector3& _rhs)
{
	return (this->value.at(Maths::coord::x) <= _rhs.value.at(Maths::coord::x) && this->value.at(Maths::coord::y) <= _rhs.value.at(Maths::coord::y) && this->value.at(Maths::coord::z) <= _rhs.value.at(Maths::coord::z));
}

bool Vector3::operator==(const Vector3& _rhs)
{
	return (this->value.at(Maths::coord::x) == _rhs.value.at(Maths::coord::x) && this->value.at(Maths::coord::y) == _rhs.value.at(Maths::coord::y) && this->value.at(Maths::coord::z) == _rhs.value.at(Maths::coord::z));
}

bool Vector3::operator!=(const Vector3& _rhs)
{
	return (this->value.at(Maths::coord::x) != _rhs.value.at(Maths::coord::x) && this->value.at(Maths::coord::y) != _rhs.value.at(Maths::coord::y) && this->value.at(Maths::coord::x) != _rhs.value.at(Maths::coord::x));
}

Vector3 Vector3::cross(const Vector3& _lhs, const Vector3& _rhs)
{
	float x = (_lhs.value.at(Maths::coord::y) * _rhs.value.at(Maths::coord::z)) - (_lhs.value.at(Maths::coord::z) * _rhs.value.at(Maths::coord::y));
	float y = (_lhs.value.at(Maths::coord::z) * _rhs.value.at(Maths::coord::x)) - (_lhs.value.at(Maths::coord::x) * _rhs.value.at(Maths::coord::z));
	float z = (_lhs.value.at(Maths::coord::x) * _rhs.value.at(Maths::coord::y)) - (_lhs.value.at(Maths::coord::y) * _rhs.value.at(Maths::coord::x));
	return Vector3(x, y, z);
}

float Vector3::dot(const Vector3& _lhs, const Vector3& _rhs)
{
	return (_lhs.value.at(Maths::coord::x) * _rhs.value.at(Maths::coord::x)) + (_lhs.value.at(Maths::coord::y) * _rhs.value.at(Maths::coord::y)) + (_lhs.value.at(Maths::coord::z) * _rhs.value.at(Maths::coord::z));
}

float Vector3::magnitude(const Vector3& _rhs)
{
	return sqrtf((_rhs.value.at(Maths::coord::x) * _rhs.value.at(Maths::coord::x)) + (_rhs.value.at(Maths::coord::y) * _rhs.value.at(Maths::coord::y)) + (_rhs.value.at(Maths::coord::z) * _rhs.value.at(Maths::coord::z)));
}

Vector3 Vector3::normalize(const Vector3& _rhs)
{
	float mag = magnitude(_rhs);

	if (mag < Maths::special::epsilon) return Vector3(0.0f, 0.0f, 0.0f);
	return Vector3(_rhs.value.at(Maths::coord::x) / mag, _rhs.value.at(Maths::coord::y) / mag, _rhs.value.at(Maths::coord::z) / mag);
}

Vector3 operator+(const float& _lhs, const Vector3& _rhs)
{
	return Vector3(_rhs.getX() + _lhs, _rhs.getY() + _lhs, _rhs.getZ() + _lhs);
}

Vector3 operator-(const float& _lhs, const Vector3& _rhs)
{
	return Vector3(_rhs.getX() - _lhs, _rhs.getY() - _lhs, _rhs.getZ() - _lhs);
}

Vector3 operator*(const float& _lhs, const Vector3& _rhs)
{
	return Vector3(_rhs.getX() * _lhs, _rhs.getY() * _lhs, _rhs.getZ() * _lhs);
}

Vector3 operator/(const float& _lhs, const Vector3& _rhs)
{
	return Vector3(_rhs.getX() / _lhs, _rhs.getY() / _lhs, _rhs.getZ() / _lhs);
}

Vector3 operator-(const Vector3& _lhs, const float& _rhs)
{
	return Vector3(_lhs.getX() / _rhs, _lhs.getY() / _rhs, _lhs.getZ() / _rhs);
}
