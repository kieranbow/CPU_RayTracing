#include "Primitive.h"
#include "Ray.h"
#include "Matrix4x4.h"
#include "Colour.h"
#include "Intersection.h"
#include "MeshData.h"

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

			Triangle triangle;
			triangle.vertices.at(0).position	= vertex_buffer.at(vertex_idx_1).position;
			triangle.vertices.at(0).normal		= vertex_buffer.at(vertex_idx_1).normal;

			triangle.vertices.at(1).position	= vertex_buffer.at(vertex_idx_2).position;
			triangle.vertices.at(1).normal		= vertex_buffer.at(vertex_idx_2).normal;

			triangle.vertices.at(2).position	= vertex_buffer.at(vertex_idx_3).position;
			triangle.vertices.at(2).normal		= vertex_buffer.at(vertex_idx_3).normal;

			// Construct a triangle and test if ray hits that triangle
			if (Intersection::MollerTrumbore(ray, triangle))
			{
				ray.data.colour = Colour(1.0f, 1.0f, 1.0f);
				ray.data.normal = Vector3::normalize((1.0f - ray.data.uv.getX() - ray.data.uv.getY()) * triangle.vertices.at(0).normal + ray.data.uv.getX() * triangle.vertices.at(1).normal + ray.data.uv.getY() * triangle.vertices.at(2).normal);
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
