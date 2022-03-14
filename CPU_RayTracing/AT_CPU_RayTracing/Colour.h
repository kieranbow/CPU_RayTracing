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

		// Arithmetic Operators
		Colour operator+(const Colour& _rhs);
		Colour operator-(const Colour& _rhs);
		Colour operator/(const Colour& _rhs);
		Colour operator*(const Colour& _rhs);

		Colour operator+(const Vector3& _rhs);
		Colour operator-(const Vector3& _rhs);
		Colour operator/(const Vector3& _rhs);
		Colour operator*(const Vector3& _rhs);

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

		// Getters
		const float& getRed() const { return this->m_colour.at(0); }
		const float& getGreen() const { return this->m_colour.at(1); }
		const float& getBlue() const { return this->m_colour.at(2); }
		const std::array<float, 3>& getColour() const { return m_colour; }

	private:
		std::array<float, 3> m_colour;
};
