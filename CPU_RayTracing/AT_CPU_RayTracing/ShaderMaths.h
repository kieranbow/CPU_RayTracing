#pragma once
#include <algorithm>
#include <cmath>

#include "Vector2.h"
#include "Vector3.h"
#include "Colour.h"

namespace Shaders 
{
	// Namespace which contain a list of functions which emulate functions within hlsl.
	// Each function acts as a wrapper around standard c++ maths function.
	// Hlsl function can be found here: 
	// https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-intrinsic-functions
	// https://developer.download.nvidia.com/cg/index_stdlib.html
	namespace Maths
	{
		// Returns the absolute value from input
		inline float abs(float x) { return std::abs(x); }
		inline Vector2 abs(Vector2 x) { return Vector2(std::abs(x.getX()), std::abs(x.getY())); }
		inline Vector3 abs(Vector3 x) { return Vector3(std::abs(x.getX()), std::abs(x.getY()), std::abs(x.getZ())); }

		// Converts input to float
		inline float asfloat(int x) { return static_cast<float>(x); }

		// Convert input to integer
		inline int asint(float x) { return static_cast<int>(x); }

		// Returns the smallest float which is greater than or equal to x
		inline float ceil(float x) { return std::ceilf(x); }
		inline Vector2 ceil(Vector2 x) { return Vector2(std::ceilf(x.getX()), std::ceilf(x.getY())); }
		inline Vector3 ceil(Vector3 x) { return Vector3(std::ceilf(x.getX()), std::ceilf(x.getY()), std::ceilf(x.getZ())); }

		// Clamps x between min and max
		inline float clamp(float x, float min, float max) { return std::clamp(x, min, max); }

		// Returns the cosine of x
		inline float cos(float x) { return std::cosf(x); }
		inline Vector2 cos(Vector2 x) { return Vector2(std::cos(x.getX()), std::cos(x.getY())); }
		inline Vector3 cos(Vector3 x) { return Vector3(std::cos(x.getX()), std::cos(x.getY()), std::cos(x.getZ())); }

		// Returns the distance between two points
		inline float distance(Vector3 a, Vector3 b) { return Vector3::distance(a, b); }
		// inline float distance(Vector2 a, Vector2 b);

		// Returns the dot product of two vectors
		inline float dot(Vector3 a, Vector3 b) { return Vector3::dot(a, b); }
		inline float dot(Vector2 a, Vector2 b) { return Vector2::dot(a, b); }

		// Returns the base-e exponent
		inline float exp(float x) { return std::expf(x); }
		inline Vector2 exp(Vector2 x) { return Vector2(std::expf(x.getX()), std::expf(x.getY())); }
		inline Vector3 exp(Vector3 x) { return Vector3(std::expf(x.getX()), std::expf(x.getY()), std::expf(x.getZ())); }

		// Base 2 exponent (per component)
		inline float exp2(float x) {return std::exp2f(x); }
		inline Vector2 exp2(Vector2 x) { return Vector2(std::exp2f(x.getX()), std::exp2f(x.getY())); }
		inline Vector3 exp2(Vector3 x) { return Vector3(std::exp2f(x.getX()), std::exp2f(x.getY()), std::expf(x.getZ())); }

		// Returns the greatest float which is less than or equal to x
		inline float floor(float x) { return std::floorf(x); }
		inline Vector2 floor(Vector2 x) { return Vector2(std::floorf(x.getX()), std::floorf(x.getY())); }
		inline Vector3 floor(Vector3 x) { return Vector3(std::floorf(x.getX()), std::floorf(x.getY()), std::floorf(x.getZ())); }

		// Returns the fractional portion of a scalar or each vector component.
		inline float frac(float x) { return x - std::floorf(x); }
		inline Vector2 frac(Vector2 x) { return Vector2(x.getX() - std::floorf(x.getX()), x.getY() - std::floorf(x.getY())); }
		inline Vector3 frac(Vector3 x) { return Vector3(std::abs(x.getX()), std::abs(x.getY()), std::abs(x.getZ())); }

