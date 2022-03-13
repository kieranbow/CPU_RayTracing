#include "Primitive.h"
#include "Ray.h"
#include "Matrix4x4.h"
#include "Colour.h"
#include "Intersection.h"

Primitive::Primitive()
{
	// Load default unit cube and pass the data to the vertex and index buffers
	MeshLoader loader("Assets\\Unit_Cube.obj", vertex_buffer, index_buffer);

	Matrix4x4 objectToWorld;

	// Convert vertices from local space to world space
	for (auto& vert : vertex_buffer)
	{
		Matrix4x4::multVecByMatrix4x4(objectToWorld, vert.position);
	}

	//for (auto& vert : vertex_buffer)
	//{
	//	Vector3 position = objectToWorld.translation({ 0.0f, 0.0f, -10.0f });
	//	vert.position += position;
	//}

	// Generates a bounding box around the mesh using the slab method
	//boundingBox.generateBoundingBox(vertex_buffer);
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
	// boundingBox.generateBoundingBox(vertex_buffer);
}

Primitive::~Primitive()
{
	// When the primitive is not used.
	// Clear all the data from the vertex and index buffers.
	vertex_buffer.clear();
	index_buffer.clear();
}

bool Primitive::triangleIntersected(RayTrace::Ray& ray)
{
	float tn = -Maths::special::infinity;
	float tf = Maths::special::infinity;

	// Check if ray hits the aabb bounding box
	if (Intersection::slab(ray, boundingBox, tn, tf) /*boundingBox.slabIntersected(ray, tn, tf)*/)
	{
		// If the ray does intersect the aabb bounding box
		// Loop through all indices and vertices inside the buffer
		for (int i = 0; i < index_buffer.size(); i += 3)
		{
			int vertex_idx_1 = index_buffer.at(i);
			int vertex_idx_2 = index_buffer.at(i + 1);
			int vertex_idx_3 = index_buffer.at(i + 2);

			// Get the three vertices of a triangle
			Vector3 vert0 = vertex_buffer.at(vertex_idx_1).position;
			Vector3 vert1 = vertex_buffer.at(vertex_idx_2).position;
			Vector3 vert2 = vertex_buffer.at(vertex_idx_3).position;

			Vector3 vert0_n = vertex_buffer.at(vertex_idx_1).normal;
			Vector3 vert1_n = vertex_buffer.at(vertex_idx_2).normal;
			Vector3 vert2_n = vertex_buffer.at(vertex_idx_3).normal;

			// Construct a triangle and test if ray hits that triangle
			if (MollerTrumboreIntersection(ray, vert0, vert1, vert2))
			{
				ray.data.colour = Colour(1.0f, 1.0f, 1.0f);
				ray.data.normal = Vector3::normalize((1.0f - ray.data.uv.getX() - ray.data.uv.getY()) * vert0_n + ray.data.uv.getX() * vert1_n + ray.data.uv.getY() * vert2_n);
				//ray.data.normal = Vector3::normalize(Vector3::cross(vert1 - vert0, vert2 - vert0));
				return true;
			}
		}
	}
	return false;
}

bool Primitive::intersectedBoundingBoxDebug(RayTrace::Ray& ray)
{
	float tn = -Maths::special::infinity;
	float tf = Maths::special::infinity;

	if (Intersection::slab(ray, boundingBox, tn ,tf))
	{
		return true;
	}

	//if (boundingBox.slabIntersected(ray, tn, tf))
	//{
	//	return true;
	//}
	return false;
}

bool Primitive::generateBoundingBox()
{
	boundingBox.generateBoundingBox(vertex_buffer);
	return true;
}

void Primitive::setPosition(Vector3 position)
{
	Matrix4x4 matrix;
	ws_position += matrix.translation(position);

	for (auto& vert : vertex_buffer)
	{
		vert.position += ws_position;
	}



	// boundingBox.generateBoundingBox(vertex_buffer);
	boundingBox.generateBoundingBox(vertex_buffer);
}

void Primitive::setScale(Vector3 scale)
{
	Matrix4x4 matrix;
	
	for (auto& vert : vertex_buffer)
	{
		vert.position = matrix.scale(scale, vert.position);
	}

	// boundingBox.generateBoundingBox(vertex_buffer);
	boundingBox.generateBoundingBox(vertex_buffer);
}

bool Primitive::MollerTrumboreIntersection(RayTrace::Ray& ray, Vector3 vert0, Vector3 vert1, Vector3 vert2)
{
	// https://cadxfem.org/inf/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
	// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection

	// Find the two edge vectors
	Vector3 v0v1 = vert1 - vert0;
	Vector3 v0v2 = vert2 - vert0;

	// Begin calculating determinant - also used to calculate U parameter
	Vector3 pvec = Vector3::cross(ray.direction, v0v2);

	float det = Vector3::dot(pvec, v0v1);

	// if the determinant is close to 0, the ray misses the triangle
	if (det < Maths::special::epsilon) return false; // Culls backface triangles

	float invDet = 1.0f / det;

	// Calculate distance from vert0 to ray's origin
	Vector3 tvec = ray.origin - vert0;

	// Calculate U parameter and test bounds
	ray.data.uv.setX(Vector3::dot(tvec, pvec) * invDet);
	if (ray.data.uv.getX() < 0.0f || ray.data.uv.getX() > 1.0f) return false;

	// Prepare to test V parameter
	Vector3 qvec = Vector3::cross(tvec, v0v1);

	// Calculate V parameter and test bounds
	ray.data.uv.setY(Vector3::dot(ray.direction, qvec) * invDet);
	if (ray.data.uv.getY() < 0.0f || ray.data.uv.getX() + ray.data.uv.getY() > 1.0f) return false; // u + v should never be greater than 1

	// Calculate t, ray intersection triangle
	ray.t = Vector3::dot(v0v2, qvec) * invDet;

	return true;
}
