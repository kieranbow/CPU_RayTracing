#pragma once
#include "Colour.h"
#include "Vector3.h"

struct Material
{
	Colour albedo			= { 1.0f, 1.0f, 1.0f };
	Vector3 normal			= { 0.0f, 0.0f, 1.0f };
	float specular			= 0.5f;
	float roughness			= 0.0f;
	float metallic			= 0.0f;
	float ambientOcculsion	= 1.0f;
};

