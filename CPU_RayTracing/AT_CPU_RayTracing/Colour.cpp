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
	this->r = _red;
	this->g = _green;
	this->b = _blue;
}

Colour Colour::operator=(const Colour& _rhs)
{
	Colour colour;
	colour.r = _rhs.r;
	colour.g = _rhs.g;
	colour.b = _rhs.b;
	return colour;
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

void Colour::setColour(float _red, float _green, float _blue)
{
	this->r = _red;
	this->g = _green;
	this->b = _blue;
}

void Colour::setColour(Colour colour)
{
	this->r = colour.r;
	this->g = colour.g;
	this->b = colour.b;
}
