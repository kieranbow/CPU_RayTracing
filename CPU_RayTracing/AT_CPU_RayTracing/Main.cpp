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
#include "Random.h"

// Graphics
#include "Colour.h"
#include "Pixel.h"
#include "Material.h"
#include "Texture.h"
#include "Atmosphere.h"

// Scene stuff
#include "Primitive.h"
#include "Bvh.h"
#include "Light.h"
#include "Camera.h"

// Utility
#include "Timer.h"
#include "Logger.h"
#include "Option.h"

int main()
{
	Logger::PrintMsg("Started program");
	// Right handed Cartesian coordinate systems
	// X+, y+, Z-

	const auto processor_count = std::thread::hardware_concurrency();
	Logger::PrintDebug("Using: " + std::to_string(processor_count) + " Threads");

	Options options;
	//options.width = width;
	//options.height = height;
	//options.aaAmount = amount;
	options.imageWidth = 1920;
	options.imageHeight = 1080;
	options.aaAmount = 4;

	Vector2 image_size = { static_cast<float>(options.imageWidth), static_cast<float>(options.imageHeight) };
	int depth = 0;

	Timer sceneTimer;
	sceneTimer.StartTimer();

	// Create and define an atmosphere
	Atmosphere atmosphere;
	float angle = Maths::deg2rad(-85.0f);
	Vector3 sunDir = Vector3(0.0f, std::cos(angle), -std::sin(angle));
	atmosphere.setSunDirection(sunDir);
	atmosphere.setBrightness(1.0f);
	//atmosphere.setPlanetRadius(10000.0f);
	//atmosphere.setAtmosphereRadius(11000.0f);
	//atmosphere.setRayleighThickness(1000.0f);
	//atmosphere.setMieThickness(100.0f);

	// https://stackoverflow.com/questions/13078243/how-to-move-a-camera-using-in-a-ray-tracer
	// Define the scene camera
	Camera camera(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), image_size, 45.0f, options);
	Matrix4x4::multVecByMatrix4x4(camera.getMatrix(), camera.getPosition());

	// Create the scenes lights
	std::vector<std::unique_ptr<Light::Light>> sceneLights;
	sceneLights.push_back(std::unique_ptr<Light::DirectionLight>(new Light::DirectionLight(1.0f, Colour(1.0f, 1.0f, 1.0f), sunDir))); // Vector3(0.0f, 0.5f, 1.0f) /*Vector3(1.0f, 0.5f, 1.0f)*/
	sceneLights.push_back(std::unique_ptr<Light::DirectionLight>(new Light::DirectionLight(1.0f, Colour(1.0f, 0.0f, 0.0f), Vector3(-1.0f, 1.0f, 1.0f)))); // Vector3(-1.0f, 1.0f, 1.0f)
	sceneLights.push_back(std::unique_ptr<Light::DirectionLight>(new Light::DirectionLight(1.0f, Colour(0.0f, 1.0f, 0.0f), Vector3(-1.0f, 0.5f, -1.0f)))); // Vector3(1.0f, 0.5f, 0.0f)
	sceneLights.push_back(std::unique_ptr<Light::DirectionLight>(new Light::DirectionLight(0.5f, Colour(0.0f, 0.0f, 1.0f), Vector3(1.0f, 1.0f, -1.0f)))); // Vector3(1.0f, 0.5f, 0.0f)

	// Create the scene's primitives and their materials
	Primitive cube;
	cube.setPosition({ 3.0f, 0.0f, -15.0f });

	Material::Data cube_material;
	cube_material.type		= Material::Types::Dielectic; // Reflective
	cube_material.albedo	= Colour(1.0f, 0.0f, 0.0f);
	cube_material.roughness	= 1.0f;
	cube_material.metallic	= 0.0f;
	cube.setMaterial(cube_material);

	Primitive helmet("Assets\\helmet.obj", { 0.0f, 0.0f, 0.0f });
	helmet.setPosition({-3.0f, 0.2f, -9.0f });

	Material::Data helmet_material;
	helmet_material.type				= Material::Types::Dielectic;
	helmet_material.albedo				= Colour(0.0f, 1.0f, 0.0f);
	helmet_material.roughness			= 0.5f;
	helmet_material.metallic			= 1.0f;
	helmet_material.specular_intensity	= 1.0f;
	helmet.setMaterial(helmet_material);

	Primitive unitSphere("Assets\\unit_sphere.obj", { 0.0f, 0.0f, 0.0f });
	unitSphere.setPosition({ 5.0f, 1.0f, -12.0f });

	Material::Data unitSphere_material;
	unitSphere_material.type		= Material::Types::Dielectic;
	unitSphere_material.albedo		= Colour(1.0f, 1.0f, 1.0f);
	unitSphere_material.roughness	= 0.5f;
	unitSphere_material.metallic	= 1.0f;
	unitSphere.setMaterial(unitSphere_material);

	Primitive metalSphere("Assets\\unit_sphere.obj", { 0.0f, 0.0f, 0.0f });
	metalSphere.setPosition({ 2.0f, -1.0f, -9.0f });

	Material::Data metalSphere_material;
	metalSphere_material.type = Material::Types::Dielectic;
	metalSphere_material.albedo = Colour(1.0f, 0.5f, 0.0f);
	metalSphere_material.roughness = 0.3f;
	metalSphere_material.metallic = 0.0f;
	metalSphere.setMaterial(metalSphere_material);

	Primitive reflectSphere("Assets\\unit_sphere.obj", { 0.0f, 0.0f, 0.0f });
	reflectSphere.setPosition({ 0.0f, 0.0f, -10.0f });

	Material::Data reflectSphere_material;
	reflectSphere_material.type			= Material::Types::Reflective;
	reflectSphere_material.albedo		= Colour(1.0f, 1.0f, 1.0f);
	reflectSphere_material.roughness	= 0.5f;
	reflectSphere_material.metallic		= 1.0f;
	reflectSphere.setMaterial(reflectSphere_material);

	Primitive plane("Assets\\plane.obj", { 0.0f, 0.0f, 0.0f });
	plane.setPosition({ 0.0f, -1.0f, -10.0f });

	Material::Data plane_material;
	plane_material.type			= Material::Types::Dielectic;
	plane_material.albedo		= Colour(0.5f, 0.5f, 0.5f);
	plane_material.roughness	= 0.3f;
	plane_material.metallic		= 0.0f;
	plane.setMaterial(plane_material);
	plane.setAlbedoTexture("Assets\\Checker.png");

	// Push primitives into vector to be processed by the bvh
	std::vector<Primitive> primitives;
	primitives.push_back(unitSphere);
	primitives.push_back(metalSphere);
	primitives.push_back(reflectSphere);
	primitives.push_back(cube);
	primitives.push_back(helmet);
	primitives.push_back(plane);

	//for (size_t i = 0; i < 1; i++)
	//{
	//	Primitive sphere("Assets\\unit_sphere.obj", { 0.0f, 0.0f, 0.0f });
	//	sphere.setPosition({ 0.0f, 0.0f, -10.0f });

	//	Material::Data material;
	//	material.type = Material::Types::Dielectic;
	//	material.albedo = Colour(1.0f, 0.0f, 0.0f);
	//	material.metallic = Maths::Random::randomFloat();
	//	material.roughness = Maths::Random::randomFloat();

	//	primitives.push_back(sphere);
	//}


	// Build a bvh for all the primitives
	BVH::Builder bvh;
	bvh.build(primitives);

	// Once the bvh has finished, clear all primitive data since that data now lives inside the bvh
	primitives.clear();

	sceneTimer.EndTimer();
	Logger::PrintDebug("Scene took: " + std::to_string(sceneTimer.ShowResult()) + " seconds to load");

	// Create a framebuffer for rendering into and set it to black
	std::vector<Pixel> framebuffer;
	framebuffer.resize(static_cast<size_t>(image_size.getX() * image_size.getY()));
	std::fill(framebuffer.begin(), framebuffer.end(), Pixel());

	// Start render timer
	Timer render_timer;
	render_timer.StartTimer();

	// Render what the camera sees into the frame buffer
	//camera.singleThreadRender(framebuffer, bvh, sceneLights, atmosphere, depth, options.aaAmount);
	camera.multiThreadRender(framebuffer, bvh, sceneLights, atmosphere, depth, options.aaAmount);

	// End render timer
	render_timer.EndTimer();
	Logger::PrintDebug("Render time: " + std::to_string(render_timer.ShowResult()) + " seconds");

	// Output render frame
	Texture outputFrame;
	outputFrame.savePNG("Image.png", framebuffer, static_cast<int>(options.imageWidth), static_cast<int>(options.imageHeight), 3);
	framebuffer.clear();

	return 1;
}
