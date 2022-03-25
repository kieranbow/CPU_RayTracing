#pragma once
// C++
#include <string>
#include <iostream>
#include <fstream>
#include <thread>

// Maths
#include "Vector3.h"
#include "Vector2.h"
#include "Matrix4x4.h"

// Graphics
#include "Colour.h"
#include "Pixel.h"
#include "Material.h"
#include "Texture.h"

// Scene stuff
#include "Primitive.h"
#include "Bvh.h"
#include "Light.h"
#include "Camera.h"

// Utility
#include "Timer.h"
#include "Logger.h"

struct Options
{
	float width = 0.0f;
	float height = 0.0f;
	int aaAmount = 1;
};

int main()
{
	Logger::PrintMsg("Started program");
	// Use stb_image for saving images

	// Right handed Cartesian coordinate systems
	// X+, y+, Z-

	//float width;
	//float height;
	//int amount;

	//Logger::PrintMsg("Input image width");
	//std::cin >> width;
	//
	//Logger::PrintMsg("Input image height");
	//std::cin >> height;

	//Logger::PrintMsg("Input Anti-aliasing amount");
	//std::cin >> amount;
	//Texture texture("Assets\\test.png");
	//texture.at(0.5f, 1.0f);

	const auto processor_count = std::thread::hardware_concurrency();
	Logger::PrintDebug("Using: " + std::to_string(processor_count) + " Threads");

	Options options;
	//options.width = width;
	//options.height = height;
	//options.aaAmount = amount;
	options.width = 1280;
	options.height = 720;
	options.aaAmount = 4;

	Vector2 image_size = { options.width, options.height };
	int depth = 0;

	// https://stackoverflow.com/questions/13078243/how-to-move-a-camera-using-in-a-ray-tracer
	// Define the scene camera
	Camera camera(Vector3(0.0f, 0.0f, -2.0f), Vector3(0.0f, 0.0f, -1.0f), image_size, 45.0f);
	Matrix4x4::multVecByMatrix4x4(camera.getMatrix(), camera.getPosition());

	// Create the scenes lights
	std::vector<std::unique_ptr<Light::Light>> sceneLights;
	//sceneLights.push_back(std::unique_ptr<Light::DirectionLight>(new Light::DirectionLight(1.0f, Colour(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.5f, 1.0f))));
	sceneLights.push_back(std::unique_ptr<Light::DirectionLight>(new Light::DirectionLight(1.0f, Colour(1.0f, 1.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f))));
	//sceneLights.push_back(std::unique_ptr<Light::DirectionLight>(new Light::DirectionLight(1.0f, Colour(0.0f, 0.0f, 1.0f), Vector3(1.0f, 0.5f, 0.0f))));
	//sceneLights.push_back(std::unique_ptr<Light::PointLight>(new Light::PointLight(1.0f, Colour(1.0f, 1.0f, 1.0f), Vector3(0.0f, 2.0f, -8.0f))));

	// Create the scene's primitives and their materials
	Primitive cube;
	cube.setPosition({ 3.0f, 0.0f, -15.0f });

	Material::Data cube_material;
	cube_material.type		= Material::Types::Dielectic; // Reflective
	cube_material.albedo	= Colour(1.0f, 0.0f, 0.0f);
	cube_material.roughness	= 1.0f;
	cube_material.metallic	= 0.0f;
	cube.setMaterial(cube_material);
	cube.setAlbedoTexture("Assets\\uv.png");

	Primitive sphere("Assets\\helmet.obj", { 0.0f, 0.0f, 0.0f });
	sphere.setPosition({-3.0f, 1.0f, -9.0f });

	Material::Data sphere_material;
	sphere_material.type		= Material::Types::Dielectic;
	sphere_material.albedo		= Colour(0.0f, 1.0f, 0.0f);
	sphere_material.roughness	= 0.0f;
	sphere_material.metallic	= 1.0f;
	sphere.setMaterial(sphere_material);

	Primitive triangle("Assets\\unit_sphere.obj", { 0.0f, 0.0f, 0.0f });
	triangle.setPosition({ 5.0f, 1.0f, -12.0f });

	Material::Data triangle_material;
	triangle_material.type = Material::Types::Dielectic;  // Reflective
	triangle_material.albedo = Colour(0.5f, 0.5f, 0.5f);
	triangle_material.roughness = 0.0f;
	triangle_material.metallic = 0.5f;
	triangle.setMaterial(triangle_material);

	Primitive cone("Assets\\unit_sphere.obj", { 0.0f, 0.0f, 0.0f });
	cone.setPosition({ 0.0f, 1.0f, -10.0f });

	Material::Data cone_material;
	cone_material.type = Material::Types::Dielectic;  // Refractive
	cone_material.albedo = Colour(1.0f, 1.0f, 0.0f);
	cone_material.roughness = 1.0f;
	cone_material.metallic = 0.0f;
	cone.setMaterial(cone_material);
	cone.setAlbedoTexture("Assets\\test.png");

	Primitive plane("Assets\\plane.obj", { 0.0f, 0.0f, 0.0f });
	plane.setPosition({ 0.0f, -1.0f, -10.0f });

	Material::Data plane_material;
	plane_material.type = Material::Types::Dielectic; // Reflective
	plane_material.albedo = Colour(0.5f, 0.5f, 0.5f);
	plane_material.roughness = 1.0f;
	plane_material.metallic = 0.0f;
	plane.setMaterial(plane_material);
	plane.setAlbedoTexture("Assets\\uv.png");

	// Push primitives into vector to be processed by the bvh
	std::vector<Primitive> primitives{};
	primitives.push_back(triangle);
	primitives.push_back(cone);
	primitives.push_back(plane);
	primitives.push_back(cube);
	primitives.push_back(sphere);


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
	camera.Render(framebuffer, bvh, sceneLights, depth, options.aaAmount);

	// End render timer
	render_timer.EndTimer();
	Logger::PrintDebug("Render time: " + std::to_string(render_timer.ShowResult()) + " seconds");

	// Output render frame
	Texture outputFrame;
	outputFrame.savePNG("Image.png", framebuffer, static_cast<int>(options.width), static_cast<int>(options.height), 3);
	framebuffer.clear();

	return 1;
}
