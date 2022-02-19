#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "Vector3.h"
#include "Ray.h"

struct Vector2
{
	float x;
	float y;
};

struct Canvas
{
	float width;
	float height;
};

struct Pixel
{
	float r;
	float g;
	float b;
	float a;
};

int main()
{
	// https://github.com/iweinbau/Ray-Tracing/blob/master/Ray%20tracing/Utils/Camera.cpp
	// https://raytracing.github.io/books/RayTracingInOneWeekend.html#overview
	// https://www.scratchapixel.com/code.php?id=24&origin=/lessons/3d-basic-rendering/3d-viewing-pinhole-camera
	// https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix
	// https://gabrielgambetta.com/computer-graphics-from-scratch/02-basic-raytracing.html
	// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview
	// https://solarianprogrammer.com/2019/06/10/c-programming-reading-writing-images-stb_image-libraries/

	// Use stb_image for saving images

	// Right handed Cartesian coordinate systems
	// X+, y+, Z-

	// Image
	Canvas image_size = { 640, 480 };

	// Canvas
	std::vector<Pixel> pixels;

	// Camera
	Vector3 camera_position		= { 0.0f, 0.0f, 0.0f }; // World origin
	Vector3 camera_direction	= { 0.0f, 0.0f, -1.0f }; // Pointing Z-
	Vector3 camera_up			= { 0.0f, 1.0f, 0.0f }; // Pointing Y+
	Vector3 camera_right		= Vector3::cross(camera_direction, camera_up);
	Vector3 camera_principle_axis = { 0.0f, 0.0f, 0.0f };
	
	float camera_length			= 1.0f;
	float camera_horizon_size	= 1.0f;
	float camera_aspect_ratio	= 1.0f;

	Vector3 camera_u				= { 0.0f, 0.0f, 0.0f };
	Vector3 camera_v				= { 0.0f, 0.0f, 0.0f };
	Vector3 camera_screen_centre	= { 0.0f, 0.0f, 0.0f };

	Vector3 target = { 0.25f, 0.5f, -1.0f, };

	// Look at
	// camera_direction = Vector3::normalize((target - camera_position));

	// Calculate camera princple axis
	camera_principle_axis = Vector3::normalize(camera_direction - camera_position);

	// Calculate Camrea UV position
	camera_u = Vector3::normalize(Vector3::cross(camera_principle_axis, camera_up));
	camera_v = Vector3::normalize(Vector3::cross(camera_u, camera_principle_axis));

	// Calculate centre of screen position
	camera_screen_centre = camera_position + (Vector3(camera_length, camera_length, camera_length) * camera_principle_axis);

	// Change uv to match aspect ratio
	camera_u *= Vector3(camera_horizon_size, camera_horizon_size, camera_horizon_size);
	const float size = camera_horizon_size / camera_aspect_ratio;
	camera_v *= Vector3(size, size, size);

	std::cout << "Centre position: " << camera_screen_centre << std::endl;
	std::cout << "U position: " << camera_u << std::endl;
	std::cout << "V position: " << camera_v << std::endl;

	// Generate Rays from camera


	// Use Ray-sphere intersection to render sphere

	std::ofstream file ("Image.ppm");

	if (file.is_open())
	{
		file << "P3\n" << image_size.width << ' ' << image_size.height << "\n255\n";
		// Save pixels into image
		for (int i = image_size.height - 1.0f; i >= 0; --i)
		{
			for (int j = 0; j < image_size.width; ++j)
			{
				Pixel pixel;
				pixel.r = static_cast<float>(j) / (image_size.width - 1.0f);
				pixel.g = static_cast<float>(i) / (image_size.height - 1.0f);
				pixel.b = 0.25f;

				int ir = static_cast<int>(255.999 * pixel.r);
				int ig = static_cast<int>(255.999 * pixel.g);
				int ib = static_cast<int>(255.999 * pixel.b);

				file << ir << ' ' << ig << ' ' << ib << '\n';
			}
		}
		file.close();
	}
	return 0;
}