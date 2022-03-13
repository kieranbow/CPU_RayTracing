#pragma once


#include "Ray.h"
#include "BoundingBox.h"

class Vector3;

namespace Intersection
{
	// Calculates a triangle and tests if a ray has intersected it
	bool MollerTrumbore(RayTrace::Ray& ray, Vector3 vert0, Vector3 vert1, Vector3 vert2);

	// Checks if a ray has intersected the slab planes that make up the bounding box
	bool slab(RayTrace::Ray& ray, BoundingBox::AABB aabb, float& tnear, float& tfar);

	// Checks if a ray has intersected the two min and max points of a bounding box
	bool minMaxBounds(RayTrace::Ray& ray, BoundingBox::AABB bounds);
}
