#include <algorithm>

#include "Vector3.h"
#include "Colour.h"

Colour::Colour()
{
	colour.at(0) = 0.0f;
	colour.at(1) = 0.0f;
	colour.at(2) = 0.0f;
}

Colour::Colour(float _red, float _green, float _blue)
{
	colour.at(0) = _red;
	colour.at(1) = _green;
	colour.at(2) = _blue;
}

Colour::Colour(Vector3& _rhs)
{
	colour.at(0) = _rhs.getX();
	colour.at(1) = _rhs.getY();
	colour.at(2) = _rhs.getZ();
}

Colour& Colour::operator=(const Colour& _rhs)
{
	this->colour.at(0) = _rhs.colour.at(0);
	this->colour.at(1) = _rhs.colour.at(1);
	this->colour.at(2) = _rhs.colour.at(2);
	return *this;
}

Colour& Colour::operator=(const Vector3& _rhs)
{
	this->colour.at(0) = _rhs.getX();
	this->colour.at(1) = _rhs.getY();
	this->colour.at(2) = _rhs.getZ();
	return *this;
}

Colour Colour::operator+=(const Vector3& _rhs)
{
	this->colour.at(0) += _rhs.getX();
	this->colour.at(1) += _rhs.getY();
	this->colour.at(2) += _rhs.getZ();
	return *this;
}

Colour Colour::operator-=(const Vector3& _rhs)
{
	this->colour.at(0) -= _rhs.getX();
	this->colour.at(1) -= _rhs.getY();
	this->colour.at(2) -= _rhs.getZ();
	return *this;
}

Colour Colour::operator/=(const Vector3& _rhs)
{
	this->colour.at(0) /= _rhs.getX();
	this->colour.at(1) /= _rhs.getY();
	this->colour.at(2) /= _rhs.getZ();
	return *this;
}

Colour Colour::operator*=(const Vector3& _rhs)
{
	this->colour.at(0) *= _rhs.getX();
	this->colour.at(1) *= _rhs.getY();
	this->colour.at(2) *= _rhs.getZ();
	return *this;
}

Colour Colour::operator+(const Colour& _rhs)
{
	Colour colour;
	colour.colour.at(0) = this->colour.at(0) + _rhs.colour.at(0);
	colour.colour.at(1) = this->colour.at(1) + _rhs.colour.at(1);
	colour.colour.at(2) = this->colour.at(2) + _rhs.colour.at(2);
	return colour;
}

Colour Colour::operator+=(const Colour& _rhs)
{
	Colour colour;
	colour.colour.at(0) = this->colour.at(0) += _rhs.colour.at(0);
	colour.colour.at(1) = this->colour.at(1) += _rhs.colour.at(1);
	colour.colour.at(2) = this->colour.at(2) += _rhs.colour.at(2);
	return colour;
}

Colour Colour::operator-(const Colour& _rhs)
{
	Colour colour;
	colour.colour.at(0) = this->colour.at(0) - _rhs.colour.at(0);
	colour.colour.at(1) = this->colour.at(1) - _rhs.colour.at(1);
	colour.colour.at(2) = this->colour.at(2) - _rhs.colour.at(2);
	return colour;
}

Colour Colour::operator-=(const Colour& _rhs)
{
	Colour colour;
	colour.colour.at(0) = this->colour.at(0) -= _rhs.colour.at(0);
	colour.colour.at(1) = this->colour.at(1) -= _rhs.colour.at(1);
	colour.colour.at(2) = this->colour.at(2) -= _rhs.colour.at(2);
	return colour;
}

Colour Colour::operator/(const Colour& _rhs)
{
	Colour colour;
	colour.colour.at(0) = this->colour.at(0) / _rhs.colour.at(0);
	colour.colour.at(1) = this->colour.at(1) / _rhs.colour.at(1);
	colour.colour.at(2) = this->colour.at(2) / _rhs.colour.at(2);
	return colour;
}

