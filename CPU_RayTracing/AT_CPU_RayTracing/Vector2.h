#pragma once
#include <math.h>
#include <iostream>
#include <string>
#include <array>

#include "Maths.h"

// Essentally the same as vector3 but without a z component
class Vector2
{
	public:
		Vector2();
		Vector2(float _x, float _y) : m_value{_x, _y} {}
		~Vector2() = default;

		// Assignment Operators
		Vector2& operator=(const Vector2& _rhs);
		Vector2 operator+=(const Vector2& _rhs);
		Vector2 operator-=(const Vector2& _rhs);
		Vector2 operator*=(const Vector2& _rhs);

		// Arithmetic Operators
		Vector2 operator+(const Vector2& _rhs);
		Vector2 operator+(const float& _rhs);
		Vector2 operator-(const Vector2& _rhs);
		Vector2 operator*(const Vector2& _rhs);
		Vector2 operator/(const Vector2& _rhs);
		Vector2 operator/(const float& _rhs);

		// Relational Operators
		bool operator>(const Vector2& _rhs);
		bool operator<(const Vector2& _rhs);
		bool operator>=(const Vector2& _rhs);
		bool operator<=(const Vector2& _rhs);
		bool operator==(const Vector2& _rhs);
		bool operator!=(const Vector2& _rhs);

		// Friend Operators
		friend Vector2 operator+(const float& _lhs, const Vector2& _rhs);
		friend Vector2 operator+(const Vector2& _lhs, const float& _rhs);
		friend Vector2 operator-(const float& _lhs, const Vector2& _rhs);
		friend Vector2 operator-(const Vector2& _lhs, const float& _rhs);
		friend Vector2 operator*(const float& _lhs, const Vector2& _rhs);
		friend Vector2 operator*(const Vector2& _lhs, const float& _rhs);
		friend Vector2 operator/(const float& _lhs, const Vector2& _rhs);
		friend Vector2 operator/(const Vector2& _lhs, const float& _rhs);

		// Mainly used for debugging 
		friend std::ostream& operator<<(std::ostream& _lhs, const Vector2& _rhs)
		{
			_lhs << std::to_string(_rhs.m_value.at(Maths::coord::x)) << ", " << std::to_string(_rhs.m_value.at(Maths::coord::y));
			return _lhs;
		}

		// Calculates the relationship between two vector2
		static float dot(const Vector2& _lhs, const Vector2& _rhs);

		// Finds the magnitude from the vector2
		static float magnitude(const Vector2& _rhs);

		// Normalizes a vector2 using it magnitude
		static Vector2 normalize(const Vector2& _rhs);

		// Find a vector2 midpoint between two vectors2
		static Vector2 findMidPoint(Vector2 vec1, Vector2 vec2);

		// Setters
		void setX(float _x) { m_value.at(Maths::coord::x) = _x; }
		void setY(float _y) { m_value.at(Maths::coord::y) = _y; }

		// Getters
		const float& getX() const { return m_value.at(Maths::coord::x); }
		const float& getY() const { return m_value.at(Maths::coord::y); }
		const std::array<float, 2>& getValue() const { return m_value; }

	private:
		std::array<float, 2> m_value;
};
