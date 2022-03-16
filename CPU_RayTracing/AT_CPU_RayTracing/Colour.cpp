#include <algorithm>

#include "Vector3.h"
#include "Colour.h"

Colour::Colour()
{
	m_colour.at(0) = 0.0f;
	m_colour.at(1) = 0.0f;
	m_colour.at(2) = 0.0f;
}

Colour::Colour(float _red, float _green, float _blue)
{
	m_colour.at(0) = _red;
	m_colour.at(1) = _green;
	m_colour.at(2) = _blue;
}

Colour::Colour(Vector3& _rhs)
{
	m_colour.at(0) = _rhs.getX();
	m_colour.at(1) = _rhs.getY();
	m_colour.at(2) = _rhs.getZ();
}

Colour& Colour::operator=(const Colour& _rhs)
{
	this->m_colour.at(0) = _rhs.m_colour.at(0);
	this->m_colour.at(1) = _rhs.m_colour.at(1);
	this->m_colour.at(2) = _rhs.m_colour.at(2);
	return *this;
}

Colour& Colour::operator=(const Vector3& _rhs)
{
	this->m_colour.at(0) = _rhs.getX();
	this->m_colour.at(1) = _rhs.getY();
	this->m_colour.at(2) = _rhs.getZ();
	return *this;
}

Colour Colour::operator+=(const Vector3& _rhs)
{
	this->m_colour.at(0) += _rhs.getX();
	this->m_colour.at(1) += _rhs.getY();
	this->m_colour.at(2) += _rhs.getZ();
	return *this;
}

Colour Colour::operator-=(const Vector3& _rhs)
{
	this->m_colour.at(0) -= _rhs.getX();
	this->m_colour.at(1) -= _rhs.getY();
	this->m_colour.at(2) -= _rhs.getZ();
	return *this;
}

Colour Colour::operator/=(const Vector3& _rhs)
{
	this->m_colour.at(0) /= _rhs.getX();
	this->m_colour.at(1) /= _rhs.getY();
	this->m_colour.at(2) /= _rhs.getZ();
	return *this;
}

Colour Colour::operator*=(const Vector3& _rhs)
{
	this->m_colour.at(0) *= _rhs.getX();
	this->m_colour.at(1) *= _rhs.getY();
	this->m_colour.at(2) *= _rhs.getZ();
	return *this;
}

Colour Colour::operator+(const Colour& _rhs)
{
	Colour colour;
	colour.m_colour.at(0) = this->m_colour.at(0) + _rhs.m_colour.at(0);
	colour.m_colour.at(1) = this->m_colour.at(1) + _rhs.m_colour.at(1);
	colour.m_colour.at(2) = this->m_colour.at(2) + _rhs.m_colour.at(2);
	return colour;
}

Colour Colour::operator+=(const Colour& _rhs)
{
	Colour colour;
	colour.m_colour.at(0) = this->m_colour.at(0) += _rhs.m_colour.at(0);
	colour.m_colour.at(1) = this->m_colour.at(1) += _rhs.m_colour.at(1);
	colour.m_colour.at(2) = this->m_colour.at(2) += _rhs.m_colour.at(2);
	return colour;
}

Colour Colour::operator-(const Colour& _rhs)
{
	Colour colour;
	colour.m_colour.at(0) = this->m_colour.at(0) - _rhs.m_colour.at(0);
	colour.m_colour.at(1) = this->m_colour.at(1) - _rhs.m_colour.at(1);
	colour.m_colour.at(2) = this->m_colour.at(2) - _rhs.m_colour.at(2);
	return colour;
}

Colour Colour::operator-=(const Colour& _rhs)
{
	Colour colour;
	colour.m_colour.at(0) = this->m_colour.at(0) -= _rhs.m_colour.at(0);
	colour.m_colour.at(1) = this->m_colour.at(1) -= _rhs.m_colour.at(1);
	colour.m_colour.at(2) = this->m_colour.at(2) -= _rhs.m_colour.at(2);
	return colour;
}

Colour Colour::operator/(const Colour& _rhs)
{
	Colour colour;
	colour.m_colour.at(0) = this->m_colour.at(0) / _rhs.m_colour.at(0);
	colour.m_colour.at(1) = this->m_colour.at(1) / _rhs.m_colour.at(1);
	colour.m_colour.at(2) = this->m_colour.at(2) / _rhs.m_colour.at(2);
	return colour;
}

Colour Colour::operator/=(const Colour& _rhs)
{
	Colour colour;
	colour.m_colour.at(0) = this->m_colour.at(0) /= _rhs.m_colour.at(0);
	colour.m_colour.at(1) = this->m_colour.at(1) /= _rhs.m_colour.at(1);
	colour.m_colour.at(2) = this->m_colour.at(2) /= _rhs.m_colour.at(2);
	return colour;
}

Colour Colour::operator*(const Colour& _rhs)
{
	Colour colour;
	colour.m_colour.at(0) = this->m_colour.at(0) * _rhs.m_colour.at(0);
	colour.m_colour.at(1) = this->m_colour.at(1) * _rhs.m_colour.at(1);
	colour.m_colour.at(2) = this->m_colour.at(2) * _rhs.m_colour.at(2);
	return colour;
}

