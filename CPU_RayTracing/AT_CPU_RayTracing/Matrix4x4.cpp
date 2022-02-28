#include <algorithm>

#include "Matrix4x4.h"
#include "Vector3.h"

Matrix4x4::Matrix4x4()
{
	// inits the matrix with zero
	std::fill(m_elements.begin(), m_elements.end(), 0.0f);

	// Defines a idenity matrix
	this->m_elements.at(static_cast<int>(c::c00)) = 1.0f;
	this->m_elements.at(static_cast<int>(c::c11)) = 1.0f;
	this->m_elements.at(static_cast<int>(c::c22)) = 1.0f;
	this->m_elements.at(static_cast<int>(c::c33)) = 1.0f;
}

Matrix4x4::Matrix4x4(float c00, float c01, float c02, float c03, float c10, float c11, float c12, float c13, float c20, float c21, float c22, float c23, float c30, float c31, float c32, float c33)
{
	this->m_elements.at(static_cast<int>(c::c00)) = c00;
	this->m_elements.at(static_cast<int>(c::c01)) = c01;
	this->m_elements.at(static_cast<int>(c::c02)) = c02;
	this->m_elements.at(static_cast<int>(c::c03)) = c03;
	this->m_elements.at(static_cast<int>(c::c10)) = c10;
	this->m_elements.at(static_cast<int>(c::c11)) = c11;
	this->m_elements.at(static_cast<int>(c::c12)) = c12;
	this->m_elements.at(static_cast<int>(c::c13)) = c13;
	this->m_elements.at(static_cast<int>(c::c20)) = c20;
	this->m_elements.at(static_cast<int>(c::c21)) = c21;
	this->m_elements.at(static_cast<int>(c::c22)) = c22;
	this->m_elements.at(static_cast<int>(c::c23)) = c23;
	this->m_elements.at(static_cast<int>(c::c30)) = c30;
	this->m_elements.at(static_cast<int>(c::c31)) = c31;
	this->m_elements.at(static_cast<int>(c::c32)) = c32;
	this->m_elements.at(static_cast<int>(c::c33)) = c33;
}

void Matrix4x4::multVecByMatrix4x4(const Matrix4x4& _lhs, Vector3& _rhs)
{
	Vector3 vector;
	// Column major
	vector.setX(_rhs.getX() * _lhs.m_elements.at(static_cast<int>(c::c00)) + _rhs.getY() * _lhs.m_elements.at(static_cast<int>(c::c01)) + _rhs.getZ() * _lhs.m_elements.at(static_cast<int>(c::c02)) + _lhs.m_elements.at(static_cast<int>(c::c03)));
	vector.setY(_rhs.getX() * _lhs.m_elements.at(static_cast<int>(c::c10)) + _rhs.getY() * _lhs.m_elements.at(static_cast<int>(c::c11)) + _rhs.getZ() * _lhs.m_elements.at(static_cast<int>(c::c12)) + _lhs.m_elements.at(static_cast<int>(c::c30)));
	vector.setZ(_rhs.getX() * _lhs.m_elements.at(static_cast<int>(c::c20)) + _rhs.getY() * _lhs.m_elements.at(static_cast<int>(c::c21)) + _rhs.getZ() * _lhs.m_elements.at(static_cast<int>(c::c22)) + _lhs.m_elements.at(static_cast<int>(c::c32)));
	float w = _rhs.getX() * _lhs.m_elements.at(static_cast<int>(c::c30)) + _rhs.getY() * _lhs.m_elements.at(static_cast<int>(c::c31)) + _rhs.getZ() * _lhs.m_elements.at(static_cast<int>(c::c32)) + _lhs.m_elements.at(static_cast<int>(c::c33));
	
	if (w != 1.0f)
	{
		vector.setX(vector.getX() / w);
		vector.setY(vector.getY() / w);
		vector.setZ(vector.getZ() / w);
	}
	_rhs = vector;
}

Vector3 Matrix4x4::multDirByMatrix4x4(const Vector3& _lhs, Vector3& _rhs)
{
	// As explain here: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
	// if w == 0 then the vector is a direction.
	
	// Column major
	_rhs.setX(_lhs.getX() * m_elements.at(static_cast<int>(c::c00)) + _lhs.getY() * m_elements.at(static_cast<int>(c::c01)) + _lhs.getZ() * m_elements.at(static_cast<int>(c::c02)));
	_rhs.setY(_lhs.getX() * m_elements.at(static_cast<int>(c::c10)) + _lhs.getY() * m_elements.at(static_cast<int>(c::c11)) + _lhs.getZ() * m_elements.at(static_cast<int>(c::c12)));
	_rhs.setZ(_lhs.getX() * m_elements.at(static_cast<int>(c::c20)) + _lhs.getY() * m_elements.at(static_cast<int>(c::c21)) + _lhs.getZ() * m_elements.at(static_cast<int>(c::c22)));

	return _rhs;
}

// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
Vector3 Matrix4x4::translation(const Vector3& _rhs)
{
	Vector3 vector;
	// Column major
	vector.setX(m_elements.at(static_cast<int>(c::c00)) * _rhs.getX() + m_elements.at(static_cast<int>(c::c01)) * _rhs.getY() + m_elements.at(static_cast<int>(c::c02)) * _rhs.getZ() + m_elements.at(static_cast<int>(c::c03)) * 1.0f);
	vector.setY(m_elements.at(static_cast<int>(c::c10)) * _rhs.getX() + m_elements.at(static_cast<int>(c::c11)) * _rhs.getY() + m_elements.at(static_cast<int>(c::c12)) * _rhs.getZ() + m_elements.at(static_cast<int>(c::c31)) * 1.0f);
	vector.setZ(m_elements.at(static_cast<int>(c::c20)) * _rhs.getX() + m_elements.at(static_cast<int>(c::c21)) * _rhs.getY() + m_elements.at(static_cast<int>(c::c22)) * _rhs.getZ() + m_elements.at(static_cast<int>(c::c32)) * 1.0f);

	return vector;
}
