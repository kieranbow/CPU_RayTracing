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
		int vertex_idx_1 = m_indexBuffer[i];
		int vertex_idx_2 = m_indexBuffer[i + 1];
		int vertex_idx_3 = m_indexBuffer[i + 2];

		Triangle triangle;
		triangle.vert0.position = m_vertexBuffer[vertex_idx_1].position;
		triangle.vert0.normal = m_vertexBuffer[vertex_idx_1].normal;

		triangle.vert1.position = m_vertexBuffer[vertex_idx_2].position;
		triangle.vert1.normal = m_vertexBuffer[vertex_idx_2].normal;

		triangle.vert2.position = m_vertexBuffer[vertex_idx_3].position;
		triangle.vert2.normal = m_vertexBuffer[vertex_idx_3].normal;

		float tnear = Maths::special::infinity;
		float tfar = -Maths::special::infinity;

		if (Intersection::slab(ray, m_boundingBox, tnear, tfar))
		{
			// Construct a triangle and test if ray hits that triangle
			if (Intersection::MollerTrumbore(ray, triangle) && ray.getT() < tnear)
			{
				// Assign tnear to be the rays t value
				tnear = ray.getT();

				// Get the material from the object
				ray.getHitData().material = m_material;

				// Override the materials albedo with a texture if one exists
				if (!m_albedo.empty())
				{
					ray.getHitData().material.albedo = m_albedo.at(Shaders::Functions::getUVCoords(ray.getHitData().uv, triangle));
				}
				else
				{
					ray.getHitData().material.albedo = m_material.albedo; //Colour(u, v, 1.0f - u - v);
				}

				// Override the materials normal with the smooth normals from the object
				ray.getHitData().material.normal = Shaders::Functions::getSmoothNormalFromTri(triangle, ray.getHitData());

				// Set the hitpoint of the ray. This is important for the lighting and shading of the scene
				ray.getHitData().hitPoint = (ray.getOrigin() + ray.getDirection() * ray.getT()) + ray.getHitData().normal;
				return true;
			}
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
	m_boundingBox.generateBoundingBox(m_vertexBuffer);
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
