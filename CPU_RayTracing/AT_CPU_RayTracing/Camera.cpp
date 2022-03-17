#include "Camera.h"
#include "Primitive.h"
#include "Intersection.h"

Camera::Camera(Vector3 positionWS, Vector3 directionWS, Vector2 cam_size, float _fov)
{
	// Set world space position and direction
	ws_position = cam_to_world.multVecByMatrix4x4(positionWS);
	ws_direction = directionWS;

	// Set the dimension of the camera
	size = cam_size;

	fov = _fov;

	// Set the aspect ratio based on camera size
	aspect_ratio = size.getX() / size.getY();
	scale = tan(deg2rad(fov) * 0.5f);
}

void Camera::Render(std::vector<Primitive> primitives, std::vector<Pixel>& buffer, BVH::Builder bvh, Light::DirectionLight light)
{
	int iter = 0;
	for (int y = 0; y < static_cast<int>(size.getY()); ++y)
	{
		for (int x = 0; x < static_cast<int>(size.getX()); ++x)
		{
			// Create a pixel
			Pixel pixel;

			// Convert pixel from raster space to camera space
			float Px = (2.0f * ((x + 0.5f) / size.getX()) - 1.0f) * tan(fov / 2.0f * Maths::special::pi / 180.0f) * aspect_ratio * scale;
			float Py = (1.0f - 2.0f * ((y + 0.5f) / size.getY()) * tan(fov / 2.0f * Maths::special::pi / 180.0f));
			pixel.position.setX(Px);
			pixel.position.setY(Py);

			// Convert pixel camera space to world space
			Vector3 pixelPosWS;
			cam_to_world.multDirByMatrix4x4(Vector3(pixel.position.getX(), pixel.position.getY(), ws_direction.getZ() /*-1.0f*/), pixelPosWS);
			Vector3::normalize(pixelPosWS);

			// Create ray that's origin is the camera and it's direction towards the pixel
			RayTrace::Ray primary_rayWS;
			primary_rayWS.setOrigin(ws_position);
			primary_rayWS.setDirection(Vector3::normalize(pixelPosWS - primary_rayWS.getOrigin()));

			float tnear = Maths::special::infinity;

			if (bvh.hit(primary_rayWS, primitives, tnear))
			{
				Colour albedo = { 1.0f, 1.0f, 1.0f };

				Vector3 L = { 0.0f, 1.0f, 0.0f }; //{ 0.5f, 0.0f, 1.0f };
				Vector3 N = primary_rayWS.getHitData().normal;

				Vector3 hitpoint = primary_rayWS.getHitPoint();
				primary_rayWS.setOrigin(hitpoint + N);

				bool visible = !bvh.hit(primary_rayWS, primitives, tnear);
				buffer.at(iter).colour = visible * albedo / Maths::special::pi * light.getIntensity() * light.getColour() * std::max(0.0f, Vector3::dot(L, N));
			}
			else
			{
				buffer.at(iter).colour = Colour(0.5f, 0.5f, 1.0f);
			}


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


			//for(auto& prim : primitives)
			//{
			//	//if (prim.intersectedBoundingBoxDebug(primary_rayWS))
			//	//{
			//	//	buffer.at(iter).colour = Colour(1.0f, 1.0f, 1.0f);
			//	//}

			//	float tn = -Maths::special::infinity;
			//	float tf = Maths::special::infinity;

			//	if (Intersection::minMaxBounds(primary_rayWS, prim.getBoundingBox()))
			//	{
			//		buffer.at(iter).colour = primary_rayWS.data.normal;
			//	}
			//	else
			//	{
			//		buffer.at(iter).colour = Colour(0.5f, 0.5f, 1.0f);
			//	}
			//}
			iter++;
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
