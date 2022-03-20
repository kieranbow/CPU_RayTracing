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

// Scene stuff
#include "Primitive.h"
#include "Bvh.h"
#include "Light.h"
#include "Camera.h"

// Utility
#include "Timer.h"
#include "Logger.h"
#include "ShaderFunc.h"

int main()
{
	Logger::PrintMsg("Started program");
	// Use stb_image for saving images

	// Right handed Cartesian coordinate systems
	// X+, y+, Z-

	Vector2 image_size = { 640, 480 };
	int depth = 0;

	// https://stackoverflow.com/questions/13078243/how-to-move-a-camera-using-in-a-ray-tracer
	// Define the scene camera
	Camera camera(Vector3(0.0f, 0.0f, 10.0f), Vector3(0.0f, 0.0f, -1.0f), image_size, 90.0f);
	Matrix4x4::multVecByMatrix4x4(camera.getMatrix(), camera.getPosition());

	// Create the scenes lights
	std::vector<std::unique_ptr<Light::Light>> sceneLights;
	sceneLights.push_back(std::unique_ptr<Light::DirectionLight>(new Light::DirectionLight(1.0f, Colour(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.5f, 1.0f))));
	//sceneLights.push_back(std::unique_ptr<Light::DirectionLight>(new Light::DirectionLight(1.0f, Colour(1.0f, 0.0f, 0.0f), Vector3(5.0f, 10.0f, 5.0f))));
	//sceneLights.push_back(std::unique_ptr<Light::PointLight>(new Light::PointLight(1.0f, Colour(1.0f, 1.0f, 1.0f), Vector3(0.0f, 1.0f, -8.0f))));

	// Create the scene's primitives
	Primitive cube;
	cube.setPosition({ 1.0f, 0.0f, -10.0f });
	cube.colour = Colour(1.0f, 0.0f, 0.0f);

	Primitive sphere("Assets\\unit_sphere.obj", { 0.0f, 0.0f, 0.0f });
	sphere.setPosition({-1.0f, 1.0f, -15.0f });
	sphere.colour = Colour(0.0f, 1.0f, 0.0f);

	Primitive triangle("Assets\\unit_sphere.obj", { 0.0f, 0.0f, 0.0f });
	triangle.setPosition({ 0.0f, 1.0f, -5.0f });
	triangle.colour = Colour(0.0f, 0.0f, 1.0f);

	Primitive cone("Assets\\unit_sphere.obj", { 0.0f, 0.0f, 0.0f });
	cone.setPosition({ -0.5f, -1.0f, -8.0f });
	cone.colour = Colour(0.5f, 1.0f, 0.5f);

	Primitive plane("Assets\\plane.obj", { 0.0f, 0.0f, 0.0f });
	plane.setPosition({ 0.0f, -1.0f, -10.0f });
	plane.colour = Colour(1.0f, 0.5f, 0.0f);

	// Push primitives into vector to be processed by the bvh
	std::vector<Primitive> primitives;
	primitives.push_back(triangle);
	primitives.push_back(cone);
	primitives.push_back(cube);
	primitives.push_back(sphere);
	primitives.push_back(plane);

	// Build a bvh for all the primitives
	BVH::Builder bvh;
	bvh.build(primitives);

	// Once the bvh has finished, clear all primitive data since that data now lives inside the bvh
	primitives.clear();

	// Create a framebuffer for rendering into and set it to black
	std::vector<Pixel> framebuffer;
	framebuffer.resize(static_cast<size_t>(image_size.getX() * image_size.getY()));
	std::fill(framebuffer.begin(), framebuffer.end(), Pixel());

	// -------------------------------------------------------
	// Start render timer
	Timer render_timer;
	render_timer.StartTimer();

	// Render what the camera sees into the frame buffer
	camera.Render(framebuffer, bvh, sceneLights, depth);

	// End render timer
	render_timer.EndTimer();
	Logger::PrintDebug("Render time: " + std::to_string(render_timer.ShowResult()) + " seconds");

	// Create a file and write the contents of the framebuffer to the file
	std::ofstream file("Image.ppm", std::ios::out | std::ios::binary);

	if (file.is_open())
	{
		file << "P3\n" << image_size.getX() << ' ' << image_size.getY() << "\n255\n";

		for(auto& pixel : framebuffer)
		{
			// Gamma correction
			Colour colour = Shaders::Functions::gammaCorrect(pixel.colour);

			int ir = static_cast<int>(256 * std::clamp(colour.getRed(), 0.0f, 0.999f));
			int ig = static_cast<int>(256 * std::clamp(colour.getGreen(), 0.0f, 0.999f));
			int ib = static_cast<int>(256 * std::clamp(colour.getBlue(), 0.0f, 0.999f));

			file << ir << ' ' << ig << ' ' << ib << '\n';
		}
		file.close();
	}
	framebuffer.clear();

	return 1;
}
