#pragma once
#include <array>

class Vector3;

// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
// https://codereview.stackexchange.com/questions/144381/4x4-matrix-implementation-in-c
// http://www.codinglabs.net/article_world_view_projection_matrix.aspx

class Matrix4x4
{
	public:
		Matrix4x4();
		Matrix4x4(float c00, float c01, float c02, float c03, float c10, float c11, float c12, float c13, float c20, float c21, float c22, float c23, float c30, float c31, float c32, float c33);
		
		~Matrix4x4() = default;

		static void multVecByMatrix4x4(const Matrix4x4& _lhs, Vector3& _rhs);
		static void multDirByMatrix4x4(const Matrix4x4 _mat, const Vector3& _lhs, Vector3& _rhs);
		
		Vector3 multVecByMatrix4x4(Vector3 position);
		Vector3 multDirByMatrix4x4(const Vector3& _lhs, Vector3& _rhs);

		// https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
		void InvertMatrix();

		Vector3 translation(Vector3 position);
		Vector3 scale();
		Vector3 rotation();

	private:
		std::array<float, 16> m_elements;

		// Mainly used to help identify which coefficient is being accessed in the array
		enum c : int
		{
			c00, c01, c02, c03,
			c10, c11, c12, c13,
			c20, c21, c22, c23, 
			c30, c31, c32, c33
		};
};
