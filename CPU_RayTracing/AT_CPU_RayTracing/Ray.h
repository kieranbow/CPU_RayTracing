#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include "Colour.h"
#include "MeshData.h"

namespace RayTrace
{
	// Generic data for when a ray hits a primitive
	struct hitData
	{
		Vector3 hitPoint	= { 0.0f, 0.0f, 0.0f };
		Colour colour		= { 0.0f, 0.0f, 0.0f };
		Vector3 normal		= { 0.0f, 0.0f, 0.0f };
		Vector2 uv			= { 0.0f, 0.0f };
	};

	class Ray
	{
		public:
			Ray() = default;
			Ray(Vector3 _position, Vector3 _direction) : m_origin(_position), m_direction(_direction) {}
			~Ray() = default;

			void setOrigin(Vector3 position) { m_origin = position; }
			void setDirection(Vector3 direction) { m_direction = direction; }
			void setT(float t) { m_t = t; }
			void setHitpoint(Ray& ray) { ray.m_origin = ray.m_origin + ray.m_direction * m_t; }
			void setHitData(Vector3 hitpoint, Colour colour, Vector3 normal, Vector2 uv) 
			{ m_data.hitPoint = hitpoint; m_data.colour = colour; m_data.normal = normal; m_data.uv = uv; }

			Vector3 getHitPoint() { return m_origin + m_direction * m_t; }
			Vector3& getOrigin() { return m_origin; }
			Vector3& getDirection() { return m_direction; }
			float& getT() { return m_t; }
			hitData& getHitData() { return m_data; }

		private:
			Vector3 m_origin	= { 0.0f, 0.0f, 0.0f };
			Vector3 m_direction	= { 0.0f, 0.0f, 0.0f };
			hitData m_data;

			float m_t		= Maths::special::infinity;
			float m_tNear	= -Maths::special::infinity; // 0.01f
			float m_tFar	= Maths::special::infinity; // 1000.0f
	};
}
