#pragma once

#include "Ray.h"
#include "BoundingBox.h"

class Vector3;
struct Triangle;

namespace Intersection
{
	// Calculates a triangle and tests if a ray has intersected it
	bool MollerTrumbore(RayTrace::Ray& ray, Triangle triangle);

	// Checks if a ray has intersected the slab planes that make up the bounding box
	bool slab(RayTrace::Ray& ray, BoundingBox::AABB aabb, float& tnear, float& tfar);

	// Checks if a ray has intersected the two min and max points of a bounding box
	bool minMaxBounds(RayTrace::Ray& ray, BoundingBox::AABB bounds);
}