Colour Colour::operator+(const Vector3& _rhs)
{
	Colour colour;
	colour.m_colour.at(0) = this->m_colour.at(0) + _rhs.getX();
	colour.m_colour.at(1) = this->m_colour.at(1) + _rhs.getY();
	colour.m_colour.at(2) = this->m_colour.at(2) + _rhs.getZ();
	return colour;
}

Colour Colour::operator-(const Vector3& _rhs)
{
	Colour colour;
	colour.m_colour.at(0) = this->m_colour.at(0) - _rhs.getX();
	colour.m_colour.at(1) = this->m_colour.at(1) - _rhs.getY();
	colour.m_colour.at(2) = this->m_colour.at(2) - _rhs.getZ();
	return colour;
}

Colour Colour::operator/(const Vector3& _rhs)
{
	Colour colour;
	colour.m_colour.at(0) = this->m_colour.at(0) / _rhs.getX();
	colour.m_colour.at(1) = this->m_colour.at(1) / _rhs.getY();
	colour.m_colour.at(2) = this->m_colour.at(2) / _rhs.getZ();
	return colour;
}

Colour Colour::operator*(const Vector3& _rhs)
{
	Colour colour;
	colour.m_colour.at(0) = this->m_colour.at(0) * _rhs.getX();
	colour.m_colour.at(1) = this->m_colour.at(1) * _rhs.getY();
	colour.m_colour.at(2) = this->m_colour.at(2) * _rhs.getZ();
	return colour;
}

bool Colour::operator>(const Colour& _rhs)
{
	return (this->m_colour.at(0) > _rhs.m_colour.at(0) || this->m_colour.at(1) > _rhs.m_colour.at(1) || this->m_colour.at(2) > _rhs.m_colour.at(2));
}

bool Colour::operator<(const Colour& _rhs)
{
	return (this->m_colour.at(0) < _rhs.m_colour.at(0) || this->m_colour.at(1) < _rhs.m_colour.at(1) || this->m_colour.at(2) < _rhs.m_colour.at(2));
}

bool Colour::operator>=(const Colour& _rhs)
{
	return (this->m_colour.at(0) >= _rhs.m_colour.at(0) || this->m_colour.at(1) >= _rhs.m_colour.at(1) || this->m_colour.at(2) >= _rhs.m_colour.at(2));
}

bool Colour::operator<=(const Colour& _rhs)
{
	return (this->m_colour.at(0) <= _rhs.m_colour.at(0) || this->m_colour.at(1) <= _rhs.m_colour.at(1) || this->m_colour.at(2) <= _rhs.m_colour.at(2));
}

bool Colour::operator==(const Colour& _rhs)
{
	return (this->m_colour.at(0) == _rhs.m_colour.at(0) || this->m_colour.at(1) ==_rhs.m_colour.at(1) || this->m_colour.at(2) == _rhs.m_colour.at(2));
}

bool Colour::operator!=(const Colour& _rhs)
{
	return (this->m_colour.at(0) != _rhs.m_colour.at(0) || this->m_colour.at(1) != _rhs.m_colour.at(1) || this->m_colour.at(2) != _rhs.m_colour.at(2));
}

Colour Colour::operator*=(const Colour& _rhs)
{
	Colour colour;
	colour.m_colour.at(0) = this->m_colour.at(0) *= _rhs.m_colour.at(0);
	colour.m_colour.at(1) = this->m_colour.at(1) *= _rhs.m_colour.at(1);
	colour.m_colour.at(2) = this->m_colour.at(2) *= _rhs.m_colour.at(2);
	return colour;
}

Colour operator+(const float& _lhs, const Colour& _rhs)
{
	return Colour(_rhs.getRed() + _lhs, _rhs.getGreen() + _lhs, _rhs.getBlue() + _lhs);
}

Colour operator-(const float& _lhs, const Colour& _rhs)
{
	return Colour(_rhs.getRed() - _lhs, _rhs.getGreen() - _lhs, _rhs.getBlue() - _lhs);
}

Colour operator*(const float& _lhs, const Colour& _rhs)
{
	return Colour(_rhs.getRed() * _lhs, _rhs.getGreen() * _lhs, _rhs.getBlue() * _lhs);
}

Colour operator/(const float& _lhs, const Colour& _rhs)
{
	return Colour(_rhs.getRed() / _lhs, _rhs.getGreen() / _lhs, _rhs.getBlue() / _lhs);
}

Colour operator/(const Colour& _lhs, const float& _rhs)
{
	return Colour(_lhs.getRed() / _rhs, _lhs.getGreen() / _rhs, _lhs.getBlue() / _rhs);
}

Colour operator*(const Colour& _lhs, const float& _rhs)
{
	return Colour(_lhs.getRed() * _rhs, _lhs.getGreen() * _rhs, _lhs.getBlue() * _rhs);
}
