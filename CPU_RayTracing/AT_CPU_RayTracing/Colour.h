#pragma once
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
		

		// Getters
		const float& getRed() const { return this->r; }
		const float& getGreen() const { return this->g; }
		const float& getBlue() const { return this->b; }

	private:
		float r = 0.0f; // Red
		float g = 0.0f; // Green
		float b = 0.0f; // Blue
};

