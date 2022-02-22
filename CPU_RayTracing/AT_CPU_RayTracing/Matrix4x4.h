#pragma once
#include <array>

class Vector3;

class Matrix4x4
{
	public:
		Matrix4x4();
		Matrix4x4(float c00, float c01, float c02, float c03, float c10, float c11, float c12, float c13, float c20, float c21, float c22, float c23, float c30, float c31, float c32, float c33);
		
		~Matrix4x4() = default;

		Vector3 multiplyVectorToMatrix4x4(const Vector3& _lhs, Vector3& _rhs);


	private:
		std::array<float, 16> m_elements;

		// Mainly used to help identify which coefficient is being accessed in the array
		enum class c : int
		{
			c00,
			c01,
			c02,
			c03,
			c10,
			c11,
			c12,
			c13,
			c20,
			c21,
			c22,
			c23,
			c30,
			c31,
			c32,
			c33
		};
};
