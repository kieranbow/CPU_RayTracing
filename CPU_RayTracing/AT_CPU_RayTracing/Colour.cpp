#include <algorithm>

#include "Colour.h"

Colour::Colour()
{
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
	a = 1.0f;
}

Colour::Colour(float _red, float _green, float _blue, float _alpha)
{
	this->r = _red;
	this->g = _green;
	this->b = _blue;
	this->a = _alpha;
}

Colour Colour::operator+(const Colour& _rhs)
{
	Colour colour;
	colour.r = this->r + _rhs.r;
	colour.g = this->g + _rhs.g;
	colour.b = this->b + _rhs.b;
	colour.a = this->a + _rhs.a;
	return colour;
}

Colour Colour::operator+=(const Colour& _rhs)
{
	Colour colour;
	colour.r = this->r += _rhs.r;
	colour.g = this->g += _rhs.g;
	colour.b = this->b += _rhs.b;
	colour.a = this->a += _rhs.a;
	return colour;
}

Colour Colour::operator-(const Colour& _rhs)
{
	Colour colour;
	colour.r = this->r - _rhs.r;
	colour.g = this->g - _rhs.g;
	colour.b = this->b - _rhs.b;
	colour.a = this->a - _rhs.a;
	return colour;
}

Colour Colour::operator-=(const Colour& _rhs)
{
	Colour colour;
	colour.r = this->r -= _rhs.r;
	colour.g = this->g -= _rhs.g;
	colour.b = this->b -= _rhs.b;
	colour.a = this->a -= _rhs.a;
	return colour;
}

Colour Colour::operator/(const Colour& _rhs)
{
	Colour colour;
	colour.r = this->r / _rhs.r;
	colour.g = this->g / _rhs.g;
	colour.b = this->b / _rhs.b;
	colour.a = this->a / _rhs.a;
	return colour;
}

Colour Colour::operator/=(const Colour& _rhs)
{
	Colour colour;
	colour.r = this->r /= _rhs.r;
	colour.g = this->g /= _rhs.g;
	colour.b = this->b /= _rhs.b;
	colour.a = this->a /= _rhs.a;
	return colour;
}

Colour Colour::operator*(const Colour& _rhs)
{
	Colour colour;
	colour.r = this->r * _rhs.r;
	colour.g = this->g * _rhs.g;
	colour.b = this->b * _rhs.b;
	colour.a = this->a * _rhs.a;
	return colour;
}

Colour Colour::operator*=(const Colour& _rhs)
{
	Colour colour;
	colour.r = this->r *= _rhs.r;
	colour.g = this->g *= _rhs.g;
	colour.b = this->b *= _rhs.b;
	colour.a = this->a *= _rhs.a;
	return colour;
}

void Colour::setColour(float _red, float _green, float _blue, float _alpha)
{
	this->r = _red;
	this->g = _green;
	this->b = _blue;
	this->a = _alpha;
}
