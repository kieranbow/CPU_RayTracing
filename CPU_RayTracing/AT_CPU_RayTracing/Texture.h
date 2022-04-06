#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

#include "Colour.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Pixel.h"

class Texture
{
	public:
		Texture() = default;
		~Texture() = default;

		// Returns a pixel value from a given uv coordinate
		Colour at(Vector2 uv);

		// Checks if the image is empty
		bool empty() { return m_texture.empty(); }

		// Loads the texture using stb from filepath
		bool load(const char* filepath);

		// Saves the contents of a vector of pixels to a png file
		void savePNG(const char* filename, const std::vector<Pixel>& data, const int width, const int height, const int numChannels);

		const int& getWidth() const { return m_width; }
		const int& getHeight() const { return m_height; }

	private:
		int m_width				= 0; // Width of the image
		int m_height			= 0; // Height of the image
		int m_numChannel		= 0; // Number of colour channels given by stb.
		int m_reqChannel		= 3; // Number of colour channels requested.
		std::vector<Colour> m_texture; // Buffer of pixels
};
