#pragma once
#include "Vector3.h"
#include "Colour.h"
#include "MeshData.h"
#include "Ray.h"

namespace Shaders
{
	// This namespace contains a list of helper function for generating image effects
	namespace Functions
	{
		// Returns a smoothed normal from the triangle of a surface
		inline Vector3 getSmoothNormalFromTri(const Triangle triangle, const RayTrace::hitData data)
		{
			return Vector3::normalize((1.0f - data.uv.getX() - data.uv.getY()) * triangle.vert0.normal + data.uv.getX() * triangle.vert1.normal + data.uv.getY() * triangle.vert2.normal);
		}

		// Returns a hard normal from the triangle of a surface
		inline Vector3 getHardNormalFromTri(Triangle triangle)
		{
			return Vector3::normalize(Vector3::cross(triangle.vert1.position - triangle.vert0.position, triangle.vert2.position - triangle.vert0.position));
		}

		// Returns a gamma correct colour
		inline Colour gammaCorrect(Colour colour)
		{
			return Colour(std::sqrtf(colour.getRed()), std::sqrtf(colour.getGreen()), std::sqrtf(colour.getBlue()));
		}
	}
}