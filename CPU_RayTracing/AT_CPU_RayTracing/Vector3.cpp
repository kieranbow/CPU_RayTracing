#include "Vector3.h"
#include "Random.h"

Vector3::Vector3()
{
	m_value[Maths::coord::x] = 0.0f;
	m_value[Maths::coord::y] = 0.0f;
	m_value[Maths::coord::z] = 0.0f;
}

Vector3& Vector3::operator=(const Vector3& _rhs)
{
	this->m_value[Maths::coord::x] = _rhs.m_value[Maths::coord::x];
	this->m_value[Maths::coord::y] = _rhs.m_value[Maths::coord::y];
	this->m_value[Maths::coord::z] = _rhs.m_value[Maths::coord::z];
	return *this;
}

Vector3 Vector3::operator+(const Vector3& _rhs)
{
	Vector3 vector;
	vector.m_value[Maths::coord::x] = this->m_value[Maths::coord::x] + _rhs.m_value[Maths::coord::x];
	vector.m_value[Maths::coord::y] = this->m_value[Maths::coord::y] + _rhs.m_value[Maths::coord::y];
	vector.m_value[Maths::coord::z] = this->m_value[Maths::coord::z] + _rhs.m_value[Maths::coord::z];
	return vector;
}

Vector3 Vector3::operator+(const float& _rhs)
{
	Vector3 vector;
	vector.m_value[Maths::coord::x] = this->m_value[Maths::coord::x] + _rhs;
	vector.m_value[Maths::coord::y] = this->m_value[Maths::coord::y] + _rhs;
	vector.m_value[Maths::coord::z] = this->m_value[Maths::coord::z] + _rhs;
	return vector;
}

Vector3 Vector3::operator+=(const Vector3& _rhs)
{
	this->m_value[Maths::coord::x] += _rhs.m_value[Maths::coord::x];
	this->m_value[Maths::coord::y] += _rhs.m_value[Maths::coord::y];
	this->m_value[Maths::coord::z] += _rhs.m_value[Maths::coord::z];
	return *this;
}

Vector3 Vector3::operator-(const Vector3& _rhs)
{
	Vector3 vector;
	vector.m_value[Maths::coord::x] = this->m_value[Maths::coord::x] - _rhs.m_value[Maths::coord::x];
	vector.m_value[Maths::coord::y] = this->m_value[Maths::coord::y] - _rhs.m_value[Maths::coord::y];
	vector.m_value[Maths::coord::z] = this->m_value[Maths::coord::z] - _rhs.m_value[Maths::coord::z];
	return vector;
}

Vector3 Vector3::operator-=(const Vector3& _rhs)
{
	this->m_value[Maths::coord::x] -= _rhs.m_value[Maths::coord::x];
	this->m_value[Maths::coord::y] -= _rhs.m_value[Maths::coord::y];
	this->m_value[Maths::coord::z] -= _rhs.m_value[Maths::coord::z];
	return *this;
}

Vector3 Vector3::operator*(const Vector3& _rhs)
{
	Vector3 vector;
	vector.m_value[Maths::coord::x] = this->m_value[Maths::coord::x] * _rhs.m_value[Maths::coord::x];
	vector.m_value[Maths::coord::y] = this->m_value[Maths::coord::y] * _rhs.m_value[Maths::coord::y];
	vector.m_value[Maths::coord::z] = this->m_value[Maths::coord::z] * _rhs.m_value[Maths::coord::z];
	return vector;
}

Vector3 Vector3::operator*=(const Vector3& _rhs)
{
	this->m_value[Maths::coord::x] *= _rhs.m_value[Maths::coord::x];
	this->m_value[Maths::coord::y] *= _rhs.m_value[Maths::coord::y];
	this->m_value[Maths::coord::z] *= _rhs.m_value[Maths::coord::z];
	return *this;
}

Vector3 Vector3::operator/=(const Vector3& _rhs)
{
	this->m_value[Maths::coord::x] /= _rhs.m_value[Maths::coord::x];
	this->m_value[Maths::coord::y] /= _rhs.m_value[Maths::coord::y];
	this->m_value[Maths::coord::z] /= _rhs.m_value[Maths::coord::z];
	return *this;
}

Vector3 Vector3::operator/(const Vector3& _rhs)
{
	Vector3 vector;
	vector.m_value[Maths::coord::x] = this->m_value[Maths::coord::x] / _rhs.m_value[Maths::coord::x];
	vector.m_value[Maths::coord::y] = this->m_value[Maths::coord::y] / _rhs.m_value[Maths::coord::y];
	vector.m_value[Maths::coord::z] = this->m_value[Maths::coord::z] / _rhs.m_value[Maths::coord::z];
	return vector;
}

