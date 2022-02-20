#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <fstream>

#include "Vector3.h"
#include "Ray.h"

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

struct Colour 
{
	float r;
	float g;
	float b;
	float a;
};

struct Pixel
{
	Colour colour;
	Vector3 pos;
};

constexpr float pi = 3.14159265358979323846f;

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
	// https://www.scratchapixel.com/code.php?id=7&origin=/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays
	// https://codeclimber.net.nz/archive/2019/06/10/the-ray-tracer-challenge-drawing-to-a-canvas-and-saving-the-image-to-a-file/
	// http://www.realtimerendering.com/raytracing.html
	// https://link.springer.com/book/10.1007/978-1-4842-4427-2
	// https://codereview.stackexchange.com/questions/144381/4x4-matrix-implementation-in-c

	// Use stb_image for saving images

	// Right handed Cartesian coordinate systems
	// X+, y+, Z-

	// Image size
	Viewport canvas = { 1920, 1080 };

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

	// Generate Rays from camera
	float screen_x = 1.0f;
	float screen_y = 1.0f;

	//Vector3 screenToWorld = camera_projection_screen_centre + (camera_projection_u * Vector3(screen_x, screen_x, static_cast<float>(i)));
	//Vector3 screenCoord = screenToWorld + (camera_projection_v * Vector3(screen_y, screen_y, static_cast<float>(j)));

	std::cout << "Centre position: " << camera_projection_screen_centre << std::endl;
	std::cout << "U position: " << camera_projection_u << std::endl;
	std::cout << "V position: " << camera_projection_v << std::endl;



	// Use Ray-sphere intersection to render sphere

	std::vector<Pixel> framebuffer;
	framebuffer.resize(static_cast<size_t>(canvas.width * canvas.height));

	std::ofstream file ("Image.ppm");

	if (file.is_open())
	{
		file << "P3\n" << canvas.width << ' ' << canvas.height << "\n255\n";

		for (int height = 0; height < static_cast<int>(canvas.height); ++height) // int height = static_cast<int>(canvas.height - 1.0f); height >= 0; --height
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

				Vector3 hit_colour = (primary_ray.direction + Vector3(1.0f, 1.0f, 1.0f)) * Vector3(0.5f, 0.5f, 0.5f);


				pixel.colour.r = hit_colour.x; //static_cast<float>(width) / (canvas.width - 1.0f);
				pixel.colour.g = hit_colour.y; //static_cast<float>(height) / (canvas.height - 1.0f);
				pixel.colour.b = hit_colour.z; //0.25f;

				int ir = static_cast<int>(255.999 * pixel.colour.r);
				int ig = static_cast<int>(255.999 * pixel.colour.g);
				int ib = static_cast<int>(255.999 * pixel.colour.b);

				file << ir << ' ' << ig << ' ' << ib << '\n';
			}
		}
		file.close();
	}
	return 0;
}