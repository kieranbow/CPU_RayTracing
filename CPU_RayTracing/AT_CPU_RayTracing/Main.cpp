#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <fstream>

// Maths
#include "Vector3.h"
#include "Vector2.h"
#include "Matrix4x4.h"

// Graphics
#include "Colour.h"
#include "Pixel.h"

#include "Ray.h"


long double operator"" _mm(long double _rhs)
{
	return _rhs;
}

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

bool intersect(Ray ray, Vector3 centre, float radius, float t)
{
	float t0 = 0.0f;
	float t1 = 0.0f;
	float radius2 = radius * radius;

	Vector3 length = centre - ray.origin;
	float tca = Vector3::dot(length, ray.direction);

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

float deg2rad(const float& deg) { return deg * pi / 180.0f; }

int main()
{
	// Use stb_image for saving images

	// Right handed Cartesian coordinate systems
	// X+, y+, Z-

	// Image in pixels
	Vector2 image_size = { 640, 480 };
	float image_aspectRatio = image_size.getX() / image_size.getY(); // 4:3


	// Matrix
	Matrix4x4 camera_to_world(0.871214, 0, -0.490904, 0, -0.192902, 0.919559, -0.342346, 0, 0.451415, 0.392953, 0.801132, 0, 14.777467, 29.361945, 27.993464, 1);


	// Camera
	float focal_length = 35.0f; // Controls how much of the image is rendered
	float film_aperture_width = 0.825f;
	float film_aperture_height = 0.446f;

	static const float inch_to_mm = 25.4f;

	float near_clipping_plane = 0.1f;
	float far_clipping_place = 1000.0f;

	float film_aspect_ratio = film_aperture_width / film_aperture_height;
	float device_aspect_ratio = image_aspectRatio;

	float top = ((film_aperture_height * inch_to_mm / 2.0f) / focal_length) * near_clipping_plane;
	float right = ((film_aperture_width * inch_to_mm / 2.0f) / focal_length) * near_clipping_plane;
	
	top *= 1.0f;
	right *= 1.0f;

	float bottom = -top;
	float left = -right;


	float camera_fov = 90.0f;

	// Deg2rad
	float scale = deg2rad(camera_fov * 0.5f);

	


	Vector3 camera_position			= { 0.0f, 0.0f, 0.0f }; // World origin
	Vector3 camera_direction		= { 0.0f, 0.0f, -2.0f}; // Pointing Z-
	Vector3 camera_up				= { 0.0f, 1.0f, 0.0f }; // Pointing Y+
	Vector3 camera_alignment_vector = { 0.0f, 0.0f, 0.0f };

	// Create framebuffer and set it to black
	std::vector<Pixel> framebuffer;
	framebuffer.resize(static_cast<size_t>(image_size.getX() * image_size.getY()));
	std::fill(framebuffer.begin(), framebuffer.end(), Pixel());

	int x = 0;

	camera_to_world.multiplyVectorToMatrix4x4(Vector3(0.0f, 0.0f, 0.0f), camera_position);

	for (int height = 0; height < static_cast<int>(image_size.getY()); ++height)
	{
		for (int width = 0; width < static_cast<int>(image_size.getX()); ++width)
		{
			Pixel pixel;

			// Rasterizer space
			pixel.position.setX(static_cast<float>(width));
			pixel.position.setY(static_cast<float>(height));

			// Normalized Device Coords (NDC)
			Vector2 pixelNDC;
			pixelNDC.setX((pixel.position.getX() + 0.5f) / image_size.getX());
			pixelNDC.setY((pixel.position.getY() + 0.5f) / image_size.getY());

			// Screen space
			Vector2 pixel_screen;
			pixel_screen.setX(2.0f * pixelNDC.getX() - 1.0f); // normalizing to [-1, 1]
			pixel_screen.setY(1.0f - 2.0f * pixelNDC.getY()); // normalizing to [-1, 1]

			// Camera space
			Vector3 pixel_camera;
			pixel_camera.setX((2.0f - pixel_screen.getX() - 1.0f) * image_aspectRatio * scale);
			pixel_camera.setY((1.0f - 2.0f * pixel_screen.getY()) * scale);

			Vector3 camera_space;
			camera_space.setX(pixel_camera.getX());
			camera_space.setY(pixel_camera.getY());
			camera_space.setZ(-1.0f);


			Ray primary_ray;
			primary_ray.origin = camera_position;
			primary_ray.direction = { 0.0f, 0.0f, 0.0f }; // Vector3::normalize(matrix.multiplyVectorToMatrix4x4(camera_space - primary_ray.origin, primary_ray.direction));

			camera_to_world.multiplyVectorToMatrix4x4(camera_space, primary_ray.direction);

			Vector3::normalize(primary_ray.direction);

			Colour hit_colour = { 0.0f, 0.0f, 0.0f };

			if (intersect(primary_ray, Vector3(0.0f, 0.0f, -100.0f), 0.2f, 0.0f))
			{
				hit_colour.setColour(1.0f, 0.0f, 0.0f);
			}
			else
			{
				hit_colour.setColour(0.0f, 0.0f, 0.0f);
			}

			// Vector3 output = (primary_ray.direction + Vector3(1.0f, 1.0f, 1.0f)) * Vector3(0.5f, 0.5f, 0.5f);
			//framebuffer.at(x).colour.setColour(output.getX(), output.getY(), output.getZ());

			// write colour output to framebuffer
			framebuffer.at(x).colour.setColour(hit_colour);
			x++;
		}
	}

	// Create a file and write the contents of the framebuffer to the file
	std::ofstream file("Image.ppm");

	if (file.is_open())
	{
		file << "P3\n" << image_size.getX() << ' ' << image_size.getY() << "\n255\n";

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