bool Vector3::operator>(const Vector3& _rhs)
{
	return (this->m_value[Maths::coord::x] > _rhs.m_value[Maths::coord::x] && this->m_value[Maths::coord::y] > _rhs.m_value[Maths::coord::y] && this->m_value[Maths::coord::z] > _rhs.m_value[Maths::coord::z]);
}

bool Vector3::operator<(const Vector3& _rhs)
{
	return (this->m_value[Maths::coord::x] < _rhs.m_value[Maths::coord::x] && this->m_value[Maths::coord::y] < _rhs.m_value[Maths::coord::y] && this->m_value[Maths::coord::z] < _rhs.m_value[Maths::coord::z]);
}

bool Vector3::operator>=(const Vector3& _rhs)
{
	return (this->m_value[Maths::coord::x] >= _rhs.m_value[Maths::coord::x] && this->m_value[Maths::coord::y] >= _rhs.m_value[Maths::coord::y] && this->m_value[Maths::coord::z] >= _rhs.m_value[Maths::coord::z]);
}

bool Vector3::operator<=(const Vector3& _rhs)
{
	return (this->m_value[Maths::coord::x] <= _rhs.m_value[Maths::coord::x] && this->m_value[Maths::coord::y] <= _rhs.m_value[Maths::coord::y] && this->m_value[Maths::coord::z] <= _rhs.m_value[Maths::coord::z]);
}

bool Vector3::operator==(const Vector3& _rhs)
{
	return (this->m_value[Maths::coord::x] == _rhs.m_value[Maths::coord::x] && this->m_value[Maths::coord::y] == _rhs.m_value[Maths::coord::y] && this->m_value[Maths::coord::z] == _rhs.m_value[Maths::coord::z]);
}

bool Vector3::operator!=(const Vector3& _rhs)
{
	return (this->m_value[Maths::coord::x] != _rhs.m_value[Maths::coord::x] && this->m_value[Maths::coord::y] != _rhs.m_value[Maths::coord::y] && this->m_value[Maths::coord::x] != _rhs.m_value[Maths::coord::x]);
}

Vector3 operator+(const float& _lhs, const Vector3& _rhs)
{
	return Vector3(_rhs.m_value[Maths::coord::x] + _lhs, _rhs.m_value[Maths::coord::y] + _lhs, _rhs.m_value[Maths::coord::z] + _lhs);
}

Vector3 operator+(const Vector3& _lhs, const float& _rhs)
{
	return Vector3(_lhs.m_value[Maths::coord::x] + _rhs, _lhs.m_value[Maths::coord::y] + _rhs, _lhs.m_value[Maths::coord::z] + _rhs);
}

Vector3 operator-(const float& _lhs, const Vector3& _rhs)
{
	return Vector3(_rhs.m_value[Maths::coord::x] - _lhs, _rhs.m_value[Maths::coord::y] - _lhs, _rhs.m_value[Maths::coord::z] - _lhs);
}

Vector3 operator-(const Vector3& _lhs, const float& _rhs)
{
	return Vector3(_lhs.m_value[Maths::coord::x] - _rhs, _lhs.m_value[Maths::coord::y] - _rhs, _lhs.m_value[Maths::coord::z] - _rhs);
}

Vector3 operator*(const float& _lhs, const Vector3& _rhs)
{
	return Vector3(_rhs.m_value[Maths::coord::x] * _lhs, _rhs.m_value[Maths::coord::y] * _lhs, _rhs.m_value[Maths::coord::z] * _lhs);
}

Vector3 operator*(const Vector3& _lhs, const float& _rhs)
{
	return Vector3(_lhs.m_value[Maths::coord::x] * _rhs, _lhs.m_value[Maths::coord::y] * _rhs, _lhs.m_value[Maths::coord::z] * _rhs);
}

Vector3 operator/(const float& _lhs, const Vector3& _rhs)
{
	return Vector3(_rhs.m_value[Maths::coord::x] / _lhs, _rhs.m_value[Maths::coord::y] / _lhs, _rhs.m_value[Maths::coord::z] / _lhs);
}

Vector3 operator/(const Vector3& _lhs, const float& _rhs)
{
	return Vector3(_lhs.m_value[Maths::coord::x] / _rhs, _lhs.m_value[Maths::coord::y] / _rhs, _lhs.m_value[Maths::coord::z] / _rhs);
}

Vector3 Vector3::operator-()
{
	Vector3 v;
	v.setX(-this->m_value[Maths::coord::x]);
	v.setY(-this->m_value[Maths::coord::y]);
	v.setZ(-this->m_value[Maths::coord::z]);
	return v;
}

