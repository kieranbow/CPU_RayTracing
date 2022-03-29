#pragma once
#include "Colour.h"
#include "Vector3.h"
#include "Matrix4x4.h"

// Contains all the classes and logic for lights
namespace Light
{
	// Base Light for different types of light to inherit
	// Contains generic information like intensity and colour
	class Light
	{
		public:
			Light(float intensity, Colour colour) 
				: m_intensity(intensity), m_colour(colour) {}
			~Light() = default;

			// Returns light information to parameters
			virtual void illuminate(Vector3& point, Vector3&, Colour&, float&) = 0;

			float m_intensity	= 1.0f;
			Colour m_colour		= { 1.0f, 1.0f, 1.0f };
	};

	// The directional light acts like the sun and only emits light in one direction
	class DirectionLight : public Light
	{
		public:
			DirectionLight(float intensity, Colour colour, Vector3 direction) 
				: Light(intensity, colour), m_direction(Vector3::normalize(direction)) {}

			void illuminate(Vector3& point, Vector3& direction, Colour& colour, float& distance)
			{
				// a * (1.0f - f)) + (b * f);
				direction = m_direction;

				auto lerp = [](Colour a, Colour b, float f)
				{
					float red	= a.getRed()	* (1.0f - f) + (b.getRed()	* f);
					float green = a.getGreen()	* (1.0f - f) + (b.getGreen() * f);
					float blue	= a.getBlue()	* (1.0f - f) + (b.getBlue()	* f);
					return Colour(red, green, blue);
				};

				colour = m_colour * m_intensity;  //lerp(m_sunset, m_colour, m_direction.getY());
				distance = Maths::special::infinity;
			}

		private:
			Vector3 m_direction;
			const Colour m_sunset = Colour(1.0f, 0.5f, 0.0f);
	};

	// A point light that emits light in all directions
	class PointLight : public Light
	{
		public:
			PointLight(float intensity, Colour colour, Vector3 position)
				: Light(intensity, colour), m_position(position) {}

			void illuminate(Vector3& point, Vector3& direction, Colour& colour, float& distance)
			{
				direction = point - m_position;
				float r2 = Vector3::distance(m_position, point);
				distance = std::sqrtf(r2);

				float x = direction.getX();
				float y = direction.getY();
				float z = direction.getZ();

				x /= distance;
				y /= distance;
				z /= distance;

				colour = m_colour * m_intensity / (4.0f * Maths::special::pi * r2);
			}
		private:
			Vector3 m_position;
	};
}
