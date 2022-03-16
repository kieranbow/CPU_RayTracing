#pragma once
#include "Colour.h"

namespace Shaders
{
	struct pixelData
	{
		
	};

	class Shader
	{
		public:
			Shader() = default;
			virtual ~Shader() = default;

			virtual Colour pixelShader() = 0;
	};
}
