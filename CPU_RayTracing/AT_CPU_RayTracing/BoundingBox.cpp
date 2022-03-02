#include "BoundingBox.h"
#include "Ray.h"

void BoundingBox::generateBoundingBox(std::vector<Vertex>& vertex_buffer)
{
	// Generates a bounding box using the slab method as mention by Kay and Kajiya in 1986
	planes.at(axis::x).normal = { 1.0f, 0.0f, 0.0f };
	planes.at(axis::y).normal = { 0.0f, 1.0f, 0.0f };
	planes.at(axis::z).normal = { 0.0f, 0.0f, 1.0f };

	// Loop through each vertex and calculate the axis plane's near and far values
	for (auto& vert : vertex_buffer)
	{
		for (auto& plane : planes)
		{
			float d = Vector3::dot(plane.normal, vert.position);
			if (d < plane.near) plane.near = d;
			if (d > plane.far) plane.far = d;
		}
	}

	// Assign each plane axis near and far to the min and max bounding boxes
	min_bounds.setX(planes.at(axis::x).near);
	min_bounds.setY(planes.at(axis::y).near);
	min_bounds.setZ(planes.at(axis::z).near);
	max_bounds.setX(planes.at(axis::x).far);
	max_bounds.setY(planes.at(axis::y).far);
	max_bounds.setZ(planes.at(axis::z).far);
}

bool BoundingBox::intersected(Ray& ray, float& tnear, float& tfar)
{
	// https://tavianator.com/2011/ray_box.html
	// https://raytracing.github.io/books/RayTracingTheNextWeek.html#boundingvolumehierarchies
	// https://github.com/erich666/GraphicsGems/blob/master/gems/RayBox.c
	// https://gamedev.stackexchange.com/questions/184998/ray-box-aabb-is-slower-than-without
	// https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms

	for (auto& plane : planes)
	{
		float NdotO = Vector3::dot(plane.normal, ray.origin);
		float NdotD = Vector3::dot(plane.normal, ray.direction);

		float tn = (plane.near - NdotO) / NdotD;
		float tf = (plane.far - NdotO) / NdotD;

		if (NdotD < 0.0f) std::swap(tn, tf);
		if (tn > plane.near) tnear = tn;
		if (tf > plane.far) tfar = tf;
		if (tnear > tfar) return false;
	}
	return true;


	//std::array<float, 3> numerator;
	//std::array<float, 3> Denumerator;

	//for (int i = 0; i < 3; i++)
	//{
	//	numerator.at(i) = Vector3::dot(planes.at(i).normal, ray.origin);
	//	Denumerator.at(i) = Vector3::dot(planes.at(i).normal, ray.direction);
	//}

	//for (int i = 0; i < 3; i++)
	//{
	//	float t_near = (planes.at(i).near - numerator.at(i) / Denumerator.at(i));
	//	float t_far = (planes.at(i).far - numerator.at(i) / Denumerator.at(i));

	//	if (Denumerator.at(i) < 0.0f) std::swap(t_near, t_far);
	//	if (t_near > tnear) tnear = t_near;
	//	if (t_far < tfar) tfar = t_far;
	//	
	//	if (tnear > tfar) return false;
	//}
	//return true;
}
