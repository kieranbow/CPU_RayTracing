#include "Camera.h"
#include "Primitive.h"

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

void Camera::Render(/*std::vector<Primitive> primitives, */std::vector<Pixel>& buffer, BVH::Accelerator bvh)
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
			primary_rayWS.origin = ws_position;
			primary_rayWS.direction = Vector3::normalize(pixelPosWS - primary_rayWS.origin);


			if (bvh.hit(primary_rayWS))
			{
				if (primary_rayWS.t >= primary_rayWS.t_near && primary_rayWS.t <= primary_rayWS.t_far)
				{
					buffer.at(iter).colour = primary_rayWS.data.normal;
				}
			}
			else
			{
				buffer.at(iter).colour = Colour(0.5f, 0.5f, 1.0f);
			}
			iter++;
		}
	}
}

bool Camera::intersect(RayTrace::Ray& ray, Vector3 center, float radius)
{
	Vector3 oc = ray.origin - center;
	float a = Vector3::dot(ray.direction, ray.direction);
	float b = 2.0f * Vector3::dot(oc, ray.direction);
	float c = Vector3::dot(oc, oc) - radius * radius;
	float distriminant = b * b - 4 * a * c;

	return (distriminant > 0.0f);
}

//for(auto& prim : primitives)
//{
//	//if (prim.intersectedBoundingBoxDebug(primary_rayWS))
//	//{
//	//	buffer.at(iter).colour = Colour(1.0f, 1.0f, 1.0f);
//	//}

//	if (prim.intersected(primary_rayWS))
//	{
//		buffer.at(iter).colour = primary_rayWS.data.normal;
//	}
//	//else
//	//{
//	//	buffer.at(iter).colour = Colour(0.5f, 0.5f, 1.0f);
//	//}
//}