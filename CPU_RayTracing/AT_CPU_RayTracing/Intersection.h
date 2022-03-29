#pragma once

#include "Ray.h"
#include "BoundingBox.h"

class Vector3;
struct Triangle;

// A namespace containing a set of intersection function used for ray-tracing
namespace Intersection
{
	// Calculates a triangle and tests if a ray has intersected it
	bool MollerTrumbore(Raycast::Ray& ray, Triangle& triangle);

	// Checks if a ray has intersected the slab planes that make up the bounding box
	bool slab(Raycast::Ray& ray, const BoundingBox::AABB& aabb, float& tnear, float& tfar);

	// Checks if a ray has intersected the two min and max points of a bounding box
	bool minMaxBounds(Raycast::Ray& ray, BoundingBox::AABB& bounds);

	// Checks if the ray has hit an implicit sphere
	bool inplicitSphere(Raycast::Ray& ray, float radius, float& t0, float& t1);

	bool raySphere(Raycast::Ray& ray, Vector3 origin, const float radius, float& t0, float& t2);
}
