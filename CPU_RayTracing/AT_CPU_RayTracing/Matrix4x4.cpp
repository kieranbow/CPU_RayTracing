#include <algorithm>

#include "Matrix4x4.h"
#include "Vector3.h"

Matrix4x4::Matrix4x4()
{
	// inits the matrix with zero
	std::fill(m_elements.begin(), m_elements.end(), 0.0f);

	// Defines a idenity matrix
	this->m_elements.at(c::c00) = 1.0f;
	this->m_elements.at(c::c11) = 1.0f;
	this->m_elements.at(c::c22) = 1.0f;
	this->m_elements.at(c::c33) = 1.0f;
}

Matrix4x4::Matrix4x4(float c00, float c01, float c02, float c03, float c10, float c11, float c12, float c13, float c20, float c21, float c22, float c23, float c30, float c31, float c32, float c33)
{
	this->m_elements.at(c::c00) = c00;
	this->m_elements.at(c::c01) = c01;
	this->m_elements.at(c::c02) = c02;
	this->m_elements.at(c::c03) = c03;
	this->m_elements.at(c::c10) = c10;
	this->m_elements.at(c::c11) = c11;
	this->m_elements.at(c::c12) = c12;
	this->m_elements.at(c::c13) = c13;
	this->m_elements.at(c::c20) = c20;
	this->m_elements.at(c::c21) = c21;
	this->m_elements.at(c::c22) = c22;
	this->m_elements.at(c::c23) = c23;
	this->m_elements.at(c::c30) = c30;
	this->m_elements.at(c::c31) = c31;
	this->m_elements.at(c::c32) = c32;
	this->m_elements.at(c::c33) = c33;
}

void Matrix4x4::multVecByMatrix4x4(const Matrix4x4& _lhs, Vector3& _rhs)
{
	Vector3 vector;
	// Column major
	vector.setX(_rhs.getX() * _lhs.m_elements.at(c::c00) + _rhs.getY() * _lhs.m_elements.at(c::c01) + _rhs.getZ() * _lhs.m_elements.at(c::c02) + _lhs.m_elements.at(c::c03));
	vector.setY(_rhs.getX() * _lhs.m_elements.at(c::c10) + _rhs.getY() * _lhs.m_elements.at(c::c11) + _rhs.getZ() * _lhs.m_elements.at(c::c12) + _lhs.m_elements.at(c::c13));
	vector.setZ(_rhs.getX() * _lhs.m_elements.at(c::c20) + _rhs.getY() * _lhs.m_elements.at(c::c21) + _rhs.getZ() * _lhs.m_elements.at(c::c22) + _lhs.m_elements.at(c::c23));
	float w = _rhs.getX() * _lhs.m_elements.at(c::c30) + _rhs.getY() * _lhs.m_elements.at(c::c31) + _rhs.getZ() * _lhs.m_elements.at(c::c32) + _lhs.m_elements.at(c::c33);

	if (w != 1.0f)
	{
		vector.setX(_rhs.getX() / w);
		vector.setY(_rhs.getY() / w);
		vector.setZ(_rhs.getZ() / w);
	}
	_rhs = vector;
}

void Matrix4x4::multDirByMatrix4x4(const Matrix4x4 _mat, const Vector3& _lhs, Vector3& _rhs)
{
	// Column major
	_rhs.setX(_lhs.getX() * _mat.m_elements.at(c::c00) + _lhs.getY() * _mat.m_elements.at(c::c01) + _lhs.getZ() * _mat.m_elements.at(c::c02));
	_rhs.setY(_lhs.getX() * _mat.m_elements.at(c::c10) + _lhs.getY() * _mat.m_elements.at(c::c11) + _lhs.getZ() * _mat.m_elements.at(c::c12));
	_rhs.setZ(_lhs.getX() * _mat.m_elements.at(c::c20) + _lhs.getY() * _mat.m_elements.at(c::c21) + _lhs.getZ() * _mat.m_elements.at(c::c22));
}

Vector3 Matrix4x4::multVecByMatrix4x4(Vector3 position)
{
	Vector3 vector;
	// Column major
	vector.setX(position.getX() * m_elements.at(c::c00) + position.getY() * m_elements.at(c::c01) + position.getZ() * m_elements.at(c::c02) + m_elements.at(c::c03));
	vector.setY(position.getX() * m_elements.at(c::c10) + position.getY() * m_elements.at(c::c11) + position.getZ() * m_elements.at(c::c12) + m_elements.at(c::c13));
	vector.setZ(position.getX() * m_elements.at(c::c20) + position.getY() * m_elements.at(c::c21) + position.getZ() * m_elements.at(c::c22) + m_elements.at(c::c23));
	float w = position.getX() * m_elements.at(c::c30) + position.getY() * m_elements.at(c::c31) + position.getZ() * m_elements.at(c::c32) + m_elements.at(c::c33);

	if (w != 1.0f)
	{
		vector.setX(position.getX() / w);
		vector.setY(position.getY() / w);
		vector.setZ(position.getZ() / w);
	}
	return vector;
}

Vector3 Matrix4x4::multDirByMatrix4x4(const Vector3& _lhs, Vector3& _rhs)
{
	// As explain here: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
	// if w == 0 then the vector is a direction.
	
	// Column major
	_rhs.setX(_lhs.getX() * m_elements.at(c::c00) + _lhs.getY() * m_elements.at(c::c01) + _lhs.getZ() * m_elements.at(c::c02));
	_rhs.setY(_lhs.getX() * m_elements.at(c::c10) + _lhs.getY() * m_elements.at(c::c11) + _lhs.getZ() * m_elements.at(c::c12));
	_rhs.setZ(_lhs.getX() * m_elements.at(c::c20) + _lhs.getY() * m_elements.at(c::c21) + _lhs.getZ() * m_elements.at(c::c22));

	return _rhs;
}

Vector3 Matrix4x4::translation(Vector3 _rhs)
{
	// Column major
	_rhs.setX(m_elements.at(c::c00) * _rhs.getX() + m_elements.at(c::c01) * _rhs.getY() + m_elements.at(c::c02) * _rhs.getZ() + m_elements.at(c::c03) * 1.0f);
	_rhs.setY(m_elements.at(c::c10) * _rhs.getX() + m_elements.at(c::c11) * _rhs.getY() + m_elements.at(c::c12) * _rhs.getZ() + m_elements.at(c::c31) * 1.0f);
	_rhs.setZ(m_elements.at(c::c20) * _rhs.getX() + m_elements.at(c::c21) * _rhs.getY() + m_elements.at(c::c22) * _rhs.getZ() + m_elements.at(c::c32) * 1.0f);

	return _rhs;
}
