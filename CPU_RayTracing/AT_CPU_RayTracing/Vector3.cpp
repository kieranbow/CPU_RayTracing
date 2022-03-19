#include "Vector3.h"
#include "Random.h"

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

Vector3 operator+(const float& _lhs, const Vector3& _rhs)
{
	return Vector3(_rhs.getX() + _lhs, _rhs.getY() + _lhs, _rhs.getZ() + _lhs);
}

Vector3 operator+(const Vector3& _lhs, const float& _rhs)
{
	return Vector3(_lhs.getX() + _rhs, _lhs.getY() + _rhs, _lhs.getZ() + _rhs);
}

Vector3 operator-(const float& _lhs, const Vector3& _rhs)
{
	return Vector3(_rhs.getX() - _lhs, _rhs.getY() - _lhs, _rhs.getZ() - _lhs);
}

Vector3 operator-(const Vector3& _lhs, const float& _rhs)
{
	return Vector3(_lhs.getX() - _rhs, _lhs.getY() - _rhs, _lhs.getZ() - _rhs);
}

Vector3 operator*(const float& _lhs, const Vector3& _rhs)
{
	return Vector3(_rhs.getX() * _lhs, _rhs.getY() * _lhs, _rhs.getZ() * _lhs);
}

Vector3 operator*(const Vector3& _lhs, const float& _rhs)
{
	return Vector3(_lhs.getX() * _rhs, _lhs.getY() * _rhs, _lhs.getZ() * _rhs);
}

Vector3 operator/(const float& _lhs, const Vector3& _rhs)
{
	return Vector3(_rhs.getX() / _lhs, _rhs.getY() / _lhs, _rhs.getZ() / _lhs);
}

Vector3 operator/(const Vector3& _lhs, const float& _rhs)
{
	return Vector3(_lhs.getX() / _rhs, _lhs.getY() / _rhs, _lhs.getZ() / _rhs);
}

Vector3 Vector3::operator-()
{
	Vector3 v;
	v.setX(-this->m_value.at(Maths::coord::x));
	v.setY(-this->m_value.at(Maths::coord::y));
	v.setZ(-this->m_value.at(Maths::coord::z));
	return v;
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
	return std::sqrtf((_rhs.m_value.at(Maths::coord::x) * _rhs.m_value.at(Maths::coord::x)) + (_rhs.m_value.at(Maths::coord::y) * _rhs.m_value.at(Maths::coord::y)) + (_rhs.m_value.at(Maths::coord::z) * _rhs.m_value.at(Maths::coord::z)));
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

float Vector3::distance(Vector3 a, Vector3 b)
{
	float x = Maths::sqr(a.m_value.at(0) - b.m_value.at(0));
	float y = Maths::sqr(a.m_value.at(1) - b.m_value.at(1));
	float z = Maths::sqr(a.m_value.at(2) - b.m_value.at(2));
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

Vector3 Vector3::randomUnitSphere()
{
	while (true)
	{
		Vector3 p = randomInRange(-1, 1);
		if (Vector3::dot(p, p) >= 1.0f) continue;
		return p;
	}
}
