#include <algorithm>

#include "Vector3.h"
#include "Colour.h"

Colour::Colour()
{
	colour[0] = 0.0f;
	colour[1] = 0.0f;
	colour[2] = 0.0f;
}

Colour::Colour(float _red, float _green, float _blue)
{
	colour[0] = _red;
	colour[1] = _green;
	colour[2] = _blue;
}

Colour::Colour(Vector3& _rhs)
{
	colour[0] = _rhs.getX();
	colour[1] = _rhs.getY();
	colour[2] = _rhs.getZ();
}

Colour& Colour::operator=(const Colour& _rhs)
{
	this->colour[0] = _rhs.colour[0];
	this->colour[1] = _rhs.colour[1];
	this->colour[2] = _rhs.colour[2];
	return *this;
}

Colour& Colour::operator=(const Vector3& _rhs)
{
	this->colour[0] = _rhs.getX();
	this->colour[1] = _rhs.getY();
	this->colour[2] = _rhs.getZ();
	return *this;
}

Colour Colour::operator+=(const Vector3& _rhs)
{
	this->colour[0] += _rhs.getX();
	this->colour[1] += _rhs.getY();
	this->colour[2] += _rhs.getZ();
	return *this;
}

Colour Colour::operator-=(const Vector3& _rhs)
{
	this->colour[0] -= _rhs.getX();
	this->colour[1] -= _rhs.getY();
	this->colour[2] -= _rhs.getZ();
	return *this;
}

Colour Colour::operator/=(const Vector3& _rhs)
{
	this->colour[0] /= _rhs.getX();
	this->colour[1] /= _rhs.getY();
	this->colour[2] /= _rhs.getZ();
	return *this;
}

Colour Colour::operator*=(const Vector3& _rhs)
{
	this->colour[0] *= _rhs.getX();
	this->colour[1] *= _rhs.getY();
	this->colour[2] *= _rhs.getZ();
	return *this;
}

Colour& Colour::operator=(const float& _rhs)
{
	Colour colour;
	colour.colour[0] = _rhs;
	colour.colour[1] = _rhs;
	colour.colour[2] = _rhs;
	return colour;
}

Colour Colour::operator+=(const float& _rhs)
{
	Colour colour;
	colour.colour[0] += _rhs;
	colour.colour[1] += _rhs;
	colour.colour[2] += _rhs;
	return colour;
}

Colour Colour::operator-=(const float& _rhs)
{
	Colour colour;
	colour.colour[0] -= _rhs;
	colour.colour[1] -= _rhs;
	colour.colour[2] -= _rhs;
	return colour;
}

Colour Colour::operator/=(const float& _rhs)
{
	Colour colour;
	colour.colour[0] /= _rhs;
	colour.colour[1] /= _rhs;
	colour.colour[2] /= _rhs;
	return colour;
}

Colour Colour::operator*=(const float& _rhs)
{
	Colour colour;
	colour.colour[0] *= _rhs;
	colour.colour[1] *= _rhs;
	colour.colour[2] *= _rhs;
	return colour;
}

Colour Colour::operator+(const Colour& _rhs)
{
	Colour colour;
	colour.colour[0] = this->colour[0] + _rhs.colour[0];
	colour.colour[1] = this->colour[1] + _rhs.colour[1];
	colour.colour[2] = this->colour[2] + _rhs.colour[2];
	return colour;
}

Colour Colour::operator+=(const Colour& _rhs)
{
	Colour colour;
	colour.colour[0] = this->colour[0] += _rhs.colour[0];
	colour.colour[1] = this->colour[1] += _rhs.colour[1];
	colour.colour[2] = this->colour[2] += _rhs.colour[2];
	return colour;
}

Colour Colour::operator-(const Colour& _rhs)
{
	Colour colour;
	colour.colour[0] = this->colour[0] - _rhs.colour[0];
	colour.colour[1] = this->colour[1] - _rhs.colour[1];
	colour.colour[2] = this->colour[2] - _rhs.colour[2];
	return colour;
}

Colour Colour::operator-=(const Colour& _rhs)
{
	Colour colour;
	colour.colour[0] = this->colour[0] -= _rhs.colour[0];
	colour.colour[1] = this->colour[1] -= _rhs.colour[1];
	colour.colour[2] = this->colour[2] -= _rhs.colour[2];
	return colour;
}

Colour Colour::operator/(const Colour& _rhs)
{
	Colour colour;
	colour.colour[0] = this->colour[0] / _rhs.colour[0];
	colour.colour[1] = this->colour[1] / _rhs.colour[1];
	colour.colour[2] = this->colour[2] / _rhs.colour[2];
	return colour;
}

