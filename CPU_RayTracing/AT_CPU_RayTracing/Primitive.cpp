#include "Primitive.h"
#include "Ray.h"
#include "Matrix4x4.h"
#include "Colour.h"
#include "Intersection.h"
#include "MeshData.h"
#include "ShaderFunc.h"

Primitive::Primitive()
{
	// Load default unit cube and pass the data to the vertex and index buffers
	MeshLoader loader("Assets\\Unit_Cube.obj", m_vertexBuffer, m_indexBuffer);

	Matrix4x4 objectToWorld;

	// Convert vertices from local space to world space
	for (auto& vert : m_vertexBuffer)
	{
		Matrix4x4::multVecByMatrix4x4(objectToWorld, vert.position);
	}

	// Generates a bounding box around the mesh using the slab method
	//m_boundingBox.generateBoundingBox(m_vertexBuffer);
}

Primitive::Primitive(std::string file_path, Vector3 positionWS)
{
	// Load mesh and pass the data to the vertex and index buffers
	MeshLoader loader(file_path, m_vertexBuffer, m_indexBuffer);

	Matrix4x4 objectToWorld;

	for (auto& vert : m_vertexBuffer)
	{
		Matrix4x4::multVecByMatrix4x4(objectToWorld, vert.position);
	}

	m_position = positionWS;

	// Generates a bounding box around the mesh using the slab method
	// m_boundingBox.generateBoundingBox(m_vertexBuffer);
}

Primitive::~Primitive()
{
	// When the primitive is not used.
	// Clear all the data from the vertex and index buffers.
	m_vertexBuffer.clear();
	m_indexBuffer.clear();
}

bool Primitive::triangleIntersected(Raycast::Ray& ray)
{
	float tn = -Maths::special::infinity;
	float tf = Maths::special::infinity;

	// If the ray does intersect the aabb bounding box
	// Loop through all indices and vertices inside the buffer
	for (int i = 0; i < m_indexBuffer.size(); i += 3)
	{
		int vertex_idx_1 = m_indexBuffer.at(i);
		int vertex_idx_2 = m_indexBuffer.at(i + 1);
		int vertex_idx_3 = m_indexBuffer.at(i + 2);

		Triangle triangle;
		triangle.vert0.position = m_vertexBuffer.at(vertex_idx_1).position;
		triangle.vert0.normal = m_vertexBuffer.at(vertex_idx_1).normal;

		triangle.vert1.position = m_vertexBuffer.at(vertex_idx_2).position;
		triangle.vert1.normal = m_vertexBuffer.at(vertex_idx_2).normal;

		triangle.vert2.position = m_vertexBuffer.at(vertex_idx_3).position;
		triangle.vert2.normal = m_vertexBuffer.at(vertex_idx_3).normal;

		// Construct a triangle and test if ray hits that triangle
		if (Intersection::MollerTrumbore(ray, triangle))
		{
			ray.getHitData().normal = Shaders::Functions::getSmoothNormalFromTri(triangle, ray.getHitData());
			return true;
		}
	}
	return false;
}

void Primitive::setPosition(Vector3 position)
{
	// Move each vertex to the new position using a matrix
	Matrix4x4 matrix;

	for (auto& vert : m_vertexBuffer)
	{
		vert.position += matrix.translation(position);;
	}

	// Create a new bounding box arond the new vertex positions
	//m_boundingBox.generateBoundingBox(m_vertexBuffer);
}

void Primitive::setScale(Vector3 scale)
{
	Matrix4x4 matrix;
	
	for (auto& vert : m_vertexBuffer)
	{
		vert.position = matrix.scale(scale, vert.position);
	}

	// boundingBox.generateBoundingBox(vertex_buffer);
	m_boundingBox.generateBoundingBox(m_vertexBuffer);
}
