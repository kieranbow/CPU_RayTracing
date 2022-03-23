#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <array>
#include <vector>

#include "Colour.h"
#include "Vector3.h"
#include "Pixel.h"

class Texture
{
	public:
		Texture() = default;
		Texture(const char* filepath);

		// Returns a pixel value from a given uv coordinate
		Colour at(float u, float v);

		void save(const char* filename, const std::vector<Pixel> data, const int width, const int height, const int numChannels);

		const int& getWidth() const { return m_width; }
		const int& getHeight() const { return m_height; }

	private:
		int m_width			= 0;
		int m_height		= 0;
		int m_numChannel	= 0; // Number of colour channels given by stb.
		int m_reqChannel	= 3; // Number of colour channels requested.

		std::vector<Pixel> m_data; // All the texture pixels are stored here.
};
