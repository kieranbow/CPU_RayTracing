#include "BoundingBox.h"
#include "Ray.h"

void BoundingBox::generateBoundingBox(std::vector<Vertex>& vertex_buffer)
{
	// Generates a bounding box using the slab method as mention by Kay and Kajiya (1986)
	planes.at(axis::x).normal = { 1.0f, 0.0f, 0.0f };
	planes.at(axis::y).normal = { 0.0f, 1.0f, 0.0f };
	planes.at(axis::z).normal = { 0.0f, 0.0f, 1.0f };

	// Loop through each plane and check each vertex to find the planes near and far values
	for (auto& plane : planes)
	{
		for (auto & vert : vertex_buffer)
		{
			// Using dot is the same as
			// plane.normal.x * vert.position.x + plane.normal.y * vert.position.y + plane.normal.z * vert.position.z
			float d = Vector3::dot(plane.normal, vert.position);
			if (d < plane.near) plane.near = d;
			if (d > plane.far) plane.far = d;
		}
	}

	bounds.min_bounds = { planes.at(axis::x).near, planes.at(axis::y).near, planes.at(axis::z).near };
	bounds.max_bounds = { planes.at(axis::x).far, planes.at(axis::y).far, planes.at(axis::z).far };
}

bool BoundingBox::intersected(Ray& ray, float& tnear, float& tfar)
{
	// https://www.scratchapixel.com/lessons/advanced-rendering/introduction-acceleration-structure/bounding-volume-hierarchy-BVH-part1

	for (int i = 0; i < planes.size(); i++)
	{
		// Instead of following what scratchapixel does and precompute the numerator and demoninator
		// Its easier just to compute them on the fly.
		float numerator		= Vector3::dot(planes.at(i).normal, ray.origin);
		float demoninator	= Vector3::dot(planes.at(i).normal, ray.direction);

		float tn = (planes.at(i).near - numerator) / demoninator;
		float tf = (planes.at(i).far - numerator) / demoninator;

		if (demoninator < 0.0f) std::swap(tn, tf);
		if (tn > tnear) tnear = tn;
		if (tf < tfar) tfar = tf;
		if (tnear > tfar) return false;
	}
	return true;
}