Colour Colour::operator/=(const Colour& _rhs)
{
	Colour colour;
	colour.colour[0] = this->colour[0] /= _rhs.colour[0];
	colour.colour[1] = this->colour[1] /= _rhs.colour[1];
	colour.colour[2] = this->colour[2] /= _rhs.colour[2];
	return colour;
}

Colour Colour::operator*(const Colour& _rhs)
{
	Colour colour;
	colour.colour[0] = this->colour[0] * _rhs.colour[0];
	colour.colour[1] = this->colour[1] * _rhs.colour[1];
	colour.colour[2] = this->colour[2] * _rhs.colour[2];
	return colour;
}

Colour Colour::operator+(const float& _rhs)
{
	return Colour(this->colour[0] + _rhs, this->colour[1] + _rhs, this->colour[2] + _rhs);
}

Colour Colour::operator-(const float& _rhs)
{
	return Colour(this->colour[0] - _rhs, this->colour[1] - _rhs, this->colour[2] - _rhs);
}

Colour Colour::operator/(const float& _rhs)
{
	return Colour(this->colour[0] / _rhs, this->colour[1] / _rhs, this->colour[2] / _rhs);
}

Colour Colour::operator*(const float& _rhs)
{
	return Colour(this->colour[0] * _rhs, this->colour[1] * _rhs, this->colour[2] * _rhs);
}

bool Colour::operator>(const Colour& _rhs)
{
	return (this->colour[0] > _rhs.colour[0] || this->colour[1] > _rhs.colour[1] || this->colour[2] > _rhs.colour[2]);
}

bool Colour::operator<(const Colour& _rhs)
{
	return (this->colour[0] < _rhs.colour[0] || this->colour[1] < _rhs.colour[1] || this->colour[2] < _rhs.colour[2]);
}

bool Colour::operator>=(const Colour& _rhs)
{
	return (this->colour[0] >= _rhs.colour[0] || this->colour[1] >= _rhs.colour[1] || this->colour[2] >= _rhs.colour[2]);
}

bool Colour::operator<=(const Colour& _rhs)
{
	return (this->colour[0] <= _rhs.colour[0] || this->colour[1] <= _rhs.colour[1] || this->colour[2] <= _rhs.colour[2]);
}

bool Colour::operator==(const Colour& _rhs)
{
	return (this->colour[0] == _rhs.colour[0] || this->colour[1] ==_rhs.colour[1] || this->colour[2] == _rhs.colour[2]);
}

bool Colour::operator!=(const Colour& _rhs)
{
	return (this->colour[0] != _rhs.colour[0] || this->colour[1] != _rhs.colour[1] || this->colour[2] != _rhs.colour[2]);
}

Colour Colour::operator*=(const Colour& _rhs)
{
	Colour colour;
	colour.colour[0] = this->colour[0] *= _rhs.colour[0];
	colour.colour[1] = this->colour[1] *= _rhs.colour[1];
	colour.colour[2] = this->colour[2] *= _rhs.colour[2];
	return colour;
}

Colour operator+(const float& _lhs, const Colour& _rhs)
{
	return Colour(_rhs.colour[0] + _lhs, _rhs.colour[1] + _lhs, _rhs.colour[2] + _lhs);
}

Colour operator-(const float& _lhs, const Colour& _rhs)
{
	return Colour(_rhs.colour[0] - _lhs, _rhs.colour[1] - _lhs, _rhs.colour[2] - _lhs);
}

Colour operator*(const float& _lhs, const Colour& _rhs)
{
	return Colour(_rhs.colour[0] * _lhs, _rhs.colour[1] * _lhs, _rhs.colour[2] * _lhs);
}

Colour operator/(const float& _lhs, const Colour& _rhs)
{
	return Colour(_rhs.colour[0] / _lhs, _rhs.colour[1] / _lhs, _rhs.colour[2] / _lhs);
}

Colour operator/(const Colour& _lhs, const float& _rhs)
{
	return Colour(_lhs.colour[0] / _rhs, _lhs.colour[1] / _rhs, _lhs.colour[2] / _rhs);
}

Colour operator*(const Colour& _lhs, const float& _rhs)
{
	return Colour(_lhs.colour[0] * _rhs, _lhs.colour[1] * _rhs, _lhs.colour[2] * _rhs);
}

Colour operator/=(Colour& _lhs, const float& _rhs)
{
	Colour colour;
	colour.colour[0] = _lhs.colour[0] /= _rhs;
	colour.colour[1] = _lhs.colour[1] /= _rhs;
	colour.colour[2] = _lhs.colour[2] /= _rhs;
	return colour;
}