		inline float lerp(float a, float b, float f) { return (a * (1.0f - f)) + (b * f); }
		//inline Vector2 lerp(Vector2 a, Vector2 b, float f) { return (a * (1.0f - f)) + (b * f); }
		inline Vector3 lerp(Vector3 a, Vector3 b, float f) { return (a * (1.0f - f)) + (b * f); }

		inline float length(Vector3 x) { return Vector3::length(x); }

		inline Vector2 normalize(Vector2 x) { return Vector2::normalize(x); }
		inline Vector3 normalize(Vector3 x) { return Vector3::normalize(x); }

		// Returns the max number from x and y
		inline float max(float x, float y) { return std::max(x, y); }
		inline Vector2 max(Vector2 x, Vector2 y) { return Vector2(std::max(x.getX(), y.getX()), std::max(x.getY(), y.getY())); }
		inline Vector3 max(Vector3 x, Vector3 y) { return Vector3(std::max(x.getX(), y.getX()), std::max(x.getY(), y.getY()), std::max(x.getZ(), y.getZ())); }

		// Returns the lowest value from x and y
		inline float min(float x, float y) { return std::min(x, y); }
		inline Vector2 max(Vector2 x, Vector2 y) { return Vector2(std::min(x.getX(), y.getX()), std::min(x.getY(), y.getY())); }
		inline Vector3 max(Vector3 x, Vector3 y) { return Vector3(std::min(x.getX(), y.getX()), std::min(x.getY(), y.getY()), std::min(x.getZ(), y.getZ())); }

		// Returns the specified value raised to the specified power
		inline float pow(float x, float y) { return std::powf(x, y); }
		inline Vector2 pow(Vector2 x, Vector2 y) { return Vector2(std::powf(x.getX(), y.getX()), std::powf(x.getY(), y.getY())); }
		inline Vector3 pow(Vector3 x, Vector3 y) { return Vector3(std::powf(x.getX(), y.getX()), std::powf(x.getY(), y.getY()), std::powf(x.getZ(), y.getZ())); }

		// Returns the reflection vector using an incident ray and a surface normal
		inline Vector3 reflect(Vector3 i, Vector3 n) { return i - 2.0f * Vector3::dot(i, n) * n; }

		// Returns the refraction vector
		inline Vector3 refract(Vector3 i, Vector3 n, float ior)
		{
			// https://asawicki.info/news_1301_reflect_and_refract_functions.html
			float NdotI = Vector3::dot(n, i);
			float k = 1.0f - ior * ior * (1.0f - NdotI * NdotI);
			return k < 0.1f ? Vector3(0.0f, 0.0f, 0.0f) : ior * i - (ior * NdotI + std::sqrtf(k)) * n;
		}

		// Returns the square root of x or per component
		inline float sqrt(float x) { return std::sqrtf(x); }
		inline Vector2 sqrt(Vector2 x) { return Vector2(std::sqrt(x.getX()), std::sqrt(x.getY())); }
		inline Vector3 sqrt(Vector3 x) { return Vector3(std::sqrt(x.getX()), std::sqrt(x.getY()), std::sqrt(x.getZ())); }

		// Returns the sin of x
		inline float sin(float x) { return std::sinf(x); }
		inline Vector2 sin(Vector2 x) { return Vector2(std::sinf(x.getX()), std::sinf(x.getY())); }
		inline Vector3 sin(Vector3 x) { return Vector3(std::sinf(x.getX()), std::sinf(x.getY()), std::sinf(x.getZ())); }

		// Returns the tangent of x
		inline float tan(float x) { return std::tanf(x); }
		inline Vector2 tan(Vector2 x) { return Vector2(std::tanf(x.getX()), std::tanf(x.getY())); }
		inline Vector3 tan(Vector3 x) { return Vector3(std::tanf(x.getX()), std::tanf(x.getY()), std::tanf(x.getZ())); }
	}
}
