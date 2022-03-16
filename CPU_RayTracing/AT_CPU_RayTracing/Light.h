#pragma once
#include "Colour.h"
#include "Vector3.h"
#include "Matrix4x4.h"

namespace Light
{
	// A struct which contains generic data about a light
	struct LightData
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
				m_data.m_intensity = intensity;
				m_data.m_colour = colour;
				m_data.m_position = m_lightToMatrix.multVecByMatrix4x4(position);
			}
			~PointLight() = default;

		private:
			Matrix4x4 m_lightToMatrix;
			LightData m_data;
	};

	class DirectionLight
	{
		public:
			DirectionLight(const Matrix4x4& lightToWorld, float intensity, Colour colour, Vector3 direction)
			{
				m_lightToMatrix = lightToWorld;
				m_data.m_intensity = intensity;
				m_data.m_colour = colour;
				m_direction = m_lightToMatrix.multDirByMatrix4x4(Vector3(0.0f, 0.0f, 0.0f), direction);
			}
			~DirectionLight() = default;

			LightData m_data;

			Vector3 m_direction;
		private:
			Matrix4x4 m_lightToMatrix;

	};
}
