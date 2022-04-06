#include "BoundingBox.h"
#include "Ray.h"

BoundingBox::AABB::AABB()
{
	m_bounds.min.setX(Maths::special::infinity);
	m_bounds.min.setY(Maths::special::infinity);
	m_bounds.min.setZ(Maths::special::infinity);

	m_bounds.max.setX(-Maths::special::infinity);
	m_bounds.max.setY(-Maths::special::infinity);
	m_bounds.max.setZ(-Maths::special::infinity);
}

void BoundingBox::AABB::generateBoundingBox(std::vector<Vertex>& vertex_buffer)
{
	// Generates a bounding box using the slab method as mention by Kay and Kajiya (1986)
	m_planes[Maths::coord::x].normal = { 1.0f, 0.0f, 0.0f };
	m_planes[Maths::coord::y].normal = { 0.0f, 1.0f, 0.0f };
	m_planes[Maths::coord::z].normal = { 0.0f, 0.0f, 1.0f };

	// Loop through each plane and check each vertex to find the planes near and far values
	for (auto& plane : m_planes)
	{
		for (auto & vert : vertex_buffer)
		{
			float d = Vector3::dot(plane.normal, vert.position);
			if (d < plane.near) plane.near = d;
			if (d > plane.far) plane.far = d;
		}
	}

	m_bounds.min = { m_planes[Maths::coord::x].near, m_planes[Maths::coord::y].near, m_planes[Maths::coord::z].near };
	m_bounds.max = { m_planes[Maths::coord::x].far, m_planes[Maths::coord::y].far, m_planes[Maths::coord::z].far };

	// Create centroid of bounding box
	m_centroid.setX(0.5f * m_bounds.min.getX() + 0.5f * m_bounds.max.getX());
	m_centroid.setY(0.5f * m_bounds.min.getY() + 0.5f * m_bounds.max.getY());
	m_centroid.setZ(0.5f * m_bounds.min.getZ() + 0.5f * m_bounds.max.getZ());
}

void BoundingBox::AABB::generateBoundingBox(const std::vector<Triangle>& triangles)
{
	float x_min = Maths::special::infinity; 
	float x_max = -Maths::special::infinity;
	float y_min = Maths::special::infinity;
	float y_max = -Maths::special::infinity;
	float z_min = Maths::special::infinity;
	float z_max = -Maths::special::infinity;

	for (auto& tri : triangles)
	{
		std::array<Vertex, 3> temp;
		temp[0] = tri.vert0;
		temp[1] = tri.vert1;
		temp[2] = tri.vert1;

		for (auto& vert : temp)
		{
			x_max = std::max(x_max, vert.position.getX());
			x_min = std::min(x_min, vert.position.getX());

			y_max = std::max(y_max, vert.position.getY());
			y_min = std::min(y_min, vert.position.getY());

			z_max = std::max(z_max, vert.position.getZ());
			z_min = std::min(z_min, vert.position.getZ());
		}
	}

	m_bounds.min = { x_min, y_min, z_min };
	m_bounds.max = { x_max, y_max, z_max };

	// Create centroid of bounding box
	m_centroid.setX(0.5f * m_bounds.min.getX() + 0.5f * m_bounds.max.getX());
	m_centroid.setY(0.5f * m_bounds.min.getY() + 0.5f * m_bounds.max.getY());
	m_centroid.setZ(0.5f * m_bounds.min.getZ() + 0.5f * m_bounds.max.getZ());
}

BoundingBox::Bounds BoundingBox::AABB::combineBounds(AABB& b1, AABB& b2)
{
	// https://pbr-book.org/3ed-2018/Geometry_and_Transformations/Bounding_Boxes#fragment-GeometryInlineFunctions-19
	// https://raytracing.github.io/books/RayTracingTheNextWeek.html#boundingvolumehierarchies
	
	BoundingBox::Bounds bounds;
	bounds.min.setX(std::min(b1.m_bounds.min.getX(), b2.m_bounds.min.getX()));
	bounds.min.setY(std::min(b1.m_bounds.min.getY(), b2.m_bounds.min.getY()));
	bounds.min.setZ(std::min(b1.m_bounds.min.getZ(), b2.m_bounds.min.getZ()));

	bounds.max.setX(std::max(b1.m_bounds.max.getX(), b2.m_bounds.max.getX()));
	bounds.max.setY(std::max(b1.m_bounds.max.getY(), b2.m_bounds.max.getY()));
	bounds.max.setZ(std::max(b1.m_bounds.max.getZ(), b2.m_bounds.max.getZ()));
	
	b1.m_bounds = bounds;
	// Create centroid of bounding box
	b1.m_centroid.setX(0.5f * bounds.min.getX() + 0.5f * bounds.max.getX());
	b1.m_centroid.setY(0.5f * bounds.min.getY() + 0.5f * bounds.max.getY());
	b1.m_centroid.setZ(0.5f * bounds.min.getZ() + 0.5f * bounds.max.getZ());

	return bounds;
}

void BoundingBox::AABB::setBounds(const Bounds extent)
{
	m_bounds = extent;
}

void BoundingBox::AABB::setBounds(const Vector3 min, const Vector3 max)
{
	m_bounds.min = min;
	m_bounds.max = max;
}
