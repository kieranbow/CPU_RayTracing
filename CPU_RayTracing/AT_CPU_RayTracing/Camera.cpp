#include "Camera.h"
#include "Primitive.h"
#include "Intersection.h"
#include "ShaderMaths.h"
#include "Random.h"

Camera::Camera(Vector3 position, Vector3 direction, Vector2 cam_size, float fov)
{
	// Set world space position and direction
	m_position = m_camToWorld.multVecByMatrix4x4(position);
	m_direction = direction;

	// Set the dimension of the camera
	m_size = cam_size;

	// Sets the field of view
	m_fov = fov;

	// Set the aspect ratio based on camera size
	m_aspectRatio = m_size.getX() / m_size.getY();
	m_scale = tan(Maths::deg2rad(m_fov) * 0.5f);
}

void Camera::Render(std::vector<Pixel>& buffer, BVH::Builder& bvh, std::vector<std::unique_ptr<Light::Light>>& sceneLights, int depth)
{
	// https://www.iquilezles.org/www/articles/cputiles/cputiles.htm
	const int tilesize = 32;
	const int numXtile = static_cast<int>(m_size.getX()) / tilesize;
	const int numYtile = static_cast<int>(m_size.getY()) / tilesize;
	const int numTiles = numXtile * numYtile;
	const int maxDepth = 5;

	int numOfSamples = 1;

	// Loop through each tile
	for (int tile = 0; tile < numTiles; tile++)
	{
		const float offset_x = static_cast<float>(tilesize * (tile % numXtile));
		const float offset_y = static_cast<float>(tilesize * (tile / numXtile));

		// Loop through the tiles width and height in pixels
		for (int y = 0; y < tilesize; y++)
		{
			for (int x = 0; x < tilesize; x++)
			{
				const float x_iter = offset_x + static_cast<float>(x);
				const float y_iter = offset_y + static_cast<float>(y);
				const int iter = static_cast<int>(m_size.getX() * (y_iter)+(x_iter));

				// Loop through all the Anti-aliasing samples.
				// This is the main render loop where the rays are cast into the scene
				// returing a colour if it has or has not hit anything
				for (int aaX = 0; aaX < numOfSamples; ++aaX)
				{
					float tile_x = x_iter + 0.5f;
					float tile_y = y_iter + 0.5f;

					// Create a pixel
					Pixel pixel;

					// Convert pixel from raster space to camera space
					float Px = (2.0f * (tile_x + (aaX + Maths::Random::randomFloat()) / numOfSamples) / m_size.getX() - 1.0f) * m_aspectRatio * m_scale;	// * tan(fov / 2.0f * Maths::special::pi / 180.0f) * aspect_ratio * scale;
					float Py = (1.0f - (tile_y + (aaX + Maths::Random::randomFloat()) / numOfSamples) / m_size.getY() * 2.0f) * m_scale;	// * tan(fov / 2.0f * Maths::special::pi / 180.0f));
					pixel.position.setX(Px);
					pixel.position.setY(Py);

					// Convert pixel camera space to world space
					Vector3 pixelPosWS;
					m_camToWorld.multDirByMatrix4x4(Vector3(pixel.position.getX(), pixel.position.getY(), m_direction.getZ()), pixelPosWS);
					Vector3::normalize(pixelPosWS);

					// Create ray that's origin is the camera and it's direction is towards the pixel
					RayTrace::Ray primary_ray;
					primary_ray.setOrigin(m_position);
					primary_ray.setDirection(Vector3::normalize(pixelPosWS - primary_ray.getOrigin()));

					// Cast the ray and return a colour to the buffer
					buffer.at(iter).colour += castRay(primary_ray, bvh, sceneLights, depth);
				}

				// Once render loop is complete. Take the current pixel and apply anti-aliasing
				float scale = 1.0f / numOfSamples;

				buffer.at(iter).colour *= Colour(scale, scale, scale);
			}
		}
	}
}

Colour Camera::castRay(RayTrace::Ray& ray, BVH::Builder& bvh, std::vector<std::unique_ptr<Light::Light>>& sceneLights, int depth)
{
	Colour hitColour;
	if (depth > max_depth) return Colour(0.5f, 0.5f, 1.0f);

	if (bvh.hit(ray))
	{
		Vector3 hitpoint = ray.getOrigin() + ray.getDirection() * ray.getHitData().tnear;

		// Loop through all the lights in the scene and add them linearly 
		for (auto& light : sceneLights)
		{
			Vector3 lightDirection;
			Colour lightColour;

			light->illuminate(hitpoint, lightDirection, lightColour, ray.getHitData().tnear);

			Vector3 N = ray.getHitData().normal;
			Vector3 L = Vector3::normalize(lightDirection - hitpoint);

			RayTrace::Ray shadowRay;
			shadowRay.setOrigin(hitpoint + N * 0.1f); /* + N * 0.1f*/
			shadowRay.setDirection(lightDirection); /*L - shadowRay.getOrigin()*/
			shadowRay.m_tNear = ray.getHitData().tnear;

			bool shadow = !bvh.hit(shadowRay);

			Colour albedo = ray.getHitData().colour;
			Colour diffuse = albedo / Maths::special::pi * lightColour * std::max(0.0f, Vector3::dot(lightDirection, N));

			hitColour += diffuse * shadow;
		}
	}
	else
	{
		hitColour = Colour(0.5f, 0.5f, 1.0f);
	}
	return hitColour;
}
