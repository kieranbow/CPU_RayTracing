#include "Camera.h"
#include "Primitive.h"
#include "Intersection.h"

Camera::Camera(Vector3 positionWS, Vector3 directionWS, Vector2 cam_size, float _fov)
{
	// Set world space position and direction
	m_position = cam_to_world.multVecByMatrix4x4(positionWS);
	m_direction = directionWS;

	// Set the dimension of the camera
	size = cam_size;

	fov = _fov;

	// Set the aspect ratio based on camera size
	aspect_ratio = size.getX() / size.getY();
	scale = tan(Maths::helperFunction::deg2rad(fov) * 0.5f);
}

void Camera::Render(std::vector<Primitive> primitives, std::vector<Pixel>& buffer, BVH::Builder bvh, Light::DirectionLight light)
{
	// https://www.iquilezles.org/www/articles/cputiles/cputiles.htm
	const int tilesize = 16;
	const int numXtile = static_cast<int>(size.getX()) / tilesize;
	const int numYtile = static_cast<int>(size.getY()) / tilesize;
	const int numTiles = numXtile * numYtile;

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
				const int iter = static_cast<int>(size.getX() * (y_iter)+(x_iter));
				// Create a pixel
				Pixel pixel;

				// Convert pixel from raster space to camera space
				float Px = (2.0f * (((x_iter)+0.5f) / size.getX()) - 1.0f) * tan(fov / 2.0f * Maths::special::pi / 180.0f) * aspect_ratio * scale;
				float Py = (1.0f - 2.0f * (((y_iter)+0.5f) / size.getY()) * tan(fov / 2.0f * Maths::special::pi / 180.0f));
				pixel.position.setX(Px);
				pixel.position.setY(Py);

				// Convert pixel camera space to world space
				Vector3 pixelPosWS;
				cam_to_world.multDirByMatrix4x4(Vector3(pixel.position.getX(), pixel.position.getY(), m_direction.getZ() /*-1.0f*/), pixelPosWS);
				Vector3::normalize(pixelPosWS);

				// Create ray that's origin is the camera and it's direction towards the pixel
				RayTrace::Ray primary_ray;
				primary_ray.setOrigin(m_position);
				primary_ray.setDirection(Vector3::normalize(pixelPosWS - primary_ray.getOrigin()));

				if (bvh.hit(primary_ray))
				{
					Vector3 hitpoint = primary_ray.getHitData().hitPoint;

					Vector3 L = { 0.0f, 5.0f, 0.0f }; //{ 0.5f, 0.0f, 1.0f };
					Vector3 N = primary_ray.getHitData().normal;

					RayTrace::Ray shadowRay;
					shadowRay.setOrigin(hitpoint + N * 0.1f);
					shadowRay.setDirection(Vector3::normalize(L - shadowRay.getOrigin()));

					bool shadow = !bvh.hit(shadowRay);

					Colour albedo = { 1.0f, 1.0f, 1.0f };
					Colour diffuse = albedo / Maths::special::pi * light.getIntensity() * light.getColour() * std::max(0.0f, Vector3::dot(L, N));

					buffer.at(iter).colour = diffuse * shadow;

					float distToCamVisible = Vector3::distance(hitpoint, primary_ray.getOrigin());
					float distToCamShadow = Vector3::distance(hitpoint, shadowRay.getOrigin());

					//if (primary_ray.getT() < distToCamVisible) buffer.at(iter).colour = Colour(1.0f, 0.0f, 0.0f);
					//if (shadowRay.getT() < distToCamShadow) buffer.at(iter).colour = Colour(0.0f, 1.0f, 0.0f);
				}
				else
				{
					buffer.at(iter).colour = Colour(0.5f, 0.5f, 1.0f);
				}
			}
		}
	}
}

//bool Camera::intersect(RayTrace::Ray& ray, Vector3 center, float radius)
//{
//	Vector3 oc = ray.m_origin - center;
//	float a = Vector3::dot(ray.m_direction, ray.m_direction);
//	float b = 2.0f * Vector3::dot(oc, ray.m_direction);
//	float c = Vector3::dot(oc, oc) - radius * radius;
//	float distriminant = b * b - 4 * a * c;
//
//	return (distriminant > 0.0f);
//}

				//if (bvh.hitPrimitive(primary_rayWS))
				//{
				//	buffer.at(iter).colour = primary_rayWS.data.normal;
				//}
				//else
				//{
				//	buffer.at(iter).colour = Colour(0.5f, 0.5f, 1.0f);
				//}

				//if (bvh.hit(primary_rayWS))
				//{
				//	if (primary_rayWS.t >= primary_rayWS.t_near && primary_rayWS.t <= primary_rayWS.t_far)
				//	{
				//		buffer.at(iter).colour = primary_rayWS.data.normal;
				//	}
				//}
				//else
				//{
				//	buffer.at(iter).colour = Colour(0.5f, 0.5f, 1.0f);
				//}
