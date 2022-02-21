#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <fstream>

#include "Vector3.h"
#include "Vector2.h"

#include "Ray.h"

#include "Colour.h"
#include "Pixel.h"

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

// https://stackoverflow.com/questions/695043/how-does-one-convert-world-coordinates-to-camera-coordinates
// https://en.wikipedia.org/wiki/Rotation_matrix#Basic_rotations
// https://www.3dgep.com/understanding-the-view-matrix/
// https://en.wikipedia.org/wiki/Euler_angles#Table_of_matrices
// https://codereview.stackexchange.com/questions/144381/4x4-matrix-implementation-in-c
// https://en.wikipedia.org/wiki/Camera_matrix


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
			pixel.position.setX(static_cast<float>(width));
			pixel.position.setY(static_cast<float>(height));

			// Normalized Device Coords (NDC)
			Vector2 pixelNDC;
			pixelNDC.setX((pixel.position.getX() + 0.5f) / canvas.width);
			pixelNDC.setY((pixel.position.getY() + 0.5f) / canvas.height);

			// Screen space
			Vector2 pixel_screen;
			pixel_screen.setX(2.0f * pixelNDC.getX() - 1.0f); // normalizing to [-1, 1]
			pixel_screen.setY(1.0f - 2.0f * pixelNDC.getY()); // normalizing to [-1, 1]

			// Deg2rad
			float deg2rad = tan(camera_fov / 2.0f * pi / 180.0f);

			// Camera space
			Vector3 pixel_camera;
			pixel_camera.setX((2.0f - pixel_screen.getX() - 1.0f) * viewport.aspect_ratio * deg2rad);
			pixel_camera.setY((1.0f - 2.0f * pixel_screen.getY()) * deg2rad);

			Vector3 camera_space;
			camera_space.setX(pixel_camera.getX());
			camera_space.setY(pixel_camera.getY());
			camera_space.setZ(-1.0f);

			Ray primary_ray;
			primary_ray.origin = camera_position;
			primary_ray.direction = Vector3::normalize(camera_space - primary_ray.origin);

			float t = std::numeric_limits<float>::max();

			Colour hit_colour;

			if (intersect(primary_ray.origin, primary_ray.direction, t))
			{
				Vector3 output = (primary_ray.direction + Vector3(1.0f, 1.0f, 1.0f))* Vector3(0.5f, 0.5f, 0.5f);
				hit_colour = { output.getX(), output.getY(), output.getZ() };
			}
			else
			{
				hit_colour = { 0.0f, 0.0f, 0.0f };
			}

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