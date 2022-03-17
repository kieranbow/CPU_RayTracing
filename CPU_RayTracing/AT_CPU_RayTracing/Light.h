#pragma once
#include "Colour.h"
#include "Vector3.h"
#include "Matrix4x4.h"

namespace Light
{
	// A struct which contains generic data about a light
	struct LightPropertices
	{
		float m_intensity = 1.0f;
		Colour m_colour = { 1.0f, 1.0f, 1.0f };
		Vector3 m_position = { 0.0f, 0.0f, 0.0f };
	};

	class PointLight
	{
		public:
			PointLight(const Matrix4x4& lightToWorld, float intensity, Colour colour, Vector3 position)
			{
				m_lightToMatrix = lightToWorld;
				m_propertices.m_intensity = intensity;
				m_propertices.m_colour = colour;
				m_propertices.m_position = m_lightToMatrix.multVecByMatrix4x4(position);
			}
			~PointLight() = default;

		private:
			Matrix4x4 m_lightToMatrix;
			LightPropertices m_propertices;
	};

	class DirectionLight
	{
		public:
			DirectionLight(float intensity, Colour colour, Vector3 m_direction)
			{
				m_propertices.m_intensity = intensity;
				m_propertices.m_colour = colour;
				m_direction = m_direction;
			}
			~DirectionLight() = default;

			void setIntensity(float intensity) { m_propertices.m_intensity = intensity; }
			void setColour(Colour colour) { m_propertices.m_colour = colour; }
			void setDirection(Vector3 direction) { m_direction = direction; }
			void setPropertices(LightPropertices propertices) { m_propertices = propertices; }

			const float& getIntensity() const { return m_propertices.m_intensity; }
			const Colour& getColour() const { return m_propertices.m_colour; }
			const Vector3& getDirection() const { return m_direction; }
			const LightPropertices& getPropertices() const { return m_propertices; }

		private:
			Vector3 m_direction;
			LightPropertices m_propertices;
	};
}
