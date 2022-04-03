#pragma once

struct Options
{
	int imageWidth		= 0; // Default 0
	int imageHeight		= 0; // Default 0
	int maxRayDepth		= 3; // Default 0
	float shadowBias	= 0.001f; // Default 0.001f
	int aaAmount		= 4; // Default 4
};
