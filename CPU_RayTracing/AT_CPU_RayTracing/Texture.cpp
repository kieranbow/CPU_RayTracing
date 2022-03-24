#include "Texture.h"
#include "ShaderFunc.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Includes\stb\stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Includes\stb\stb_image_write.h"

Texture::~Texture()
{
	stbi_image_free(m_data);
	delete m_data;
}

Texture::Texture(const Texture& texture) 
	: m_width(texture.m_width), m_height(texture.m_height), m_numChannel(texture.m_numChannel), m_reqChannel(texture.m_reqChannel)
{
	if (texture.m_data != nullptr)
	{
		delete[] m_data;

		m_data = new unsigned char[m_width * m_height * m_numChannel];

		for (int i = 0; i < m_width * m_height * m_numChannel; i++)
		{
			m_data[i] = texture.m_data[i];
		}
	}
	else
	{
		m_data = nullptr;
	}
}

Colour Texture::at(Vector2 uv)
{
	//uv.setX(std::clamp(uv.getX(), 0.0f, 1.0f));
	//uv.setY(1.0f - std::clamp(uv.getY(), 0.0f, 1.0f));

	//float i = uv.getX() * static_cast<int>(m_width);
	//float j = uv.getY() * static_cast<int>(m_height);

	//if (i >= m_width) i = static_cast<float>(m_width - 1);
	//if (j >= m_height) j = static_cast<float>(m_height - 1);

	//return m_data.at(uv.getX() + m_width * uv.getY()).colour;

	if (m_data == nullptr) return Colour(1.0f, 0.0f, 1.0f);

	uv.setX(std::clamp(uv.getX(), 0.0f, 1.0f));
	uv.setY(1.0f - std::clamp(uv.getY(), 0.0f, 1.0f));

	int i = static_cast<int>(uv.getX() * m_width);
	int j = static_cast<int>(uv.getY() * m_height);

	if (i >= m_width) i = m_width - 1;
	if (j >= m_height) j = m_height - 1;

	auto pixel = m_data + j * bytesPerScanline + i * 3;

	float colour_remap = 1.0f / 255.0f;

	return Colour(colour_remap * pixel[0], colour_remap * pixel[1], colour_remap * pixel[2]);
}

bool Texture::load(const char* filepath)
{
	// https://stackoverflow.com/questions/48235421/get-rgb-of-a-pixel-in-stb-image

	m_data = stbi_load(filepath, &m_width, &m_height, &m_numChannel, m_reqChannel);

	bytesPerScanline = 3 * m_width;

	if (!m_data) return false;
	return true;

	// Load the texture using stb
	//unsigned char* data;
	//data = stbi_load(filepath, &m_width, &m_height, &m_numChannel, m_reqChannel);

	//if (!data) return false;

	//// Check if the data is valid and copy the contents to the vector of pixels.
	//if (data)
	//{
	//	for (int i = 0; i < m_reqChannel * m_width * m_height; i += m_reqChannel)
	//	{
	//		// Copies the pixel content from the file to the vector and remaps it to 0-1.
	//		float colour_remap = 1.0f / 255.0f;
	//		Pixel temp;
	//		temp.colour = Colour(colour_remap * data[i], colour_remap * data[i + 1], colour_remap * data[i + 2]);
	//		m_data.push_back(temp);
	//	}
	//}

	//m_data.resize((m_width * m_height) / 2);

	//for (int y = 0; y < m_height; y++)
	//{
	//	for (int x = 0; x < m_width; x++)
	//	{
	//		int i = y * (3 * m_width) + x * 3;

	//		// Copies the pixel content from the file to the vector and remaps it to 0-1.
	//		float colour_remap = 1.0f / 255.0f;
	//		Pixel temp;
	//		temp.colour = Colour(colour_remap * data[i], colour_remap * data[i + 1], colour_remap * data[i + 2]);
	//		m_data.at(x).push_back(temp);
	//	}

	//}



	// Clear the loaded data
	//stbi_image_free(data);
	//return true;
}

void Texture::savePNG(const char* filename, const std::vector<Pixel> data, const int width, const int height, const int numChannels)
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
	// Write output data into PNG file
	stbi_write_png(filename, width, height, numChannels, output, width * numChannels);

	// Clear output data
	delete[] output;
}