Vector3 Vector3::cross(const Vector3& _lhs, const Vector3& _rhs)
{
	float x = (_lhs.m_value[Maths::coord::y] * _rhs.m_value[Maths::coord::z]) - (_lhs.m_value[Maths::coord::z] * _rhs.m_value[Maths::coord::y]);
	float y = (_lhs.m_value[Maths::coord::z] * _rhs.m_value[Maths::coord::x]) - (_lhs.m_value[Maths::coord::x] * _rhs.m_value[Maths::coord::z]);
	float z = (_lhs.m_value[Maths::coord::x] * _rhs.m_value[Maths::coord::y]) - (_lhs.m_value[Maths::coord::y] * _rhs.m_value[Maths::coord::x]);
	return Vector3(x, y, z);
}

float Vector3::dot(const Vector3& _lhs, const Vector3& _rhs)
{
	return (_lhs.m_value[Maths::coord::x] * _rhs.m_value[Maths::coord::x]) + (_lhs.m_value[Maths::coord::y] * _rhs.m_value[Maths::coord::y]) + (_lhs.m_value[Maths::coord::z] * _rhs.m_value[Maths::coord::z]);
}

float Vector3::magnitude(const Vector3& _rhs)
{
	return std::sqrtf((_rhs.m_value[Maths::coord::x] * _rhs.m_value[Maths::coord::x]) + (_rhs.m_value[Maths::coord::y] * _rhs.m_value[Maths::coord::y]) + (_rhs.m_value[Maths::coord::z] * _rhs.m_value[Maths::coord::z]));
}

Vector3 Vector3::normalize(const Vector3& _rhs)
{
	float mag = magnitude(_rhs);

	if (mag < Maths::special::epsilon) return Vector3(0.0f, 0.0f, 0.0f);
	return Vector3(_rhs.m_value[Maths::coord::x] / mag, _rhs.m_value[Maths::coord::y] / mag, _rhs.m_value[Maths::coord::z] / mag);
}

Vector3 Vector3::findMidPoint(Vector3 vec1, Vector3 vec2)
{
	float mid_x = (vec1.m_value[Maths::coord::x] + vec2.m_value[Maths::coord::x]) / 2.0f;
	float mid_y = (vec1.m_value[Maths::coord::y] + vec2.m_value[Maths::coord::y]) / 2.0f;
	float mid_z = (vec1.m_value[Maths::coord::z] + vec2.m_value[Maths::coord::z]) / 2.0f;
	return Vector3(mid_x, mid_y, mid_z);
}

float Vector3::distance(Vector3 a, Vector3 b)
{
	float x = Maths::sqr(a.m_value[Maths::coord::x] - b.m_value[Maths::coord::x]);
	float y = Maths::sqr(a.m_value[Maths::coord::y] - b.m_value[Maths::coord::y]);
	float z = Maths::sqr(a.m_value[Maths::coord::z] - b.m_value[Maths::coord::z]);
	return std::sqrtf(x + y + z);
}

float Vector3::length(Vector3 a)
{
	return std::sqrtf(Vector3::dot(a, a));
}

Vector3 Vector3::random()
{
	return Vector3(Maths::Random::randomFloat(), Maths::Random::randomFloat(), Maths::Random::randomFloat());
}

Vector3 Vector3::randomInRange(const float min, const float max)
{
	return Vector3(Maths::Random::randomFloatInRange(min, max), Maths::Random::randomFloatInRange(min, max), Maths::Random::randomFloatInRange(min, max));
}

void Vector3::createCoordinateSystem(const Vector3& n, Vector3& nt, Vector3& nb)
{
	if (std::fabs(n.getX()) > std::fabs(n.getY()))
	{
		nt = Vector3(n.m_value[Maths::coord::z], 0.0f, -n.m_value[Maths::coord::x]) / std::sqrtf(n.m_value[Maths::coord::x] * n.m_value[Maths::coord::x] + n.m_value[Maths::coord::z] * n.m_value[Maths::coord::z]);
	}
	else
	{
		nt = Vector3(0.0f, -n.m_value[Maths::coord::z], n.m_value[Maths::coord::y]) / std::sqrtf(n.m_value[Maths::coord::y] * n.m_value[Maths::coord::y] + n.m_value[Maths::coord::z] * n.m_value[Maths::coord::z]);
	}
	nb = Vector3::cross(n, nt);
}

Vector3 Vector3::uniformSampleHemisphere(const float& r1, const float& r2)
{
	float sinTheta = std::sqrtf(1.0f - r1 * r1);
	float phi = 2.0f * Maths::special::pi * r2;
	float x = sinTheta * std::cosf(phi);
	float z = sinTheta * std::sinf(phi);
	return Vector3(x, r1, z);
}

int Vector3::getGreatestAxis(Vector3 vec)
{
	if (vec.m_value[Maths::coord::x] > vec.m_value[Maths::coord::y] && vec.m_value[Maths::coord::x] > vec.m_value[Maths::coord::z]) return Maths::coord::x;
	else if (vec.m_value[Maths::coord::y] > vec.m_value[Maths::coord::z]) return Maths::coord::y;
	else return Maths::coord::z;
}
