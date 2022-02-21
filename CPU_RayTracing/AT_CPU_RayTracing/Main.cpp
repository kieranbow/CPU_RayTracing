#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <fstream>

#include "Vector3.h"
#include "Ray.h"
#include "Colour.h"

struct Vector2
{
	float x;
	float y;
};

struct Viewport
{
	float width;
	float height;
	float aspect_ratio;

	const float& getViewportSize() const
	{
		return width * height;
	}
};

struct Pixel
{
	Colour colour;
	Vector3 pos;
};

constexpr float pi = 3.14159265358979323846f;

struct Matrix3x3
{
	// https://stackoverflow.com/questions/695043/how-does-one-convert-world-coordinates-to-camera-coordinates
	// https://en.wikipedia.org/wiki/Rotation_matrix#Basic_rotations
	// https://www.3dgep.com/understanding-the-view-matrix/
	// https://en.wikipedia.org/wiki/Euler_angles#Table_of_matrices
	// https://codereview.stackexchange.com/questions/144381/4x4-matrix-implementation-in-c
	// https://en.wikipedia.org/wiki/Camera_matrix

	Matrix3x3()
	{
		// Sets all elements of matrix to 0
		std::fill(m_elements.begin(), m_elements.end(), 0);

		// Change elements to create identity matrix
		this->m_elements[0] = 1; // 1, 0, 0
		this->m_elements[4] = 1; // 0, 1, 0
		this->m_elements[8] = 1; // 0, 0, 1
	}

	Matrix3x3 operator+(const Matrix3x3& _rhs)
	{
		for (int i = 0; i < 9; i++)
		{
			this->m_elements[i] + _rhs.m_elements[i];
		}
		return *this;
	}

	Matrix3x3 operator+=(const Matrix3x3& _rhs)
	{
		for (int i = 0; i < 9; i++)
		{
			this->m_elements[i] += _rhs.m_elements[i];
		}
		return *this;
	}

	std::array<int, 9> m_elements;

};

bool intersect(const Vector3 &origin, const Vector3 &dir, float &t)
{
	float t0 = 0.0f;
	float t1 = 0.0f;
	Vector3 centre = { 0.0f, 0.0f, -15.0f };
	float radius = 15.0f;
	float radius2 = radius * radius;

	Vector3 length = centre - origin;
	float tca = Vector3::dot(length, dir);

	if (tca < 0.0f) return false;

	float d2 = Vector3::dot(length, length) - tca * tca;

	if (d2 < radius2) return false;

	float thc = sqrtf(radius2 - d2);

	t0 = tca - thc;
	t1 = tca + thc;

	if (t0 > t1) std::swap(t0, t1);

	if (t0 < 0.0f)
	{
		t0 = t1;

		if (t0 < 0.0f) return false;
	}

	t = t0;

	return true;
}

