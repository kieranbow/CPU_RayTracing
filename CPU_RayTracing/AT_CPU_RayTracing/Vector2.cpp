#include "Vector2.h"

Vector2::Vector2()
{
	m_value.at(Maths::coord::x) = 0.0f;
	m_value.at(Maths::coord::y) = 0.0f;
}

Vector2& Vector2::operator=(const Vector2& _rhs)
{
	this->m_value.at(Maths::coord::x) = _rhs.m_value.at(Maths::coord::x);
	this->m_value.at(Maths::coord::y) = _rhs.m_value.at(Maths::coord::y);
	return *this;
}

Vector2 Vector2::operator+(const Vector2& _rhs)
{
	Vector2 vector;
	vector.m_value.at(Maths::coord::x) = this->m_value.at(Maths::coord::x) + _rhs.m_value.at(Maths::coord::x);
	vector.m_value.at(Maths::coord::y) = this->m_value.at(Maths::coord::y) + _rhs.m_value.at(Maths::coord::y);
	return vector;
}

Vector2 Vector2::operator+(const float& _rhs)
{
	Vector2 vector;
	vector.m_value.at(Maths::coord::x) = this->m_value.at(Maths::coord::x) + _rhs;
	vector.m_value.at(Maths::coord::y) = this->m_value.at(Maths::coord::x) + _rhs;
	return vector;
}

Vector2 Vector2::operator+=(const Vector2& _rhs)
{
	this->m_value.at(Maths::coord::x) += _rhs.m_value.at(Maths::coord::x);
	this->m_value.at(Maths::coord::y) += _rhs.m_value.at(Maths::coord::y);
	return *this;
}

Vector2 Vector2::operator-(const Vector2& _rhs)
{
	Vector2 vector;
	vector.m_value.at(Maths::coord::x) = this->m_value.at(Maths::coord::x) - _rhs.m_value.at(Maths::coord::x);
	vector.m_value.at(Maths::coord::y) = this->m_value.at(Maths::coord::y) - _rhs.m_value.at(Maths::coord::y);
	return vector;
}

Vector2 Vector2::operator-=(const Vector2& _rhs)
{
	this->m_value.at(Maths::coord::x) -= _rhs.m_value.at(Maths::coord::x);
	this->m_value.at(Maths::coord::y) -= _rhs.m_value.at(Maths::coord::y);
	return *this;
}

Vector2 Vector2::operator*(const Vector2& _rhs)
{
	Vector2 vector;
	vector.m_value.at(Maths::coord::x) = this->m_value.at(Maths::coord::x) * _rhs.m_value.at(Maths::coord::x);
	vector.m_value.at(Maths::coord::y) = this->m_value.at(Maths::coord::y) * _rhs.m_value.at(Maths::coord::y);
	return vector;
}

Vector2 Vector2::operator*=(const Vector2& _rhs)
{
	this->m_value.at(Maths::coord::x) *= _rhs.m_value.at(Maths::coord::x);
	this->m_value.at(Maths::coord::y) *= _rhs.m_value.at(Maths::coord::y);
	return *this;
}

Vector2 Vector2::operator/(const Vector2& _rhs)
{
	Vector2 vector;
	vector.m_value.at(Maths::coord::x) = this->m_value.at(Maths::coord::x) / _rhs.m_value.at(Maths::coord::x);
	vector.m_value.at(Maths::coord::y) = this->m_value.at(Maths::coord::y) / _rhs.m_value.at(Maths::coord::y);
	return vector;
}

Vector2 Vector2::operator/(const float& _rhs)
{
	Vector2 vector;
	vector.m_value.at(Maths::coord::x) = this->m_value.at(Maths::coord::x) / _rhs;
	vector.m_value.at(Maths::coord::y) = this->m_value.at(Maths::coord::y) / _rhs;
	return vector;
}

bool Vector2::operator>(const Vector2& _rhs)
{
	return (this->m_value.at(Maths::coord::x) > _rhs.m_value.at(Maths::coord::x) || this->m_value.at(Maths::coord::y) > _rhs.m_value.at(Maths::coord::y));
}

bool Vector2::operator<(const Vector2& _rhs)
{
	return (this->m_value.at(Maths::coord::x) < _rhs.m_value.at(Maths::coord::x) || this->m_value.at(Maths::coord::y) < _rhs.m_value.at(Maths::coord::y));
}

bool Vector2::operator>=(const Vector2& _rhs)
{
	return (this->m_value.at(Maths::coord::x) >= _rhs.m_value.at(Maths::coord::x) || this->m_value.at(Maths::coord::y) >= _rhs.m_value.at(Maths::coord::y));
}

bool Vector2::operator<=(const Vector2& _rhs)
{
	return (this->m_value.at(Maths::coord::x) <= _rhs.m_value.at(Maths::coord::x) || this->m_value.at(Maths::coord::y) <= _rhs.m_value.at(Maths::coord::y));
}

bool Vector2::operator==(const Vector2& _rhs)
{
	return (this->m_value.at(Maths::coord::x) == _rhs.m_value.at(Maths::coord::x) || this->m_value.at(Maths::coord::y) == _rhs.m_value.at(Maths::coord::y));
}

bool Vector2::operator!=(const Vector2& _rhs)
{
	return (this->m_value.at(Maths::coord::x) != _rhs.m_value.at(Maths::coord::x) || this->m_value.at(Maths::coord::y) != _rhs.m_value.at(Maths::coord::y));
}

float Vector2::dot(const Vector2& _lhs, const Vector2& _rhs)
{
	return (_lhs.m_value.at(Maths::coord::x) * _rhs.m_value.at(Maths::coord::x)) + (_lhs.m_value.at(Maths::coord::y) * _rhs.m_value.at(Maths::coord::y));
}

float Vector2::magnitude(const Vector2& _rhs)
{
	return sqrtf((_rhs.m_value.at(Maths::coord::x) * _rhs.m_value.at(Maths::coord::x)) + (_rhs.m_value.at(Maths::coord::y) * _rhs.m_value.at(Maths::coord::y)));
}

Vector2 Vector2::normalize(const Vector2& _rhs)
{
	float mag = magnitude(_rhs);

	if (mag < Maths::special::epsilon) return Vector2(0.0f, 0.0f);
	return Vector2(_rhs.m_value.at(Maths::coord::x) / mag, _rhs.m_value.at(Maths::coord::y) / mag);
}

Vector2 Vector2::findMidPoint(Vector2 vec1, Vector2 vec2)
{
	float mid_x = (vec1.getX() + vec2.getX()) / 2.0f;
	float mid_y = (vec1.getY() + vec2.getY()) / 2.0f;
	return Vector2(mid_x, mid_y);
}