Colour Colour::operator/=(const Colour& _rhs)
{
	Colour colour;
	colour.colour.at(0) = this->colour.at(0) /= _rhs.colour.at(0);
	colour.colour.at(1) = this->colour.at(1) /= _rhs.colour.at(1);
	colour.colour.at(2) = this->colour.at(2) /= _rhs.colour.at(2);
	return colour;
}

Colour Colour::operator*(const Colour& _rhs)
{
	Colour colour;
	colour.colour.at(0) = this->colour.at(0) * _rhs.colour.at(0);
	colour.colour.at(1) = this->colour.at(1) * _rhs.colour.at(1);
	colour.colour.at(2) = this->colour.at(2) * _rhs.colour.at(2);
	return colour;
}

Colour Colour::operator+(const Vector3& _rhs)
{
	Colour colour;
	colour.colour.at(0) = this->colour.at(0) + _rhs.getX();
	colour.colour.at(1) = this->colour.at(1) + _rhs.getY();
	colour.colour.at(2) = this->colour.at(2) + _rhs.getZ();
	return colour;
}

Colour Colour::operator-(const Vector3& _rhs)
{
	Colour colour;
	colour.colour.at(0) = this->colour.at(0) - _rhs.getX();
	colour.colour.at(1) = this->colour.at(1) - _rhs.getY();
	colour.colour.at(2) = this->colour.at(2) - _rhs.getZ();
	return colour;
}

Colour Colour::operator/(const Vector3& _rhs)
{
	Colour colour;
	colour.colour.at(0) = this->colour.at(0) / _rhs.getX();
	colour.colour.at(1) = this->colour.at(1) / _rhs.getY();
	colour.colour.at(2) = this->colour.at(2) / _rhs.getZ();
	return colour;
}

Colour Colour::operator*(const Vector3& _rhs)
{
	Colour colour;
	colour.colour.at(0) = this->colour.at(0) * _rhs.getX();
	colour.colour.at(1) = this->colour.at(1) * _rhs.getY();
	colour.colour.at(2) = this->colour.at(2) * _rhs.getZ();
	return colour;
}

bool Colour::operator>(const Colour& _rhs)
{
	return (this->colour.at(0) > _rhs.colour.at(0) || this->colour.at(1) > _rhs.colour.at(1) || this->colour.at(2) > _rhs.colour.at(2));
}

bool Colour::operator<(const Colour& _rhs)
{
	return (this->colour.at(0) < _rhs.colour.at(0) || this->colour.at(1) < _rhs.colour.at(1) || this->colour.at(2) < _rhs.colour.at(2));
}

bool Colour::operator>=(const Colour& _rhs)
{
	return (this->colour.at(0) >= _rhs.colour.at(0) || this->colour.at(1) >= _rhs.colour.at(1) || this->colour.at(2) >= _rhs.colour.at(2));
}

bool Colour::operator<=(const Colour& _rhs)
{
	return (this->colour.at(0) <= _rhs.colour.at(0) || this->colour.at(1) <= _rhs.colour.at(1) || this->colour.at(2) <= _rhs.colour.at(2));
}

bool Colour::operator==(const Colour& _rhs)
{
	return (this->colour.at(0) == _rhs.colour.at(0) || this->colour.at(1) ==_rhs.colour.at(1) || this->colour.at(2) == _rhs.colour.at(2));
}

bool Colour::operator!=(const Colour& _rhs)
{
	return (this->colour.at(0) != _rhs.colour.at(0) || this->colour.at(1) != _rhs.colour.at(1) || this->colour.at(2) != _rhs.colour.at(2));
}

Colour Colour::operator*=(const Colour& _rhs)
{
	Colour colour;
	colour.colour.at(0) = this->colour.at(0) *= _rhs.colour.at(0);
	colour.colour.at(1) = this->colour.at(1) *= _rhs.colour.at(1);
	colour.colour.at(2) = this->colour.at(2) *= _rhs.colour.at(2);
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
