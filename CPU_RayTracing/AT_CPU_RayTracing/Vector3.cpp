#include "Vector3.h"

Vector3::Vector3()
{
	m_value.at(Maths::coord::x) = 0.0f;
	m_value.at(Maths::coord::y) = 0.0f;
	m_value.at(Maths::coord::z) = 0.0f;
}

Vector3& Vector3::operator=(const Vector3& _rhs)
{
	this->m_value.at(Maths::coord::x) = _rhs.m_value.at(Maths::coord::x);
	this->m_value.at(Maths::coord::y) = _rhs.m_value.at(Maths::coord::y);
	this->m_value.at(Maths::coord::z) = _rhs.m_value.at(Maths::coord::z);
	return *this;
}

Vector3 Vector3::operator+(const Vector3& _rhs)
{
	Vector3 vector;
	vector.m_value.at(Maths::coord::x) = this->m_value.at(Maths::coord::x) + _rhs.m_value.at(Maths::coord::x);
	vector.m_value.at(Maths::coord::y) = this->m_value.at(Maths::coord::y) + _rhs.m_value.at(Maths::coord::y);
	vector.m_value.at(Maths::coord::z) = this->m_value.at(Maths::coord::z) + _rhs.m_value.at(Maths::coord::z);
	return vector;
}

Vector3 Vector3::operator+(const float& _rhs)
{
	Vector3 vector;
	vector.m_value.at(Maths::coord::x) = this->m_value.at(Maths::coord::x) + _rhs;
	vector.m_value.at(Maths::coord::y) = this->m_value.at(Maths::coord::y) + _rhs;
	vector.m_value.at(Maths::coord::z) = this->m_value.at(Maths::coord::z) + _rhs;
	return vector;
}

Vector3 Vector3::operator+=(const Vector3& _rhs)
{
	this->m_value.at(Maths::coord::x) += _rhs.m_value.at(Maths::coord::x);
	this->m_value.at(Maths::coord::y) += _rhs.m_value.at(Maths::coord::y);
	this->m_value.at(Maths::coord::z) += _rhs.m_value.at(Maths::coord::z);
	return *this;
}

Vector3 Vector3::operator-(const Vector3& _rhs)
{
	Vector3 vector;
	vector.m_value.at(Maths::coord::x) = this->m_value.at(Maths::coord::x) - _rhs.m_value.at(Maths::coord::x);
	vector.m_value.at(Maths::coord::y) = this->m_value.at(Maths::coord::y) - _rhs.m_value.at(Maths::coord::y);
	vector.m_value.at(Maths::coord::z) = this->m_value.at(Maths::coord::z) - _rhs.m_value.at(Maths::coord::z);
	return vector;
}

Vector3 Vector3::operator-=(const Vector3& _rhs)
{
	this->m_value.at(Maths::coord::x) -= _rhs.m_value.at(Maths::coord::x);
	this->m_value.at(Maths::coord::y) -= _rhs.m_value.at(Maths::coord::y);
	this->m_value.at(Maths::coord::z) -= _rhs.m_value.at(Maths::coord::z);
	return *this;
}

Vector3 Vector3::operator*(const Vector3& _rhs)
{
	Vector3 vector;
	vector.m_value.at(Maths::coord::x) = this->m_value.at(Maths::coord::x) * _rhs.m_value.at(Maths::coord::x);
	vector.m_value.at(Maths::coord::y) = this->m_value.at(Maths::coord::y) * _rhs.m_value.at(Maths::coord::y);
	vector.m_value.at(Maths::coord::z) = this->m_value.at(Maths::coord::z) * _rhs.m_value.at(Maths::coord::z);
	return vector;
}

Vector3 Vector3::operator*=(const Vector3& _rhs)
{
	this->m_value.at(Maths::coord::x) *= _rhs.m_value.at(Maths::coord::x);
	this->m_value.at(Maths::coord::y) *= _rhs.m_value.at(Maths::coord::y);
	this->m_value.at(Maths::coord::z) *= _rhs.m_value.at(Maths::coord::z);
	return *this;
}

Vector3 Vector3::operator/=(const Vector3& _rhs)
{
	this->m_value.at(Maths::coord::x) /= _rhs.m_value.at(Maths::coord::x);
	this->m_value.at(Maths::coord::y) /= _rhs.m_value.at(Maths::coord::y);
	this->m_value.at(Maths::coord::z) /= _rhs.m_value.at(Maths::coord::z);
	return *this;
}

Vector3 Vector3::operator/(const Vector3& _rhs)
{
	Vector3 vector;
	vector.m_value.at(Maths::coord::x) = this->m_value.at(Maths::coord::x) / _rhs.m_value.at(Maths::coord::x);
	vector.m_value.at(Maths::coord::y) = this->m_value.at(Maths::coord::y) / _rhs.m_value.at(Maths::coord::y);
	vector.m_value.at(Maths::coord::z) = this->m_value.at(Maths::coord::z) / _rhs.m_value.at(Maths::coord::z);
	return vector;
}

