#pragma once
#include <algorithm>
#include <cmath>

#include "Vector2.h"
#include "Vector3.h"

namespace Shaders 
{
	// Namespace which contain a list of functions which emulate function within hlsl.
	// Each function acts as a wrapper around standard c++ maths function.
	// Hlsl function can be found here : https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-intrinsic-functions
	namespace Maths
	{
		// Returns the absolute value from input
		template<typename T>
		T abs(T) { return std::abs(T); }

		// Converts input to float
		inline float asfloat(int x) { return static_cast<float>(x); }

		// Convert input to int
		inline int asint(float x) { return static_cast<int>(x); }

		// Returns the max number from x and y
		inline float max(float x, float y) { return std::max(x, y); }

		// Returns the lowest value from x and y
		inline float min(float x, float y) { return std::min(x, y); }

		// Returns the smallest float which is greater than or equal to x
		inline float ceil(float x) { return std::ceilf(x); }

		// Returns the greatest float which is less than or equal to x
		inline float floor(float x) { return std::floorf(x); }

		// Clamps x between min and max
		inline float clamp(float x, float min, float max) { return std::clamp(x, min, max); }

		// Returns the cosine of x
		inline float cos(float x) { return std::cosf(x); }

		// Returns the distance between two points
		inline float distance(Vector3 a, Vector3 b) { return Vector3::distance(a, b); }
		inline float distance(Vector2 a, Vector2 b);

		// Returns the dot product of two vectors
		inline float dot(Vector3 a, Vector3 b) { return Vector3::dot(a, b); }
		inline float dot(Vector2 a, Vector2 b) { return Vector2::dot(a, b); }

		// Returns the base-e exponent
		inline float exp(float x) { return std::expf(x); }

		// Base 2 exponent (per component)
		template<typename T>
		inline T exp2(T x) 
		{ 
			static_assert(!std::is_floating_point<T>::value, "Cannot use type here. Expected Vector2, Vector3 or float");
			return std::exp2f(x); 
		}

		inline float lerp(float a, float b, float f) { return (a * (1.0f - f)) + (b * f); }

		inline float length();

		// Square root(per component)
		inline float sqrt(float x) { return std::sqrtf(x); }

		// Returns the sin of x
		inline float sin(float x) { return std::sinf(x); }

		// Returns the tangent of x
		inline float tan(float x) { return std::tanf(x); }

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

		// Returns the specified value raised to the specified power
		inline float pow(float x, float y) { return std::powf(x, y); }
		inline Vector3 pow(Vector3 x, Vector3 y) { return Vector3(std::powf(x.getX(), y.getX()), std::powf(x.getY(), y.getY()), std::powf(x.getZ(), y.getZ())); }
	}
}