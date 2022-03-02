#include "Primitive.h"
#include "Ray.h"
#include "Matrix4x4.h"

Primitive::Primitive()
{
	// Load default unit cube and pass the data to the vertex and index buffers
	MeshLoader loader("Assets\\helmet.obj", vertex_buffer, index_buffer);

	Matrix4x4 objectToWorld;

	// Convert obj from local space to world space
	for (auto& vert : vertex_buffer)
	{
		Matrix4x4::multVecByMatrix4x4(objectToWorld, vert.position);
	}

	// Generates a bounding box around the mesh using the slab method
	boundingBox.generateBoundingBox(vertex_buffer);
}

Primitive::Primitive(std::string file_path, Vector3 positionWS)
{
	// Load mesh and pass the data to the vertex and index buffers
	MeshLoader loader(file_path, vertex_buffer, index_buffer);

	Matrix4x4 objectToWorld;

	for (auto& vert : vertex_buffer)
	{
		Matrix4x4::multVecByMatrix4x4(objectToWorld, vert.position);
	}

	ws_position = positionWS;

	// Generates a bounding box around the mesh using the slab method
	boundingBox.generateBoundingBox(vertex_buffer);
}

Primitive::~Primitive()
{
	// When the primitive is not used and is destroyed.
	// Clear all the data from the vertex and index buffers.
	vertex_buffer.clear();
	index_buffer.clear();
}

bool Primitive::intersected(Ray& ray)
{
	float tn = k_infinity;
	float tf = -k_infinity;

	//if (boundingBox.intersected(ray, tn, tf))
	//{
	//	return true;
	//}


	// Loop through all indices inside the buffer
	for (int i = 0; i < index_buffer.size(); i += 3)
	{
		int vertex_idx_1 = index_buffer.at(i);
		int vertex_idx_2 = index_buffer.at(i + 1);
		int vertex_idx_3 = index_buffer.at(i + 2);

		// Get the three vertices of a triangle
		Vector3 vert0 = vertex_buffer.at(vertex_idx_1).position;
		Vector3 vert1 = vertex_buffer.at(vertex_idx_2).position;
		Vector3 vert2 = vertex_buffer.at(vertex_idx_3).position;

		// Test if ray hits the triangle
		if (MollerTrumboreIntersection(ray, vert0, vert1, vert2)) return true;
	}
	return false;
}

bool Primitive::intersected2(Ray& ray)
{
	float tn = -k_infinity;
	float tf = k_infinity;

	if (boundingBox.intersected(ray, tn, tf))
	{
		// std::cout << "hit\n";
		return true;
	}
	return false;
}

// https://cadxfem.org/inf/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
bool Primitive::MollerTrumboreIntersection(Ray& ray, Vector3 vert0, Vector3 vert1, Vector3 vert2)
{
	float u = 0.0f, v = 0.0f;

	// Find the two edge vectors
	Vector3 v0v1 = vert1 - vert0;
	Vector3 v0v2 = vert2 - vert0;

	// Begin calculating determinant - also used to calculate U parameter
	Vector3 pvec = Vector3::cross(ray.direction, v0v2);

	float det = Vector3::dot(pvec, v0v1);

	// if the determinant is close to 0, the ray misses the triangle
	if (det < epsilon) return false; // Culls backface triangles

	float invDet = 1.0f / det;

	// Calculate distance from vert0 to ray's origin
	Vector3 tvec = ray.origin - vert0;

	// Calculate U parameter and test bounds
	u = Vector3::dot(tvec, pvec) * invDet;
	if (u < 0.0f || u > 1.0f) return false;

	// Prepare to test V parameter
	Vector3 qvec = Vector3::cross(tvec, v0v1);

	// Calculate V parameter and test bounds
	v = Vector3::dot(ray.direction, qvec) * invDet;
	if (v < 0.0f || u + v > 1.0f) return false; // u + v should never be greater than 1

	// Calculate t, ray intersection triangle
	ray.t = Vector3::dot(v0v2, qvec) * invDet;

	return true;
}
