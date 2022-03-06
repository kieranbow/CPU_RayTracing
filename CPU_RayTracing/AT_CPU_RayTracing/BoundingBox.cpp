#include "BoundingBox.h"
#include "Ray.h"

void BoundingBox::AABB::generateBoundingBox(std::vector<Vertex>& vertex_buffer)
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
			float d = Vector3::dot(plane.normal, vert.position);
			if (d < plane.near) plane.near = d;
			if (d > plane.far) plane.far = d;
		}
	}

	bounds.min_extent = { planes.at(axis::x).near, planes.at(axis::y).near, planes.at(axis::z).near };
	bounds.max_extent = { planes.at(axis::x).far, planes.at(axis::y).far, planes.at(axis::z).far };
}

bool BoundingBox::AABB::intersected(Ray& ray, float& tnear, float& tfar)
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

BoundingBox::Extent BoundingBox::AABB::unionBounds(const AABB& b1, const AABB& b2)
{
	// https://pbr-book.org/3ed-2018/Geometry_and_Transformations/Bounding_Boxes#fragment-GeometryInlineFunctions-19
	BoundingBox::Extent extent;
	extent.min_extent.setX(std::min(b1.bounds.min_extent.getX(), b2.bounds.min_extent.getX()));
	extent.min_extent.setY(std::min(b1.bounds.min_extent.getY(), b2.bounds.min_extent.getY()));
	extent.min_extent.setZ(std::min(b1.bounds.min_extent.getZ(), b2.bounds.min_extent.getZ()));

	extent.max_extent.setX(std::max(b1.bounds.max_extent.getX(), b2.bounds.max_extent.getX()));
	extent.max_extent.setY(std::max(b1.bounds.max_extent.getY(), b2.bounds.max_extent.getY()));
	extent.max_extent.setZ(std::max(b1.bounds.max_extent.getZ(), b2.bounds.max_extent.getZ()));
	
	return extent;
}

void BoundingBox::AABB::setBounds(const Extent extent)
{
	bounds = extent;
}

void BoundingBox::AABB::setBounds(const Vector3 min, const Vector3 max)
{
	bounds.min_extent = min;
	bounds.max_extent = max;
}
