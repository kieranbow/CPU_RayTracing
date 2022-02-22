#pragma once
class Vector3;

// A class that defines a colour using rgba.
class Colour
{
	public:
		// Creates a default black colour
		Colour();

		// Custom colour
		Colour(float _red, float _green, float _blue);

		~Colour() = default;

		Colour operator=(const Colour& _rhs);

		Colour operator+(const Colour& _rhs);
		Colour operator+=(const Colour& _rhs);
		Colour operator-(const Colour& _rhs);
		Colour operator-=(const Colour& _rhs);
		Colour operator/(const Colour& _rhs);
		Colour operator/=(const Colour& _rhs);
		Colour operator*(const Colour& _rhs);
		Colour operator*=(const Colour& _rhs);

		// Setters
		void setColour(float _red, float _green, float _blue);
		void setColour(Colour colour);

		// Getters
		const float& getRed() const { return this->r; }
		const float& getGreen() const { return this->g; }
		const float& getBlue() const { return this->b; }

	private:
		float r = 0.0f; // Red
		float g = 0.0f; // Green
		float b = 0.0f; // Blue
};