int main()
{
	// https://github.com/iweinbau/Ray-Tracing/blob/master/Ray%20tracing/Utils/Camera.cpp
	// https://raytracing.github.io/books/RayTracingInOneWeekend.html#overview
	// https://www.scratchapixel.com/code.php?id=24&origin=/lessons/3d-basic-rendering/3d-viewing-pinhole-camera
	// https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix
	// https://gabrielgambetta.com/computer-graphics-from-scratch/02-basic-raytracing.html
	// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview
	// https://solarianprogrammer.com/2019/06/10/c-programming-reading-writing-images-stb_image-libraries/

	// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
	// https://codeclimber.net.nz/archive/2019/06/10/the-ray-tracer-challenge-drawing-to-a-canvas-and-saving-the-image-to-a-file/
	// http://www.realtimerendering.com/raytracing.html
	// https://link.springer.com/book/10.1007/978-1-4842-4427-2
	// https://codereview.stackexchange.com/questions/144381/4x4-matrix-implementation-in-c

	// Use stb_image for saving images

	// Right handed Cartesian coordinate systems
	// X+, y+, Z-

	Matrix3x3 test;

	// Image size
	Viewport canvas = { 640, 480 };

	// Viewport
	Viewport viewport;
	viewport.aspect_ratio	= canvas.width / canvas.height;
	viewport.height			= 2.0f;
	viewport.width			= viewport.aspect_ratio * viewport.height;
	

	// Camera
	Vector3 camera_position			= { 0.0f, 0.0f, 0.0f }; // World origin
	Vector3 camera_direction		= { 0.0f, 0.0f, -1.0f}; // Pointing Z-
	Vector3 camera_up				= { 0.0f, 1.0f, 0.0f }; // Pointing Y+
	Vector3 camera_alignment_vector = { 0.0f, 0.0f, 0.0f };
	
	float camera_length			= 1.0f; // focal length
	float camera_horizon_size	= 1.0f;
	float camera_aspect_ratio	= 1.0f; //image_size.width / image_size.height;
	float camera_fov = 90.0f;

	Vector3 camera_projection_u				= { 0.0f, 0.0f, 0.0f };
	Vector3 camera_projection_v				= { 0.0f, 0.0f, 0.0f };
	Vector3 camera_projection_screen_centre	= { 0.0f, 0.0f, 0.0f };

	Vector3 target = { 0.25f, 0.5f, -1.0f, };

	// Look at
	// camera_direction = Vector3::normalize((target - camera_position));

	// Calculate camera princple axis
	camera_alignment_vector = Vector3::normalize(camera_direction - camera_position);

	// Calculate Camrea UV position
	camera_projection_u = Vector3::normalize(Vector3::cross(camera_alignment_vector, camera_up));
	camera_projection_v = Vector3::normalize(Vector3::cross(camera_projection_u, camera_alignment_vector));

	// Calculate centre of screen position
	camera_projection_screen_centre = camera_position + (Vector3(camera_length, camera_length, camera_length) * camera_alignment_vector);

	// Change uv to match size and aspect ratio
	camera_projection_u *= Vector3(camera_horizon_size, camera_horizon_size, camera_horizon_size);
	const float size = camera_horizon_size / camera_aspect_ratio;
	camera_projection_v *= Vector3(size, size, size);

	// Create framebuffer and set it to black
	std::vector<Pixel> framebuffer;
	framebuffer.resize(static_cast<size_t>(canvas.width * canvas.height));
	std::fill(framebuffer.begin(), framebuffer.end(), Pixel());

	int x = 0;

	for (int height = 0; height < static_cast<int>(canvas.height); ++height)
	{
		for (int width = 0; width < static_cast<int>(canvas.width); ++width)
		{
			Pixel pixel;

			// Rasterizer space
			pixel.pos.x = static_cast<float>(width);
			pixel.pos.y = static_cast<float>(height);

			// Normalized Device Coords (NDC)
			Vector2 pixelNDC;
			pixelNDC.x = (pixel.pos.x + 0.5f) / canvas.width;
			pixelNDC.y = (pixel.pos.y + 0.5f) / canvas.height;

			// Screen space
			Vector2 pixel_screen;
			pixel_screen.x = 2.0f * pixelNDC.x - 1.0f; // normalizing to [-1, 1]
			pixel_screen.y = 1.0f - 2.0f * pixelNDC.y; // normalizing to [-1, 1]

			// Deg2rad
			float deg2rad = tan(camera_fov / 2.0f * pi / 180.0f);

			// Camera space
			Vector3 pixel_camera;
			pixel_camera.x = (2.0f - pixel_screen.x - 1.0f) * viewport.aspect_ratio * deg2rad;
			pixel_camera.y = (1.0f - 2.0f * pixel_screen.y) * deg2rad;

			Vector3 camera_space;
			camera_space.x = pixel_camera.x;
			camera_space.y = pixel_camera.y;
			camera_space.z = -1.0f;

			Ray primary_ray;
			primary_ray.position = camera_position;
			primary_ray.direction = Vector3::normalize(camera_space - primary_ray.position);

			float t = std::numeric_limits<float>::max();

			Colour test = Vector3(1.0f, 1.0f, 1.0f);

			Colour hit_colour = (primary_ray.direction + Vector3(1.0f, 1.0f, 1.0f)) * Vector3(0.5f, 0.5f, 0.5f);

			//if (intersect(primary_ray.position, primary_ray.direction, t))
			//{
			//	hit_colour = Vector3(0.0f, 0.0f, 0.0f);
			//}
			//else
			//{
			//	hit_colour = Vector3(1.0f, 0.0f, 0.0f);
			//}

			// write colour output to framebuffer
			framebuffer.at(x).colour.setColour(hit_colour);
			x++;
		}
	}

	// Create a file and write the contents of the framebuffer to the file
	std::ofstream file("Image.ppm");

	if (file.is_open())
	{
		file << "P3\n" << canvas.width << ' ' << canvas.height << "\n255\n";

		for(auto& pixel : framebuffer)
		{
			int ir = static_cast<int>(255.999 * pixel.colour.getRed());
			int ig = static_cast<int>(255.999 * pixel.colour.getGreen());
			int ib = static_cast<int>(255.999 * pixel.colour.getBlue());

			file << ir << ' ' << ig << ' ' << ib << '\n';
		}
		file.close();
	}
	framebuffer.clear();

	return 0;
}