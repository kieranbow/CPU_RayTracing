#include "BoundingBox.h"
#include "Ray.h"

void BoundingBox::AABB::generateBoundingBox(std::vector<Vertex>& vertex_buffer)
{
	// Generates a bounding box using the slab method as mention by Kay and Kajiya (1986)
	planes.at(Maths::coord::x).normal = { 1.0f, 0.0f, 0.0f };
	planes.at(Maths::coord::y).normal = { 0.0f, 1.0f, 0.0f };
	planes.at(Maths::coord::z).normal = { 0.0f, 0.0f, 1.0f };

	// Loop through each plane and check each vertex to find the planes near and far values
	for (auto& plane : planes)
	{
		for (auto & vert : vertex_buffer)
		{
			float d = Vector3::dot(plane.normal, vert.position);
			if (d < plane.near) plane.near = d;
			if (d > plane.far) plane.far = d;
		}
	}

	bounds.min = { planes.at(Maths::coord::x).near, planes.at(Maths::coord::y).near, planes.at(Maths::coord::z).near };
	bounds.max = { planes.at(Maths::coord::x).far, planes.at(Maths::coord::y).far, planes.at(Maths::coord::z).far };

	// Create centroid of bounding box
	centroid.setX(0.5f * bounds.min.getX() + 0.5f * bounds.max.getX());
	centroid.setY(0.5f * bounds.min.getY() + 0.5f * bounds.max.getY());
	centroid.setZ(0.5f * bounds.min.getZ() + 0.5f * bounds.max.getZ());
}

void BoundingBox::AABB::generateBoundingBox(const std::vector<Triangle>& triangles)
{
	float x_min = Maths::special::infinity; 
	float x_max = -Maths::special::infinity;
	float y_min = Maths::special::infinity;
	float y_max = -Maths::special::infinity;
	float z_min = Maths::special::infinity;
	float z_max = -Maths::special::infinity;


	for (int i = 0; i < triangles.size(); i++)
	{
		for (int j = 0; j < triangles.at(i).vertices.size(); j++)
		{
			x_max = std::max(x_max, triangles.at(i).vertices.at(j).position.getX());
			x_min = std::min(x_min, triangles.at(i).vertices.at(j).position.getX());

			y_max = std::max(y_max, triangles.at(i).vertices.at(j).position.getY());
			y_min = std::min(y_min, triangles.at(i).vertices.at(j).position.getY());

			z_max = std::max(z_max, triangles.at(i).vertices.at(j).position.getZ());
			z_min = std::min(z_min, triangles.at(i).vertices.at(j).position.getZ());
		}
	}

	bounds.min = { x_min, y_min, z_min };
	bounds.max = { x_max, y_max, z_max };

	// Create centroid of bounding box
	centroid.setX(0.5f * bounds.min.getX() + 0.5f * bounds.max.getX());
	centroid.setY(0.5f * bounds.min.getY() + 0.5f * bounds.max.getY());
	centroid.setZ(0.5f * bounds.min.getZ() + 0.5f * bounds.max.getZ());
}

BoundingBox::Bounds BoundingBox::AABB::combineBounds(AABB& b1, AABB& b2)
{
	// https://pbr-book.org/3ed-2018/Geometry_and_Transformations/Bounding_Boxes#fragment-GeometryInlineFunctions-19
	// https://raytracing.github.io/books/RayTracingTheNextWeek.html#boundingvolumehierarchies
	
	BoundingBox::Bounds bounds;
	bounds.min.setX(std::min(b1.bounds.min.getX(), b2.bounds.min.getX()));
	bounds.min.setY(std::min(b1.bounds.min.getY(), b2.bounds.min.getY()));
	bounds.min.setZ(std::min(b1.bounds.min.getZ(), b2.bounds.min.getZ()));

	bounds.max.setX(std::max(b1.bounds.max.getX(), b2.bounds.max.getX()));
	bounds.max.setY(std::max(b1.bounds.max.getY(), b2.bounds.max.getY()));
	bounds.max.setZ(std::max(b1.bounds.max.getZ(), b2.bounds.max.getZ()));
	
	b1.bounds = bounds;
	// Create centroid of bounding box
	b1.centroid.setX(0.5f * bounds.min.getX() + 0.5f * bounds.max.getX());
	b1.centroid.setY(0.5f * bounds.min.getY() + 0.5f * bounds.max.getY());
	b1.centroid.setZ(0.5f * bounds.min.getZ() + 0.5f * bounds.max.getZ());

	return bounds;
}

void BoundingBox::AABB::setBounds(const Bounds extent)
{
	bounds = extent;
}

void BoundingBox::AABB::setBounds(const Vector3 min, const Vector3 max)
{
	bounds.min = min;
	bounds.max = max;
}
