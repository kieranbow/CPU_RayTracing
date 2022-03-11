#pragma once

namespace Maths
{
	namespace special
	{
		constexpr float epsilon = 0.000001f; // A really really really small floating point
		constexpr float pi = 3.14159265358979323846f;
		constexpr float k_infinity = std::numeric_limits<float>::max();
	}
	namespace coord
	{
		// Enum to help identify major axis in code
		enum axis { x, y, z };
	}
}

