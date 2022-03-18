#pragma once
// C++
#include <string>
#include <iostream>
#include <fstream>

// Maths
#include "Vector3.h"
#include "Vector2.h"
#include "Matrix4x4.h"

// Graphics
#include "Colour.h"
#include "Pixel.h"

#include "Ray.h"
#include "Camera.h"
#include "Primitive.h"

// Utility
#include "Timer.h"
#include "Logger.h"

#include "Bvh.h"

#include "Light.h"

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
// https://github.com/ssloy/tinyraytracer/blob/master/tinyraytracer.cpp	

// https://computergraphics.stackexchange.com/questions/1976/how-to-determine-the-object-to-world-matrix
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/#translation-matrices

int main()
{
	Logger::PrintMsg("Started program");
	// Use stb_image for saving images

	// Right handed Cartesian coordinate systems
	// X+, y+, Z-

	Light::DirectionLight dirLight(Maths::special::pi, { 1.0f, 1.0f, 1.0f }, { 0.0f, 5.0f, 0.0f });

	Primitive cube;
	cube.setPosition({ 1.0f, 0.0f, -10.0f });

	Primitive sphere("Assets\\unit_sphere.obj", { 0.0f, 0.0f, 0.0f });
	sphere.setPosition({-1.0f, 1.0f, -15.0f });

	Primitive triangle("Assets\\unit_sphere.obj", { 0.0f, 0.0f, 0.0f });
	triangle.setPosition({ 0.0f, 1.0f, -5.0f });

	Primitive cone("Assets\\unit_sphere.obj", { 0.0f, 0.0f, 0.0f });
	cone.setPosition({ -0.5f, -1.0f, -8.0f });

	Primitive plane("Assets\\plane.obj", { 0.0f, 0.0f, 0.0f });
	plane.setPosition({ 0.0f, -1.0f, -10.0f });

	std::vector<Primitive> primitives;

	primitives.push_back(triangle);
	primitives.push_back(cone);
	primitives.push_back(cube);
	primitives.push_back(sphere);
	primitives.push_back(plane);
	

	// Split scene primitives into bounding boxes using a BVH accelerator
	//BVH::Scene::Accelerator bvh_scene;
	//bvh_scene.buildBVHScene(primitives);

	BVH::Builder bvh;
	bvh.build(primitives);

	//// Once the bvh has finished, clear all primitive data since that data now lives inside the bvh
	//primitives.clear();


	// Image in pixels
	Vector2 image_size = { 640, 480 };

	// https://stackoverflow.com/questions/13078243/how-to-move-a-camera-using-in-a-ray-tracer
	// Camera
	Camera camera(Vector3(0.0f, 0.0f, 10.0f), Vector3(0.0f, 0.0f, -1.0f), image_size, 90.0f);
	Matrix4x4::multVecByMatrix4x4(camera.getMatrix(), camera.getPosition());

	// Create framebuffer and set it to black
	std::vector<Pixel> framebuffer;
	framebuffer.resize(static_cast<size_t>(image_size.getX() * image_size.getY()));
	std::fill(framebuffer.begin(), framebuffer.end(), Pixel());

	// Start timer
	Timer render_timer;
	render_timer.StartTimer();

	// Render what the camera sees in the frame buffer
	camera.Render(primitives, framebuffer, bvh, dirLight);

	// End timer
	render_timer.EndTimer();

	// Output timer
	Logger::PrintDebug("Render time: " + std::to_string(render_timer.ShowResult()) + " seconds");

	Timer output_timer;
	output_timer.StartTimer();

	// Create a file and write the contents of the framebuffer to the file
	std::ofstream file("Image.ppm", std::ios::out | std::ios::binary);

	if (file.is_open())
	{
		file << "P3\n" << image_size.getX() << ' ' << image_size.getY() << "\n255\n";

		for(auto& pixel : framebuffer)
		{
			// Gamma correction
			float r = std::sqrtf(pixel.colour.getRed());
			float g = std::sqrtf(pixel.colour.getGreen());
			float b = std::sqrtf(pixel.colour.getBlue());

			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);

			file << ir << ' ' << ig << ' ' << ib << '\n';
		}
		file.close();
	}
	framebuffer.clear();

	output_timer.EndTimer();
	
	// Output timer
	Logger::PrintDebug("Output time: " + std::to_string(output_timer.ShowResult()) + " seconds");
	Logger::PrintMsg("Closing program");
	return 0;
}
