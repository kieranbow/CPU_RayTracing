#pragma once
#include <array>

class Vector3;

// A class that defines a colour using rgb.
class Colour
{
	public:
		// Creates a default black colour
		Colour();

		// Custom colour
		Colour(float _red, float _green, float _blue);
		Colour(Vector3& _rhs);

		~Colour() = default;

		// Assignment Operators
		Colour& operator=(const Colour& _rhs);
		Colour operator+=(const Colour& _rhs);
		Colour operator-=(const Colour& _rhs);
		Colour operator/=(const Colour& _rhs);
		Colour operator*=(const Colour& _rhs);

		// Vector3 Assignment Operators
		Colour& operator=(const Vector3& _rhs);
		Colour operator+=(const Vector3& _rhs);
		Colour operator-=(const Vector3& _rhs);
		Colour operator/=(const Vector3& _rhs);
		Colour operator*=(const Vector3& _rhs);

		// Float assigment Operator
		Colour& operator=(const float& _rhs);
		Colour operator+=(const float& _rhs);
		Colour operator-=(const float& _rhs);
		Colour operator/=(const float& _rhs);
		Colour operator*=(const float& _rhs);

		// Arithmetic Operators
		Colour operator+(const Colour& _rhs);
		Colour operator-(const Colour& _rhs);
		Colour operator/(const Colour& _rhs);
		Colour operator*(const Colour& _rhs);
		Colour operator+(const float& _rhs);
		Colour operator-(const float& _rhs);
		Colour operator/(const float& _rhs);
		Colour operator*(const float& _rhs);

		// Relational Operators
		bool operator>(const Colour& _rhs);
		bool operator<(const Colour& _rhs);
		bool operator>=(const Colour& _rhs);
		bool operator<=(const Colour& _rhs);
		bool operator==(const Colour& _rhs);
		bool operator!=(const Colour& _rhs);
		
		// Friend Operators
		friend Colour operator+(const float& _lhs, const Colour& _rhs);
		friend Colour operator-(const float& _lhs, const Colour& _rhs);
		friend Colour operator*(const float& _lhs, const Colour& _rhs);
		friend Colour operator/(const float& _lhs, const Colour& _rhs);

		friend Colour operator/(const Colour& _lhs, const float& _rhs);
		friend Colour operator*(const Colour& _lhs, const float& _rhs);

		friend Colour operator/=(Colour& _lhs, const float& _rhs);

		// Getters
		const float& getRed() const { return this->colour.at(0); }
		const float& getGreen() const { return this->colour.at(1); }
		const float& getBlue() const { return this->colour.at(2); }
		const std::array<float, 3>& getColour() const { return colour; }

	private:
		std::array<float, 3> colour;
};
