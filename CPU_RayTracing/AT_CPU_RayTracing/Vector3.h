#pragma once
#include <math.h>
#include <iostream>
#include <string>

#include "Numbers.h"

// Add template to vector
class Vector3
{
	public:
		Vector3();
		Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

		~Vector3() = default;

		Vector3 operator=(const Vector3& _rhs);
		Vector3 operator+(const Vector3& _rhs);
		Vector3 operator+(const float& _rhs);
		Vector3 operator+=(const Vector3& _rhs);
		Vector3 operator-(const Vector3& _rhs);
		Vector3 operator-=(const Vector3& _rhs);
		Vector3 operator*(const Vector3& _rhs);
		Vector3 operator*=(const Vector3& _rhs);
		Vector3 operator/(const Vector3& _rhs);
		
		friend std::ostream& operator<<(std::ostream& _lhs, const Vector3& _rhs)
		{
			_lhs << std::to_string(_rhs.x) << ", " << std::to_string(_rhs.y) << ", " << std::to_string(_rhs.z);
			return _lhs;
		}

		// Produces a new vector C using vector A and B
		static Vector3 cross(const Vector3& _lhs, const Vector3& _rhs);

		// Calculates the relationship between two vectors. I.e opposite vectors = -1
		static float dot(const Vector3& _lhs, const Vector3& _rhs);

		// Finds the magnitude from the vectors x,y,z coords
		static float magnitude(const Vector3& _rhs);

		// Normalizes a vector using it magnitude
		static Vector3 normalize(const Vector3& _rhs);

		// Setters
		void setX(float _x) { x = _x; }
		void setY(float _y) { y = _y; }
		void setZ(float _z) { z = _z; }

		// Getters
		const float& getX() const { return x; }
		const float& getY() const { return y; }
		const float& getZ() const { return z; }

	private:
		float x = 0;
		float y = 0;
		float z = 0;
};
