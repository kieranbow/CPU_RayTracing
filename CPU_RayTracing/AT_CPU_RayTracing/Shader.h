#pragma once
#include "Colour.h"

namespace Shaders
{
	class Shader
	{
		public:
			Shader() = default;
			virtual ~Shader() = default;

			virtual Colour computeShader() = 0;
	};
}
