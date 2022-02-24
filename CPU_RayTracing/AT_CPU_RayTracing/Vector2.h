#pragma once
#include <math.h>
#include <iostream>
#include <string>

#include "Numbers.h"

// Essentally the same as vector3 but without a z component
class Vector2
{
	public:
		Vector2();
		Vector2(float _x, float _y) : x(_x), y(_y) {}

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

		// Mainly used for debugging 
		friend std::ostream& operator<<(std::ostream& _lhs, const Vector2& _rhs)
		{
			_lhs << std::to_string(_rhs.x) << ", " << std::to_string(_rhs.y);
			return _lhs;
		}

		// Calculates the relationship between two vectors. I.e opposite vectors = -1
		static float dot(const Vector2& _lhs, const Vector2& _rhs);

		// Finds the magnitude from the vectors x,y coords
		static float magnitude(const Vector2& _rhs);

		// Normalizes a vector using it magnitude
		static Vector2 normalize(const Vector2& _rhs);

		// Setters
		void setX(float _x) { x = _x; }
		void setY(float _y) { y = _y; }

		// Getters
		const float& getX() const { return x; }
		const float& getY() const { return y; }

	private:
		float x = 0;
		float y = 0;
};
