#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include "Colour.h"

namespace RayTrace
{
	struct hitData
	{
		Colour colour	= { 0.0f, 0.0f, 0.0f };
		Vector3 normal	= { 0.0f, 0.0f, 0.0f };
		Vector2 uv		= { 0.0f, 0.0f };
	};

	class Ray
	{
		public:
			Ray() = default;
			Ray(Vector3 _position, Vector3 _direction) : origin(_position), direction(_direction) {}

			~Ray() = default;

			Vector3 origin = { 0.0f, 0.0f, 0.0f };
			Vector3 direction = { 0.0f, 0.0f, 0.0f };
			
			hitData data;

			float t = Maths::special::k_infinity;
			float t_near = 0.1f;
			float t_far = 1000.0f;
	};
}
