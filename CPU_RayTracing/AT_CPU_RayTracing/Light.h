#pragma once
#include "Colour.h"
#include "Vector3.h"
#include "Matrix4x4.h"

namespace Light
{
	// A struct which contains generic data about a light
	struct LightPropertices
	{
		float intensity = 1.0f;
		Colour colour = { 1.0f, 1.0f, 1.0f };
		Vector3 m_position = { 0.0f, 0.0f, 0.0f };
	};

	class PointLight
	{
		public:
			PointLight(float intensity, Colour colour, Vector3 m_position)
			{
				m_propertices.intensity = intensity;
				m_propertices.colour = colour;
				m_propertices.m_position = m_position;
			}
			~PointLight() = default;

			void getDirection(Vector3 point) 
			{ 
				Vector3 lightDir = Vector3::normalize(m_propertices.m_position - point);
				float r2 = Vector3::distance(m_propertices.m_position, point);

				// m_propertices.intensity = m_propertices.intensity * m_propertices.colour / (4.0f * Maths::special::pi * r2);
			}

		private:
			LightPropertices m_propertices;
	};

	class DirectionLight
	{
		public:
			DirectionLight() = default;
			DirectionLight(float intensity, Colour colour, Vector3 direction)
			{
				m_propertices.intensity = intensity;
				m_propertices.colour = colour;
				m_propertices.m_position = direction;
			}
			~DirectionLight() = default;

			void setIntensity(float intensity) { m_propertices.intensity = intensity; }
			void setColour(Colour colour) { m_propertices.colour = colour; }
			void setDirection(Vector3 direction) { m_propertices.m_position = direction; }
			void setPropertices(LightPropertices propertices) { m_propertices = propertices; }

			const float& getIntensity() const { return m_propertices.intensity; }
			const Colour& getColour() const { return m_propertices.colour; }
			const Vector3& getDirection() const { return m_propertices.m_position; }
			const LightPropertices& getPropertices() const { return m_propertices; }

		private:
			LightPropertices m_propertices;
	};
}
