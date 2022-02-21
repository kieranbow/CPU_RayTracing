#pragma once

class Colour
{
	public:
		// Creates a default black colour
		Colour();

		// Custom colour
		Colour(float _red, float _green, float _blue, float _alpha);

		Colour operator+(const Colour& _rhs);
		Colour operator+=(const Colour& _rhs);
		Colour operator-(const Colour& _rhs);
		Colour operator-=(const Colour& _rhs);
		Colour operator/(const Colour& _rhs);
		Colour operator/=(const Colour& _rhs);
		Colour operator*(const Colour& _rhs);
		Colour operator*=(const Colour& _rhs);

		// Setters

		void setColour(float _red, float _green, float _blue, float _alpha);

		// Getters

		const float& getRed() const { return this->r; }
		const float& getGreen() const { return this->g; }
		const float& getBlue() const { return this->b; }
		const float& getAlpha() const { return this->a; }

	private:
		float r = 0.0f; // Red
		float g = 0.0f; // Green
		float b = 0.0f; // Blue
		float a = 0.0f; // Alpha
};

