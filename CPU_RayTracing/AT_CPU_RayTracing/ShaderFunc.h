#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include "Colour.h"
#include "MeshData.h"
#include "Ray.h"
#include "Maths.h"
#include "ShaderMaths.h"

namespace Shaders
{
	// This namespace contains a list of helper function for generating image effects
	namespace Functions
	{
		// Returns a smoothed normal from the triangle of a surface using Gouraud shading
		inline Vector3 getSmoothNormalFromTri(const Triangle triangle, const Raycast::hitData data)
		{
			return Vector3::normalize((1.0f - data.uv.getX() - data.uv.getY()) * triangle.vert0.normal + data.uv.getX() * triangle.vert1.normal + data.uv.getY() * triangle.vert2.normal);
		}

		// Returns a hard normal from the triangle of a surface
		inline Vector3 getHardNormalFromTri(Triangle triangle)
		{
			return Vector3::normalize(Vector3::cross(triangle.vert1.position - triangle.vert0.position, triangle.vert2.position - triangle.vert0.position));
		}

		// Returns a uv coordinate using the uvs generatered from Moller Trumbore and the meshes vertices texcoord
		inline Vector2 getUVCoords(const Vector2& uv, const Triangle& triangle)
		{
			return (1.0f - uv.getX() - uv.getY()) * triangle.vert0.texcoord + uv.getX() * triangle.vert1.texcoord + uv.getY() * triangle.vert2.texcoord;
		}

		// Returns a gamma correct colour
		inline Colour gammaCorrect(Colour colour)
		{
			Colour gammaCorrectColour = colour / (colour + 1.0f);
			gammaCorrectColour = Shaders::Math::power(gammaCorrectColour, 1.0f / 2.2f);
			return gammaCorrectColour;
		}

		inline void fresnel(const Vector3& viewDir, const Vector3 normal, const float ior, float& kr)
		{
			float cosi = std::clamp(Vector3::dot(viewDir, normal), -1.0f, 1.0f);
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

		inline Colour lambertCosineLaw(const float NdotL, Colour lightColour, Colour albedo)
		{
			return albedo * lightColour * NdotL;
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

	namespace BRDF
	{
		// Dinsey's remapping of roughness
		inline float disney_roughness(const float roughness)
		{
			return (roughness + 1.0f);
		}

		// A normal distribution function that distributes microfacets based of the surface's roughness
		inline float trowbridge_reitz_ggx(const float NdotH, const float roughness)
		{
			const float a = roughness * roughness;
			const float a2 = a * a;
			const float n_dot_h2 = NdotH * NdotH;

			const float num = a2;
			float de_nom = (n_dot_h2 * (a2 - 1.0f) + 1.0f);
			de_nom = Maths::special::pi * de_nom * de_nom;

			return num / de_nom;
		}

		inline float geometry_schlick_ggx(const float NdotV, const float roughness)
		{
			const float r = disney_roughness(roughness); // Disney modification to remap roughness to reduce roughness 'Hotness'
			const float k = r * r / 8.0f;

			const float num = NdotV;
			const float de_nom = NdotV * (1.0f - k) + k;

			return num / de_nom;
		}

		inline float geometry_smith(const float n_dot_v, const float n_dot_l, const float roughness)
		{
			const float ggx1 = geometry_schlick_ggx(n_dot_v, roughness);
			const float ggx2 = geometry_schlick_ggx(n_dot_l, roughness);

			return ggx1 * ggx2;
		}

		inline Colour fresnel_schlick(float NdotL, Colour f0, float f90) { return f0 + (f90 - f0) * std::powf(1.0f - NdotL, 5.0f); }

		// Evaluates the cook torrance BRDF to create the specular component of am objects surface
		inline Colour cookTorranceBRDF(const Colour f, const float d, const float g, const float NdotV, const float NdotL) { return (f * d * g) / (4.0f * NdotV * NdotL + 0.0001f); }
	}
}
