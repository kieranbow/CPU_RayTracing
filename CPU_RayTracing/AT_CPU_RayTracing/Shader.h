#pragma once
#include "Colour.h"

namespace Shaders
{
	class Shader
	{
		public:
			Shader() = default;
			virtual ~Shader() = default;

			virtual Colour computeShader(Vector3&, Vector3&, Colour&, Vector3&) = 0;
	};


	class PBR : public Shader
	{
		public:
			Colour computeShader(Vector3& normal, Vector3& lightDirection, Colour& lightColour, Vector3& viewDirection)
			{
				return Colour();
			}
	};

	class Unlit : public Shader
	{
		public:
			Colour computeShader(Vector3&, Vector3&, Colour& lightColour, Vector3&)
			{
				return Colour();
			}
	};

}
