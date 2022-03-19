#include "Camera.h"
#include "Primitive.h"
#include "Intersection.h"
#include "ShaderMaths.h"
#include "Random.h"

Camera::Camera(Vector3 positionWS, Vector3 directionWS, Vector2 cam_size, float _fov)
{
	// Set world space position and direction
	m_position = m_camToWorld.multVecByMatrix4x4(positionWS);
	m_direction = directionWS;

	// Set the dimension of the camera
	m_size = cam_size;

	m_fov = _fov;

	// Set the aspect ratio based on camera size
	m_aspectRatio = m_size.getX() / m_size.getY();
	m_scale = tan(Maths::deg2rad(m_fov) * 0.5f);
}

void Camera::Render(std::vector<Primitive> primitives, std::vector<Pixel>& buffer, BVH::Builder& bvh, Light::DirectionLight& light, int depth)
{
	// https://www.iquilezles.org/www/articles/cputiles/cputiles.htm
	const int tilesize = 16;
	const int numXtile = static_cast<int>(m_size.getX()) / tilesize;
	const int numYtile = static_cast<int>(m_size.getY()) / tilesize;
	const int numTiles = numXtile * numYtile;
	const int maxDepth = 5;

	for (int tile = 0; tile < numTiles; tile++)
	{
		const float offset_x = static_cast<float>(tilesize * (tile % numXtile));
		const float offset_y = static_cast<float>(tilesize * (tile / numXtile));

		for (int y = 0; y < tilesize; y++)
		{
			for (int x = 0; x < tilesize; x++)
			{
				const float x_iter = offset_x + static_cast<float>(x);
				const float y_iter = offset_y + static_cast<float>(y);
				const int iter = static_cast<int>(m_size.getX() * (y_iter) + (x_iter));
				// Create a pixel
				Pixel pixel;

				// Convert pixel from raster space to camera space
				float Px = (2.0f * (((x_iter) + 0.5f) / m_size.getX()) - 1.0f) * m_aspectRatio * m_scale;	// * tan(fov / 2.0f * Maths::special::pi / 180.0f) * aspect_ratio * scale;
				float Py = (1.0f - 2.0f * (((y_iter) + 0.5f) / m_size.getY()));	// * tan(fov / 2.0f * Maths::special::pi / 180.0f));
				pixel.position.setX(Px);
				pixel.position.setY(Py);

				// Convert pixel camera space to world space
				Vector3 pixelPosWS;
				m_camToWorld.multDirByMatrix4x4(Vector3(pixel.position.getX(), pixel.position.getY(), m_direction.getZ()), pixelPosWS);
				Vector3::normalize(pixelPosWS);

				// Create ray that's origin is the camera and it's direction towards the pixel
				RayTrace::Ray primary_ray;
				primary_ray.setOrigin(m_position);
				primary_ray.setDirection(Vector3::normalize(pixelPosWS - primary_ray.getOrigin()));

				buffer.at(iter).colour = castRay(primary_ray, bvh, light, depth);

				//if (bvh.hit(primary_ray))
				//{
				//	Vector3 hitpoint = primary_ray.getOrigin() + primary_ray.getDirection() * primary_ray.getHitData().tnear;
				//	
				//	Vector3 N = primary_ray.getHitData().normal;
				//	Vector3 L = (hitpoint + N + Vector3::randomUnitSphere()) - hitpoint; //light.getDirection();


				//	RayTrace::Ray shadowRay;
				//	shadowRay.setOrigin(hitpoint + N * 0.1f);
				//	shadowRay.setDirection(Vector3::normalize(L - shadowRay.getOrigin()));

				//	bool shadow = !bvh.hit(shadowRay);

				//	Colour albedo = { 1.0f, 1.0f, 1.0f };
				//	Colour diffuse = albedo / Maths::special::pi * light.getIntensity() * light.getColour() * std::max(0.0f, Vector3::dot(L, N));

				//	buffer.at(iter).colour = diffuse * shadow;
				//}
				//else
				//{
				//	buffer.at(iter).colour = Colour(0.5f, 0.5f, 1.0f);
				//}
			}
		}
	}
}

Colour Camera::castRay(RayTrace::Ray& ray, BVH::Builder& bvh, Light::DirectionLight& light, int depth)
{
	if (depth > max_depth) return Colour(0.5f, 0.5f, 1.0f);

	if (bvh.hit(ray))
	{
		Vector3 hitpoint = ray.getOrigin() + ray.getDirection() * ray.getHitData().tnear;

		Vector3 N = ray.getHitData().normal;
		Vector3 L = light.getDirection();


		RayTrace::Ray shadowRay;
		shadowRay.setOrigin(hitpoint + N * 0.1f);
		shadowRay.setDirection(Vector3::normalize(L - shadowRay.getOrigin()));

		bool shadow = !bvh.hit(shadowRay);

		Colour albedo = { 1.0f, 1.0f, 1.0f };
		Colour diffuse = albedo / Maths::special::pi * light.getIntensity() * light.getColour() * std::max(0.0f, Vector3::dot(L, N));

		return diffuse * shadow;
	}
	else
	{
		return Colour(0.5f, 0.5f, 1.0f);
	}
}
