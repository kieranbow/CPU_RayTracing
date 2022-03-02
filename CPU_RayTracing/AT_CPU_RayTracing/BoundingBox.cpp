#include "BoundingBox.h"
#include "Ray.h"

void BoundingBox::generateBoundingBox(std::vector<Vertex>& vertex_buffer)
{
	// Generates a bounding box using the slab method as mention by Kay and Kajiya in 1986
	planes.at(axis::x).normal = { 1.0f, 0.0f, 0.0f };
	planes.at(axis::y).normal = { 0.0f, 1.0f, 0.0f };
	planes.at(axis::z).normal = { 0.0f, 0.0f, 1.0f };

	// Loop through each vertex and calculate the axis plane's near and far values
	for (auto& plane : planes)
	{
		for (auto & vert : vertex_buffer)
		{
			float d = Vector3::dot(plane.normal, vert.position);
			if (d < plane.near) plane.near = d;
			if (d > plane.far) plane.far = d;
		}
	}

	
	//for (auto& vert : vertex_buffer)
	//{
	//	for (auto& plane : planes)
	//	{
	//		float d = Vector3::dot(plane.normal, vert.position);
	//		if (d < plane.near) plane.near = d;
	//		if (d > plane.far) plane.far = d;
	//	}
	//}

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
	// https://www.scratchapixel.com/lessons/advanced-rendering/introduction-acceleration-structure/bounding-volume-hierarchy-BVH-part1

	// This kinda works
	//float tminX = (min_bounds.getX() - ray.origin.getX()) / ray.direction.getX();
	//float tmaxX = (max_bounds.getX() - ray.origin.getX()) / ray.direction.getX();
	//if (tminX > tmaxX) std::swap(tminX, tmaxX);

	//float tminY = (min_bounds.getY() - ray.origin.getY()) / ray.direction.getY();
	//float tmaxY = (max_bounds.getY() - ray.origin.getY()) / ray.direction.getY();
	//if (tminY > tmaxY) std::swap(tminY, tmaxY);

	//if ((tminX > tmaxY) || (tminY > tmaxX)) return false;

	//if (tminY > tminX) tminX = tminY;
	//if (tmaxY > tmaxX) tmaxX = tmaxY;

	//float tminZ = (min_bounds.getZ() - ray.origin.getZ()) / ray.direction.getZ();
	//float tmaxZ = (max_bounds.getZ() - ray.origin.getZ()) / ray.direction.getZ();
	//if (tminZ > tmaxZ) std::swap(tminZ, tmaxZ);

	//if ((tminX > tmaxZ) || (tminZ > tmaxX)) return false;

	//if (tminZ > tminX) tminX = tminZ;
	//if (tmaxZ > tmaxX) tmaxX = tmaxZ;

	//return true;

	std::array<float, 3>precomuteNumerator;
	std::array<float, 3>precomputeDemoninator;

	for (int i = 0; i < planes.size(); i++)
	{
		precomuteNumerator.at(i) = Vector3::dot(planes.at(i).normal, ray.origin);
		precomputeDemoninator.at(i) = Vector3::dot(planes.at(i).normal, ray.direction);
	}

	for (int i = 0; i < planes.size(); i++)
	{
		float tn = (planes.at(i).near - precomuteNumerator.at(i)) / precomputeDemoninator.at(i);
		float tf = (planes.at(i).far - precomuteNumerator.at(i)) / precomputeDemoninator.at(i);

		if (precomputeDemoninator.at(i) < 0.0f) std::swap(tn, tf);
		if (tn > tnear) tnear = tn;
		if (tf < tfar) tfar = tf;
		if (tnear > tfar) return false;
	}
	return true;

	//for (auto& plane : planes)
	//{
	//	float NdotO = Vector3::dot(plane.normal, ray.origin);
	//	float NdotD = Vector3::dot(plane.normal, ray.direction);

	//	float tn = (plane.near - NdotO) / NdotD;
	//	float tf = (plane.far - NdotO) / NdotD;

	//	if (NdotD < 0.0f) std::swap(tn, tf);
	//	if (tn > plane.near) tnear = tn;
	//	if (tf > plane.far) tfar = tf;
	//	if (tnear > tfar) return false;
	//}
	//return true;

	//float tmin = -k_infinity, tmax = k_infinity;
	//float invert_dir_x = 1.0f - ray.direction.getX();
	//float invert_dir_y = 1.0f - ray.direction.getY();
	//float invert_dir_z = 1.0f - ray.direction.getZ();

	//float tx1 = (min_bounds.getX() - ray.origin.getX()) * invert_dir_x;
	//float tx2 = (max_bounds.getX() - ray.origin.getX()) * invert_dir_x;

	//tmin = std::fmax(tmin, std::fmin(tx1, tx2));
	//tmax = std::fmin(tmax, std::fmax(tx1, tx2));

	//float ty1 = (min_bounds.getY() - ray.origin.getY()) * invert_dir_y;
	//float ty2 = (max_bounds.getY() - ray.origin.getY()) * invert_dir_y;

	//tmin = std::fmax(tmin, std::fmin(ty1, ty2));
	//tmax = std::fmin(tmax, std::fmax(ty1, ty2));

	//float tz1 = (min_bounds.getZ() - ray.origin.getZ()) * invert_dir_z;
	//float tz2 = (max_bounds.getZ() - ray.origin.getZ()) * invert_dir_z;

	//tmin = std::fmax(tmin, std::fmin(tz1, tz2));
	//tmax = std::fmin(tmax, std::fmax(tz1, tz2));

	//return tmax >= std::fmax(0.0f, tmin) && tmin < ray.t;
	
	
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
