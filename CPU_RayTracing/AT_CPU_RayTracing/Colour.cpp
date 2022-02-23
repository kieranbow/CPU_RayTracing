#include <algorithm>

#include "Vector3.h"
#include "Colour.h"

Colour::Colour()
{
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
}

Colour::Colour(float _red, float _green, float _blue)
{
	r = _red;
	g = _green;
	b = _blue;
}

Colour::Colour(Vector3& _rhs)
{
	r = _rhs.getX();
	g = _rhs.getY();
	b = _rhs.getZ();
}

Colour& Colour::operator=(const Colour& _rhs)
{
	this->r = _rhs.r;
	this->g = _rhs.g;
	this->b = _rhs.b;
	return *this;
}

Colour& Colour::operator=(const Vector3& _rhs)
{
	this->r = _rhs.getX();
	this->g = _rhs.getY();
	this->b = _rhs.getZ();
	return *this;
}

Colour Colour::operator+(const Colour& _rhs)
{
	Colour colour;
	colour.r = this->r + _rhs.r;
	colour.g = this->g + _rhs.g;
	colour.b = this->b + _rhs.b;
	return colour;
}

Colour Colour::operator+=(const Colour& _rhs)
{
	Colour colour;
	colour.r = this->r += _rhs.r;
	colour.g = this->g += _rhs.g;
	colour.b = this->b += _rhs.b;
	return colour;
}

Colour Colour::operator-(const Colour& _rhs)
{
	Colour colour;
	colour.r = this->r - _rhs.r;
	colour.g = this->g - _rhs.g;
	colour.b = this->b - _rhs.b;
	return colour;
}

Colour Colour::operator-=(const Colour& _rhs)
{
	Colour colour;
	colour.r = this->r -= _rhs.r;
	colour.g = this->g -= _rhs.g;
	colour.b = this->b -= _rhs.b;
	return colour;
}

Colour Colour::operator/(const Colour& _rhs)
{
	Colour colour;
	colour.r = this->r / _rhs.r;
	colour.g = this->g / _rhs.g;
	colour.b = this->b / _rhs.b;
	return colour;
}

Colour Colour::operator/=(const Colour& _rhs)
{
	Colour colour;
	colour.r = this->r /= _rhs.r;
	colour.g = this->g /= _rhs.g;
	colour.b = this->b /= _rhs.b;
	return colour;
}

Colour Colour::operator*(const Colour& _rhs)
{
	Colour colour;
	colour.r = this->r * _rhs.r;
	colour.g = this->g * _rhs.g;
	colour.b = this->b * _rhs.b;
	return colour;
}

Colour Colour::operator*=(const Colour& _rhs)
{
	Colour colour;
	colour.r = this->r *= _rhs.r;
	colour.g = this->g *= _rhs.g;
	colour.b = this->b *= _rhs.b;
	return colour;
}
