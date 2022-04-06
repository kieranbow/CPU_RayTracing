#include "Texture.h"
#include "ShaderFunc.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Includes\stb\stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Includes\stb\stb_image_write.h"

Colour Texture::at(Vector2 uv)
{
	// Return pink if no texture exist
	if (m_texture.empty()) return Colour(1.0f, 0.0f, 1.0f);

	uv.setX(std::clamp(uv.getX(), 0.0f, 1.0f));
	uv.setY(1.0f - std::clamp(uv.getY(), 0.0f, 1.0f));

	size_t i = static_cast<size_t>(uv.getX() * m_width);
	size_t j = static_cast<size_t>(uv.getY() * m_height);

	if (i >= m_width) i = m_width - 1;
	if (j >= m_height) j = m_height - 1;

	return m_texture.at(j * m_width + i);
}

bool Texture::load(const char* filepath)
{
	// https://stackoverflow.com/questions/48235421/get-rgb-of-a-pixel-in-stb-image
	// Load the texture using stb
	unsigned char* data;
	data = stbi_load(filepath, &m_width, &m_height, &m_numChannel, m_reqChannel);

	if (!data) return false;

	// Check if the data is valid and copy the contents to the vector of pixels.
	if (data)
	{
		for (int i = 0; i < m_reqChannel * m_width * m_height; i += m_reqChannel)
		{
			// Copies the pixel content from the file to the vector and remaps it to 0-1.
			float colour_remap = 1.0f / 255.0f;
			Colour temp;
			temp = Colour(colour_remap * data[i], colour_remap * data[i + 1], colour_remap * data[i + 2]);
			m_texture.push_back(temp);
		}
	}

	// Clear the loaded data
	stbi_image_free(data);
	return true;
}

void Texture::savePNG(const char* filename, const std::vector<Pixel>& data, const int width, const int height, const int numChannels)
{
	// https://stackoverflow.com/questions/61153680/how-to-use-stbi-write-png-to-write-image-pixel-data-to-a-png-file
	unsigned char* outputBuffer = new unsigned char[width * height * numChannels];

	size_t index = 0;
	for (auto& pixel : data)
	{
		// Gamma correction
		Colour colour = Shaders::Functions::gammaCorrect(pixel.colour);

		// Convert colour from [0, 1] to [0, 255] and assign colour values to outputBuffer
		outputBuffer[index++] = static_cast<unsigned char>(255.0f * colour.getRed());
		outputBuffer[index++] = static_cast<unsigned char>(255.0f * colour.getGreen());
		outputBuffer[index++] = static_cast<unsigned char>(255.0f * colour.getBlue());
	}
	// Write output data into PNG file
	stbi_write_png(filename, width, height, numChannels, outputBuffer, width * numChannels);

	// Clear output data
	delete[] outputBuffer;
}
