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

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& _rhs)
{
	Matrix4x4 matrix;
	this->m_elements.at(c::c00) = this->m_elements.at(c::c00) * _rhs.m_elements.at(c::c00);
	this->m_elements.at(c::c01) = this->m_elements.at(c::c01) * _rhs.m_elements.at(c::c01);
	this->m_elements.at(c::c02) = this->m_elements.at(c::c02) * _rhs.m_elements.at(c::c02);
	this->m_elements.at(c::c03) = this->m_elements.at(c::c03) * _rhs.m_elements.at(c::c03);

	this->m_elements.at(c::c10) = this->m_elements.at(c::c10) * _rhs.m_elements.at(c::c10);
	this->m_elements.at(c::c11) = this->m_elements.at(c::c11) * _rhs.m_elements.at(c::c11);
	this->m_elements.at(c::c12) = this->m_elements.at(c::c12) * _rhs.m_elements.at(c::c12);
	this->m_elements.at(c::c13) = this->m_elements.at(c::c13) * _rhs.m_elements.at(c::c13);

	this->m_elements.at(c::c20) = this->m_elements.at(c::c20) * _rhs.m_elements.at(c::c20);
	this->m_elements.at(c::c21) = this->m_elements.at(c::c21) * _rhs.m_elements.at(c::c21);
	this->m_elements.at(c::c22) = this->m_elements.at(c::c22) * _rhs.m_elements.at(c::c22);
	this->m_elements.at(c::c23) = this->m_elements.at(c::c23) * _rhs.m_elements.at(c::c23);

	this->m_elements.at(c::c30) = this->m_elements.at(c::c30) * _rhs.m_elements.at(c::c30);
	this->m_elements.at(c::c31) = this->m_elements.at(c::c31) * _rhs.m_elements.at(c::c31);
	this->m_elements.at(c::c32) = this->m_elements.at(c::c32) * _rhs.m_elements.at(c::c32);
	this->m_elements.at(c::c33) = this->m_elements.at(c::c33) * _rhs.m_elements.at(c::c33);
	return matrix;
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

void Matrix4x4::multVecMatrix(const Vector3& src, Vector3& dst)
{
	dst.setX(src.getX() * m_elements.at(c::c00) + src.getY() * m_elements.at(c::c01) + src.getZ() * m_elements.at(c::c02) + m_elements.at(c::c03));
	dst.setY(src.getX() * m_elements.at(c::c10) + src.getY() * m_elements.at(c::c11) + src.getZ() * m_elements.at(c::c12) + m_elements.at(c::c13));
	dst.setZ(src.getX() * m_elements.at(c::c20) + src.getY() * m_elements.at(c::c21) + src.getZ() * m_elements.at(c::c22) + m_elements.at(c::c23));
	float w = src.getX() * m_elements.at(c::c30) + src.getY() * m_elements.at(c::c31) + src.getZ() * m_elements.at(c::c32) + m_elements.at(c::c33);
	if (w != 1.0f && w != 0.0f)
	{
		dst.setX(src.getX() / w);
		dst.setY(src.getY() / w);
		dst.setZ(src.getZ() / w);
	}
}

Vector3 Matrix4x4::multVecByMatrix4x4(Vector3 m_position)
{
	Vector3 vector;
	// Column major
	vector.setX(m_position.getX() * m_elements.at(c::c00) + m_position.getY() * m_elements.at(c::c01) + m_position.getZ() * m_elements.at(c::c02) + m_elements.at(c::c03));
	vector.setY(m_position.getX() * m_elements.at(c::c10) + m_position.getY() * m_elements.at(c::c11) + m_position.getZ() * m_elements.at(c::c12) + m_elements.at(c::c13));
	vector.setZ(m_position.getX() * m_elements.at(c::c20) + m_position.getY() * m_elements.at(c::c21) + m_position.getZ() * m_elements.at(c::c22) + m_elements.at(c::c23));
	float w = m_position.getX() * m_elements.at(c::c30) + m_position.getY() * m_elements.at(c::c31) + m_position.getZ() * m_elements.at(c::c32) + m_elements.at(c::c33);

	if (w != 1.0f)
	{
		vector.setX(m_position.getX() / w);
		vector.setY(m_position.getY() / w);
		vector.setZ(m_position.getZ() / w);
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

Vector3 Matrix4x4::scale(Vector3 scale, Vector3 m_position)
{
	// Defines a scaled idenity matrix
	this->m_elements.at(c::c00) = scale.getX();
	this->m_elements.at(c::c11) = scale.getY();
	this->m_elements.at(c::c22) = scale.getZ();

	// Column major
	m_position.setX(m_elements.at(c::c00) * m_position.getX() + m_elements.at(c::c01) * m_position.getY() + m_elements.at(c::c02) * m_position.getZ() + m_elements.at(c::c03) * 0.0f);
	m_position.setY(m_elements.at(c::c10) * m_position.getX() + m_elements.at(c::c11) * m_position.getY() + m_elements.at(c::c12) * m_position.getZ() + m_elements.at(c::c31) * 0.0f);
	m_position.setZ(m_elements.at(c::c20) * m_position.getX() + m_elements.at(c::c21) * m_position.getY() + m_elements.at(c::c22) * m_position.getZ() + m_elements.at(c::c32) * 0.0f);

	return m_position;
}
