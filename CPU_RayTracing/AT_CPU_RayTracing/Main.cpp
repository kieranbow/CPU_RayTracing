#include "Vector3.h"

struct Vector2
{
	float x;
	float y;
};

int main()
{
	// https://github.com/iweinbau/Ray-Tracing/blob/master/Ray%20tracing/Utils/Camera.cpp
	// https://raytracing.github.io/books/RayTracingInOneWeekend.html#overview
	// https://www.scratchapixel.com/code.php?id=24&origin=/lessons/3d-basic-rendering/3d-viewing-pinhole-camera
	// https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix
	// https://gabrielgambetta.com/computer-graphics-from-scratch/02-basic-raytracing.html
	// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview
	// 

	// Image
	Vector2 image_size = { 640, 480 };

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

	return 0;
}