#pragma once
#include <random>

namespace Maths
{
	// This namespace contains a list of functions that randomize numbers
	namespace Random
	{
		// Returns a random float between [0, 1]
		inline float randomFloat()
		{
			static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
			static std::mt19937 generator;
			return distribution(generator);
		}

		// Returns a random number from min and max
		inline float randomFloatInRange(const float min, const float max)
		{
			static std::uniform_real_distribution<float> distribution(min, max);
			static std::mt19937 generator;
			return distribution(generator);
		}

		inline int randomInt()
		{
			static std::uniform_int_distribution<int> distribution(0, 1);
			static std::mt19937 generator;
			return distribution(generator);
		}

		inline int randomIntInRange(const int min, const int max)
		{
			static std::uniform_int_distribution<int> distribution(min, max);
			static std::mt19937 generator;
			return distribution(generator);
		}
	}
}