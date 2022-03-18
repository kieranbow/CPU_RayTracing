#include "Intersection.h"
#include "Vector3.h"
#include "MeshData.h"

bool Intersection::MollerTrumbore(RayTrace::Ray& ray, Triangle triangle)
{
	// https://cadxfem.org/inf/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
	// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection

	// Find the two edge vectors
	Vector3 v0v1 = triangle.vert1.position - triangle.vert0.position;
	Vector3 v0v2 = triangle.vert2.position - triangle.vert0.position;

	// Begin calculating determinant - also used to calculate U parameter
	Vector3 pvec = Vector3::cross(ray.getDirection(), v0v2);

	float det = Vector3::dot(pvec, v0v1);

	// if the determinant is close to 0, the ray misses the triangle
	if (det < Maths::special::epsilon) return false; // Culls backface triangles

	float invDet = 1.0f / det;

	// Calculate distance from vert0 to ray's origin
	Vector3 tvec = ray.getOrigin() - triangle.vert0.position;

	// Calculate U parameter and test bounds
	ray.getHitData().uv.setX(Vector3::dot(tvec, pvec) * invDet);
	if (ray.getHitData().uv.getX() < 0.0f || ray.getHitData().uv.getX() > 1.0f) return false;

	// Prepare to test V parameter
	Vector3 qvec = Vector3::cross(tvec, v0v1);

	// Calculate V parameter and test bounds
	ray.getHitData().uv.setY(Vector3::dot(ray.getDirection(), qvec) * invDet);
	if (ray.getHitData().uv.getY() < 0.0f || ray.getHitData().uv.getX() + ray.getHitData().uv.getY() > 1.0f) return false; // u + v should never be greater than 1

	// Calculate t, ray intersection triangle
	ray.setT(Vector3::dot(v0v2, qvec) * invDet);

	return (ray.getT() > 0.0f) ? true : false;
}

bool Intersection::slab(RayTrace::Ray& ray, BoundingBox::AABB aabb, float& tnear, float& tfar)
{
	// https://www.scratchapixel.com/lessons/advanced-rendering/introduction-acceleration-structure/bounding-volume-hierarchy-BVH-part1

	for (int i = 0; i < aabb.getPlanes().size(); i++)
	{
		// Instead of following what scratchapixel does and precompute the numerator and demoninator
		// Its easier just to compute them on the fly.
		float numerator = Vector3::dot(aabb.getPlanes().at(i).normal, ray.getOrigin());
		float demoninator = Vector3::dot(aabb.getPlanes().at(i).normal, ray.getDirection());

		float tn = (aabb.getPlanes().at(i).near - numerator) / demoninator;
		float tf = (aabb.getPlanes().at(i).far - numerator) / demoninator;

		if (demoninator < 0.0f) std::swap(tn, tf);
		if (tn > tnear) tnear = tn;
		if (tf < tfar) tfar = tf;
		if (tnear > tfar) return false;
	}
	return true;
}

bool Intersection::minMaxBounds(RayTrace::Ray& ray, BoundingBox::AABB bounds)
{
	// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
	
	float tmin_x = (bounds.getBounds().min.getX() - ray.getOrigin().getX()) / ray.getDirection().getX();
	float tmax_x = (bounds.getBounds().max.getX() - ray.getOrigin().getX()) / ray.getDirection().getX();

	if (tmin_x > tmax_x) std::swap(tmin_x, tmax_x);

	float tmin_y = (bounds.getBounds().min.getY() - ray.getOrigin().getY()) / ray.getDirection().getY();
	float tmax_y = (bounds.getBounds().max.getY() - ray.getOrigin().getY()) / ray.getDirection().getY();

	if (tmin_y > tmax_y) std::swap(tmin_y, tmax_y);

	if ((tmin_x > tmax_y) || (tmin_y > tmax_x)) return false;
	if (tmin_y > tmin_x) tmin_x = tmin_y;
	if (tmax_y < tmax_x) tmax_x = tmax_y;

	float tmin_z = (bounds.getBounds().min.getZ() - ray.getOrigin().getZ()) / ray.getDirection().getZ();
	float tmax_z = (bounds.getBounds().max.getZ() - ray.getOrigin().getZ()) / ray.getDirection().getZ();

	if (tmin_z > tmax_z) std::swap(tmin_z, tmax_z);

	if ((tmin_x > tmax_z) || (tmin_z > tmax_x)) return false;
	if (tmin_z > tmin_x) tmin_x = tmin_z;
	if (tmax_z < tmax_x) tmax_x = tmax_z;

	return true;
}

bool Intersection::inplicitSphere(RayTrace::Ray& ray, Vector3 center, float radius)
{
	Vector3 oc = ray.getOrigin() - center;
	float a = Vector3::dot(ray.getDirection(), ray.getDirection());
	float b = 2.0f * Vector3::dot(oc, ray.getDirection());
	float c = Vector3::dot(oc, oc) - Maths::helperFunction::sqr(radius);
	float distriminant = b * b - 4 * a * c;
	return (distriminant > 0.0f);
}
