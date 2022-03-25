#pragma once
#include "Colour.h"
#include "Vector3.h"

namespace Material
{
	enum class Types
	{
		Dielectic, // Rough surfaces
		Phong,
		Reflective, // Mirrors
		Refractive, // Glass
		Reflective_and_refractive, // Mirros and Glass
		None
	};

	struct Data
	{
		Types type					= Types::None;
		Colour albedo				= { 1.0f, 1.0f, 1.0f };
		Vector3 normal				= { 0.0f, 0.0f, 1.0f };
		float specular_intensity	= 0.5f;
		float roughness				= 0.0f;
		float metallic				= 0.0f;
	};
}
