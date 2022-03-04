#pragma once
#include <vector>
#include <array>

#include "Vector3.h"
#include "Vertex.h"

class Ray;

// A class that generates and stores a bounding box based off objects size
class BoundingBox
{
	public:
		BoundingBox() = default;
		~BoundingBox() = default;

		struct Bounds
		{
			Vector3 min_bounds;
			Vector3 max_bounds;
		};

		// Loops through the obj vertex buffer and generate a bounding box using the slab method
		void generateBoundingBox(std::vector<Vertex>& vertex_buffer);

		// Checks if a ray has intersected the slab planes that make up the bounding box
		bool intersected(Ray& ray, float& tnear, float& tfar);

		// Returns the min and max points that make up the bounds
		const Bounds& getBounds() const { return bounds; }

	private:
		struct Plane
		{
			Vector3 normal = { 0.0f, 0.0f, 0.0f };
			float near = k_infinity;
			float far = -k_infinity;
		};

		enum axis { x, y, z };
		static const int max_num_plane = 3;
		
		std::array<Plane, max_num_plane> planes;
		Bounds bounds;
};
