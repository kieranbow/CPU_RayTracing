#include "Texture.h"
#include "ShaderFunc.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Includes\stb\stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Includes\stb\stb_image_write.h"

Texture::Texture(const char* filepath)
{
	// https://stackoverflow.com/questions/48235421/get-rgb-of-a-pixel-in-stb-image

	// Load the texture using stb
	unsigned char* data;
	data = stbi_load(filepath, &m_width, &m_height, &m_numChannel, 3);

	// Check if the data is valid and copy the contents to the vector of pixels.
	if (data)
	{
		for (int i = 0; i < m_reqChannel * m_width * m_height; i += m_reqChannel)
		{
			float colour_remap = 1.0f / 255.0f;
			Pixel temp;
			temp.colour = Colour(colour_remap * data[i], colour_remap * data[i + 1], colour_remap * data[i + 2]);
			m_data.push_back(temp);
		}
	}
	stbi_image_free(data);
}

Colour Texture::at(float u, float v)
{
	u = std::clamp(u, 0.0f, 1.0f);
	v = 1.0f - std::clamp(v, 0.0f, 1.0f);

	float i = u * static_cast<int>(m_width);
	float j = v * static_cast<int>(m_height);

	if (i >= m_width) i = m_width - 1.0f;
	if (j >= m_height) j = m_height - 1.0f;

	return m_data.at(j + i).colour;
}

void Texture::save(const char* filename, const std::vector<Pixel> data, const int width, const int height, const int numChannels)
{
	// https://stackoverflow.com/questions/61153680/how-to-use-stbi-write-png-to-write-image-pixel-data-to-a-png-file
	unsigned char* output = new unsigned char[width * height * numChannels];

	int index = 0;
	for (auto& pixel : data)
	{
		// Gamma correction
		Colour colour = Shaders::Functions::gammaCorrect(pixel.colour);

		output[index++] = static_cast<unsigned char>(255.0f * colour.getRed());
		output[index++] = static_cast<unsigned char>(255.0f * colour.getGreen());
		output[index++] = static_cast<unsigned char>(255.0f * colour.getBlue());
	}
	stbi_write_png(filename, width, height, numChannels, output, width * numChannels);
}
