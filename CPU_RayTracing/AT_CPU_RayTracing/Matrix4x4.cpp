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

Vector3 Matrix4x4::multiplyVectorToMatrix4x4(const Vector3& _lhs, Vector3& _rhs, const float& w)
{
	//float a = 0.0f, b = 0.0f, c = 0.0f, w = 0.0f;

	// Column major
	_rhs.setX(_lhs.getX() * m_elements.at(static_cast<int>(c::c00)) + _lhs.getY() * m_elements.at(static_cast<int>(c::c01)) + _lhs.getZ() * m_elements.at(static_cast<int>(c::c02)) + m_elements.at(static_cast<int>(c::c03)) * w);
	_rhs.setY(_lhs.getX() * m_elements.at(static_cast<int>(c::c10)) + _lhs.getY() * m_elements.at(static_cast<int>(c::c11)) + _lhs.getZ() * m_elements.at(static_cast<int>(c::c12)) + m_elements.at(static_cast<int>(c::c13)) * w);
	_rhs.setZ(_lhs.getX() * m_elements.at(static_cast<int>(c::c20)) + _lhs.getY() * m_elements.at(static_cast<int>(c::c21)) + _lhs.getZ() * m_elements.at(static_cast<int>(c::c22)) + m_elements.at(static_cast<int>(c::c23)) * w);
	//w = _lhs.getX() * m_elements.at(static_cast<int>(c::c30)) + _lhs.getY() * m_elements.at(static_cast<int>(c::c31)) + _lhs.getZ() * m_elements.at(static_cast<int>(c::c32)) + m_elements.at(static_cast<int>(c::c33)) * w;

	//_rhs.setX(a / w);
	//_rhs.setY(b / w);
	//_rhs.setZ(c / w);
	return _rhs;
}