bool Vector3::operator>(const Vector3& _rhs)
{
	return (this->m_value.at(Maths::coord::x) > _rhs.m_value.at(Maths::coord::x) && this->m_value.at(Maths::coord::y) > _rhs.m_value.at(Maths::coord::y) && this->m_value.at(Maths::coord::z) > _rhs.m_value.at(Maths::coord::z));
}

bool Vector3::operator<(const Vector3& _rhs)
{
	return (this->m_value.at(Maths::coord::x) < _rhs.m_value.at(Maths::coord::x) && this->m_value.at(Maths::coord::y) < _rhs.m_value.at(Maths::coord::y) && this->m_value.at(Maths::coord::z) < _rhs.m_value.at(Maths::coord::z));
}

bool Vector3::operator>=(const Vector3& _rhs)
{
	return (this->m_value.at(Maths::coord::x) >= _rhs.m_value.at(Maths::coord::x) && this->m_value.at(Maths::coord::y) >= _rhs.m_value.at(Maths::coord::y) && this->m_value.at(Maths::coord::z) >= _rhs.m_value.at(Maths::coord::z));
}

bool Vector3::operator<=(const Vector3& _rhs)
{
	return (this->m_value.at(Maths::coord::x) <= _rhs.m_value.at(Maths::coord::x) && this->m_value.at(Maths::coord::y) <= _rhs.m_value.at(Maths::coord::y) && this->m_value.at(Maths::coord::z) <= _rhs.m_value.at(Maths::coord::z));
}

bool Vector3::operator==(const Vector3& _rhs)
{
	return (this->m_value.at(Maths::coord::x) == _rhs.m_value.at(Maths::coord::x) && this->m_value.at(Maths::coord::y) == _rhs.m_value.at(Maths::coord::y) && this->m_value.at(Maths::coord::z) == _rhs.m_value.at(Maths::coord::z));
}

bool Vector3::operator!=(const Vector3& _rhs)
{
	return (this->m_value.at(Maths::coord::x) != _rhs.m_value.at(Maths::coord::x) && this->m_value.at(Maths::coord::y) != _rhs.m_value.at(Maths::coord::y) && this->m_value.at(Maths::coord::x) != _rhs.m_value.at(Maths::coord::x));
}

Vector3 Vector3::cross(const Vector3& _lhs, const Vector3& _rhs)
{
	float x = (_lhs.m_value.at(Maths::coord::y) * _rhs.m_value.at(Maths::coord::z)) - (_lhs.m_value.at(Maths::coord::z) * _rhs.m_value.at(Maths::coord::y));
	float y = (_lhs.m_value.at(Maths::coord::z) * _rhs.m_value.at(Maths::coord::x)) - (_lhs.m_value.at(Maths::coord::x) * _rhs.m_value.at(Maths::coord::z));
	float z = (_lhs.m_value.at(Maths::coord::x) * _rhs.m_value.at(Maths::coord::y)) - (_lhs.m_value.at(Maths::coord::y) * _rhs.m_value.at(Maths::coord::x));
	return Vector3(x, y, z);
}

float Vector3::dot(const Vector3& _lhs, const Vector3& _rhs)
{
	return (_lhs.m_value.at(Maths::coord::x) * _rhs.m_value.at(Maths::coord::x)) + (_lhs.m_value.at(Maths::coord::y) * _rhs.m_value.at(Maths::coord::y)) + (_lhs.m_value.at(Maths::coord::z) * _rhs.m_value.at(Maths::coord::z));
}

float Vector3::magnitude(const Vector3& _rhs)
{
	return sqrtf((_rhs.m_value.at(Maths::coord::x) * _rhs.m_value.at(Maths::coord::x)) + (_rhs.m_value.at(Maths::coord::y) * _rhs.m_value.at(Maths::coord::y)) + (_rhs.m_value.at(Maths::coord::z) * _rhs.m_value.at(Maths::coord::z)));
}

Vector3 Vector3::normalize(const Vector3& _rhs)
{
	float mag = magnitude(_rhs);

	if (mag < Maths::special::epsilon) return Vector3(0.0f, 0.0f, 0.0f);
	return Vector3(_rhs.m_value.at(Maths::coord::x) / mag, _rhs.m_value.at(Maths::coord::y) / mag, _rhs.m_value.at(Maths::coord::z) / mag);
}

Vector3 Vector3::findMidPoint(Vector3 vec1, Vector3 vec2)
{
	float mid_x = (vec1.getX() + vec2.getX()) / 2.0f;
	float mid_y = (vec1.getY() + vec2.getY()) / 2.0f;
	float mid_z = (vec1.getZ() + vec2.getZ()) / 2.0f;
	return Vector3(mid_x, mid_y, mid_z);
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
