#pragma once
#include <math.h>
#include <iostream>
#include <string>
#include <array>

#include "Maths.h"

class Vector3
{
	public:
		Vector3();
		Vector3(float _x, float _y, float _z) : m_value{_x, _y, _z} {}
		~Vector3() = default;
		
		// Assignment Operators
		Vector3& operator=(const Vector3& _rhs);
		Vector3 operator+=(const Vector3& _rhs);
		Vector3 operator-=(const Vector3& _rhs);
		Vector3 operator*=(const Vector3& _rhs);
		Vector3 operator/=(const Vector3& _rhs);

		// Arithmetic Operators
		Vector3 operator+(const Vector3& _rhs);
		Vector3 operator+(const float& _rhs);
		Vector3 operator-(const Vector3& _rhs);
		Vector3 operator*(const Vector3& _rhs);
		Vector3 operator/(const Vector3& _rhs);

		// Relational Operators
		bool operator>(const Vector3& _rhs);
		bool operator<(const Vector3& _rhs);
		bool operator>=(const Vector3& _rhs);
		bool operator<=(const Vector3& _rhs);
		bool operator==(const Vector3& _rhs);
		bool operator!=(const Vector3& _rhs);
		
		// Friend Operators
		friend Vector3 operator+(const float& _lhs, const Vector3& _rhs);
		friend Vector3 operator+(const Vector3& _lhs, const float& _rhs);
		friend Vector3 operator-(const float& _lhs, const Vector3& _rhs);
		friend Vector3 operator-(const Vector3& _lhs, const float& _rhs);
		friend Vector3 operator*(const float& _lhs, const Vector3& _rhs);
		friend Vector3 operator*(const Vector3& _lhs, const float& _rhs);
		friend Vector3 operator/(const float& _lhs, const Vector3& _rhs);
		friend Vector3 operator/(const Vector3& _lhs, const float& _rhs);

		// unary operator
		Vector3 operator-();

		// Mainly used for debugging
		friend std::ostream& operator<<(std::ostream& _lhs, const Vector3& _rhs)
		{
			_lhs << std::to_string(_rhs.m_value.at(Maths::coord::x)) << ", " << std::to_string(_rhs.m_value.at(Maths::coord::y)) << ", " << std::to_string(_rhs.m_value.at(Maths::coord::z));
			return _lhs;
		}

		// Produces a new vector3 C using vector3 A and B
		static Vector3 cross(const Vector3& _lhs, const Vector3& _rhs);

		// Calculates the relationship between two vectors3
		static float dot(const Vector3& _lhs, const Vector3& _rhs);

		// Finds the magnitude from the vectors3
		static float magnitude(const Vector3& _rhs);

		// Normalizes a vector3 using it magnitude
		static Vector3 normalize(const Vector3& _rhs);

		// Find a vector3 midpoint between two vectors3
		static Vector3 findMidPoint(Vector3 vec1, Vector3 vec2);

		// Returns the distance between two vectors3
		static float distance(Vector3 a, Vector3 b);

		// Returns the length of the vector3
		static float length(Vector3 a);

		static Vector3 random();

		static Vector3 randomInRange(const float min, const float max);

		static Vector3 randomUnitSphere();

		static void createCoordinateSystem(const Vector3& n, Vector3& nt, Vector3& nb);

		static Vector3 uniformSampleHemisphere(const float& r1, const float& r2);

		// Finds the biggest axis from a Vector3
		static int getGreatestAxis(Vector3 vec);

		// Setters
		void setX(float _x) { m_value.at(Maths::coord::x) = _x; }
		void setY(float _y) { m_value.at(Maths::coord::y) = _y; }
		void setZ(float _z) { m_value.at(Maths::coord::z) = _z; }

		// Getters
		const float& getX() const { return m_value.at(Maths::coord::x); }
		const float& getY() const { return m_value.at(Maths::coord::y); }
		const float& getZ() const { return m_value.at(Maths::coord::z); }
		const std::array<float, 3>& getValue() const{ return m_value; }

	private:
		std::array<float, 3> m_value = {0.0f, 0.0f, 0.0f};
};
