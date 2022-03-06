#pragma once
#include <vector>
#include <array>

#include "Vector3.h"
#include "Vertex.h"
#include "Numbers.h"

class Ray;

namespace BoundingBox
{
	struct Extent
	{
		Vector3 min_extent;
		Vector3 max_extent;
	};

	// A class that generates and stores a bounding box based off objects size
	class AABB
	{
		public:
			AABB() = default;
			~AABB() = default;

			// Loops through the obj vertex buffer and generate a bounding box using the slab method
			void generateBoundingBox(std::vector<Vertex>& vertex_buffer);

			// Checks if a ray has intersected the slab planes that make up the bounding box
			bool intersected(Ray& ray, float& tnear, float& tfar);

			// Returns the min and max points that make up the bounds
			const Extent& getBounds() const { return bounds; }

		private:
			struct Plane
			{
				Vector3 normal = { 0.0f, 0.0f, 0.0f };
				float near = k_infinity;
				float far = -k_infinity;;
			};

			enum axis { x, y, z };
			static const int max_num_plane = 3;

			std::array<Plane, max_num_plane> planes;
			Extent bounds;
	};
}

