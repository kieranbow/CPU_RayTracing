#pragma once
#include <vector>
#include <array>

#include "Vector3.h"
#include "Vertex.h"

class Ray;

class BoundingBox
{
	private:
		struct Plane
		{
			Vector3 normal = { 0.0f, 0.0f, 0.0f };
			float near = -k_infinity;
			float far = k_infinity;
		};

		enum axis
		{
			x,
			y,
			z
		};

	public:
		BoundingBox() = default;
	
		// Loops through obj vertex buffer and generate a bounding box
		void generateBoundingBox(std::vector<Vertex>& vertex_buffer);

		bool intersected(Ray& ray, float& tnear, float& tfar);

		const std::array<Plane, 3>& getBounds() const { return planes; }
		const Vector3& getMinBounds() const { return min_bounds; }
		const Vector3& getMaxBounds() const { return max_bounds; }

	private:
		Vector3 min_bounds	= { 0.0f, 0.0f, 0.0f };
		Vector3 max_bounds	= { 0.0f, 0.0f, 0.0f };

		std::array<Plane, 3> planes;
};
