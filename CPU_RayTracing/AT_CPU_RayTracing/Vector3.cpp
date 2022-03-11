#include "Vector3.h"

Vector3::Vector3()
{
	//x = 0.0f;
	//y = 0.0f;
	//z = 0.0f;
	value.at(0) = 0;
	value.at(1) = 0;
	value.at(2) = 0;
}

Vector3& Vector3::operator=(const Vector3& _rhs)
{
	this->value.at(0) = _rhs.value.at(0);
	this->value.at(1) = _rhs.value.at(1);
	this->value.at(2) = _rhs.value.at(2);
	return *this;
}

Vector3 Vector3::operator+(const Vector3& _rhs)
{
	Vector3 vector;
	vector.value.at(0) = this->value.at(0) + _rhs.value.at(0);
	vector.value.at(1) = this->value.at(1) + _rhs.value.at(1);
	vector.value.at(2) = this->value.at(2) + _rhs.value.at(2);
	return vector;
}

Vector3 Vector3::operator+(const float& _rhs)
{
	Vector3 vector;
	vector.value.at(0) = this->value.at(0) + _rhs;
	vector.value.at(1) = this->value.at(1) + _rhs;
	vector.value.at(2) = this->value.at(2) + _rhs;
	return vector;
}

Vector3 Vector3::operator+=(const Vector3& _rhs)
{
	this->value.at(0) += _rhs.value.at(0);
	this->value.at(1) += _rhs.value.at(1);
	this->value.at(2) += _rhs.value.at(2);
	return *this;
}

Vector3 Vector3::operator-(const Vector3& _rhs)
{
	Vector3 vector;
	vector.value.at(0) = this->value.at(0) - _rhs.value.at(0);
	vector.value.at(1) = this->value.at(1) - _rhs.value.at(1);
	vector.value.at(2) = this->value.at(2) - _rhs.value.at(2);
	return vector;
}

Vector3 Vector3::operator-=(const Vector3& _rhs)
{
	this->value.at(0) -= _rhs.value.at(0);
	this->value.at(1) -= _rhs.value.at(1);
	this->value.at(2) -= _rhs.value.at(2);
	return *this;
}

Vector3 Vector3::operator*(const Vector3& _rhs)
{
	Vector3 vector;
	vector.value.at(0) = this->value.at(0) * _rhs.value.at(0);
	vector.value.at(1) = this->value.at(1) * _rhs.value.at(1);
	vector.value.at(2) = this->value.at(2) * _rhs.value.at(2);
	return vector;
}

Vector3 Vector3::operator*=(const Vector3& _rhs)
{
	this->value.at(0) *= _rhs.value.at(0);
	this->value.at(1) *= _rhs.value.at(1);
	this->value.at(2) *= _rhs.value.at(2);
	return *this;
}

Vector3 Vector3::operator/=(const Vector3& _rhs)
{
	this->value.at(0) /= _rhs.value.at(0);
	this->value.at(1) /= _rhs.value.at(1);
	this->value.at(2) /= _rhs.value.at(2);
	return *this;
}

Vector3 Vector3::operator/(const Vector3& _rhs)
{
	Vector3 vector;
	vector.value.at(0) = this->value.at(0) / _rhs.value.at(0);
	vector.value.at(1) = this->value.at(1) / _rhs.value.at(1);
	vector.value.at(2) = this->value.at(2) / _rhs.value.at(2);
	return vector;
}

bool Vector3::operator>(const Vector3& _rhs)
{
	return (this->value.at(0) > _rhs.value.at(0) && this->value.at(1) > _rhs.value.at(1) && this->value.at(2) > _rhs.value.at(2));
}

bool Vector3::operator<(const Vector3& _rhs)
{
	return (this->value.at(0) < _rhs.value.at(0) && this->value.at(1) < _rhs.value.at(1) && this->value.at(2) < _rhs.value.at(2));
}

bool Vector3::operator>=(const Vector3& _rhs)
{
	return (this->value.at(0) >= _rhs.value.at(0) && this->value.at(1) >= _rhs.value.at(1) && this->value.at(2) >= _rhs.value.at(2));
}

bool Vector3::operator<=(const Vector3& _rhs)
{
	return (this->value.at(0) <= _rhs.value.at(0) && this->value.at(1) <= _rhs.value.at(1) && this->value.at(2) <= _rhs.value.at(2));
}

bool Vector3::operator==(const Vector3& _rhs)
{
	return (this->value.at(0) == _rhs.value.at(0) && this->value.at(1) == _rhs.value.at(1) && this->value.at(2) == _rhs.value.at(2));
}

bool Vector3::operator!=(const Vector3& _rhs)
{
	return (this->value.at(0) != _rhs.value.at(0) && this->value.at(1) != _rhs.value.at(1) && this->value.at(0) != _rhs.value.at(0));
}

Vector3 Vector3::cross(const Vector3& _lhs, const Vector3& _rhs)
{
	float x = (_lhs.value.at(1) * _rhs.value.at(2)) - (_lhs.value.at(2) * _rhs.value.at(1));
	float y = (_lhs.value.at(2) * _rhs.value.at(0)) - (_lhs.value.at(0) * _rhs.value.at(2));
	float z = (_lhs.value.at(0) * _rhs.value.at(1)) - (_lhs.value.at(1) * _rhs.value.at(0));
	return Vector3(x, y, z);
}

float Vector3::dot(const Vector3& _lhs, const Vector3& _rhs)
{
	return (_lhs.value.at(0) * _rhs.value.at(0)) + (_lhs.value.at(1) * _rhs.value.at(1)) + (_lhs.value.at(2) * _rhs.value.at(2));
}

float Vector3::magnitude(const Vector3& _rhs)
{
	return sqrtf((_rhs.value.at(0) * _rhs.value.at(0)) + (_rhs.value.at(1) * _rhs.value.at(1)) + (_rhs.value.at(2) * _rhs.value.at(2)));
}

Vector3 Vector3::normalize(const Vector3& _rhs)
{
	float mag = magnitude(_rhs);

	if (mag < epsilon) return Vector3(0.0f, 0.0f, 0.0f);
	return Vector3(_rhs.value.at(0) / mag, _rhs.value.at(1) / mag, _rhs.value.at(2) / mag);
}

Vector3 Vector3::findMidPoint(const Vector3 & vec1)
{
	return Vector3(vec1.getX() + vec1.getX() / 2.0f, vec1.getY() + vec1.getY() / 2.0f, vec1.getZ() + vec1.getZ() / 2.0f);
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
