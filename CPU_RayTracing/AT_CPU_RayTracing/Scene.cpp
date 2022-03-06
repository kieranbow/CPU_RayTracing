#include "Scene.h"

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

// Utility
#include "Timer.h"
#include "Logger.h"

void Scene::initialize()
{
	Primitive cube;
	cube.setPosition({ 1.0f, 0.0f, -10.0f });

	std::unique_ptr<Primitive> test = std::make_unique<Primitive>();

	p_primitives.push_back(test);

}

void Scene::destroy()
{
}

void Scene::update()
{
}

void Scene::Render()
{
	// Image in pixels
	image_size = { 640, 480 };

	framebuffer.resize(static_cast<size_t>(image_size.getX() * image_size.getY()));
	std::fill(framebuffer.begin(), framebuffer.end(), Pixel());

	// https://stackoverflow.com/questions/13078243/how-to-move-a-camera-using-in-a-ray-tracer
	// Camera
	Camera camera(Vector3(0.0f, 0.0f, 10.0f), Vector3(0.0f, 0.0f, -1.0f), image_size, 90.0f);
	Matrix4x4::multVecByMatrix4x4(camera.getMatrix(), camera.getPosition());

	// Start timer
	Timer render_timer;
	render_timer.StartTimer();

	// Render what the camera sees
	camera.Render(p_primitives, framebuffer);

	// End timer
	render_timer.EndTimer();

	// Output timer
	Logger::PrintDebug("Render time: " + std::to_string(render_timer.ShowResult()) + " seconds");
}

void Scene::Output()
{
	Timer output_timer;
	output_timer.StartTimer();

	// Create a file and write the contents of the framebuffer to the file
	std::ofstream file("Image.ppm", std::ios::out | std::ios::binary);

	if (file.is_open())
	{
		file << "P3\n" << image_size.getX() << ' ' << image_size.getY() << "\n255\n";

		for (auto& pixel : framebuffer)
		{
			int ir = static_cast<int>(255.999 * pixel.colour.getRed());
			int ig = static_cast<int>(255.999 * pixel.colour.getGreen());
			int ib = static_cast<int>(255.999 * pixel.colour.getBlue());

			file << ir << ' ' << ig << ' ' << ib << '\n';
		}
		file.close();
	}
	framebuffer.clear();

	output_timer.EndTimer();
}
