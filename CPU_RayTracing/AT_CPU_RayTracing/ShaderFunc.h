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
		inline Vector3 getSmoothNormalFromTri(const Triangle triangle, const Raycast::hitData data)
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

		inline void fresnel(const Vector3& viewDir, const Vector3 normal, const float ior, float& kr)
		{
			float cosi = std::clamp(-1.0f, 1.0f, Vector3::dot(viewDir, normal));
			float etai = 1.0f;
			float etat = ior;
			if (cosi > 0.0f) std::swap(etai, etat);
			float sint = etai / etat * std::sqrtf(std::max(0.0f, 1.0f - cosi * cosi));
			if (sint >= 1.0f)
			{
				kr = 1.0f;
			}
			else
			{
				float cost = std::sqrtf(std::max(0.0f, 1.0f - sint * sint));
				cosi = std::fabsf(cosi);
				float rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
				float rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etai * cost));
				kr = (rs * rs + rp * rp) / 2.0f;
			}
		}
	}

	namespace Tonemapping
	{
		// https://frictionalgames.blogspot.com/2012/09/tech-feature-hdr-lightning.html
		// https://64.github.io/tonemapping/
		inline Colour uncharted2_tonemap_partial(Colour x)
		{
			float A = 0.15f;
			float B = 0.50f;
			float C = 0.10f;
			float D = 0.20f;
			float E = 0.02f;
			float F = 0.30f;
			return ((x * (A * x + C * B) + D * E) / (x * (A * x + B) + D * F)) - E / F;
		}

		// http://filmicworlds.com/blog/filmic-tonemapping-with-piecewise-power-curves/
		inline Colour hableTonemap(Colour v)
		{
			float exposure_bias = 2.0f;
			Colour curr = uncharted2_tonemap_partial(v * exposure_bias);

			Colour W = Colour(11.2f, 11.2f, 11.2f);
			Colour white_scale = Colour(1.0f, 1.0f, 1.0f) / uncharted2_tonemap_partial(W);
			return curr * white_scale;
		}
	}
}