#pragma once
#include <vector>
#include <array>

#include "Vector3.h"
#include "MeshData.h"
#include "Maths.h"
#include "Ray.h"

namespace BoundingBox
{
	// Contains the min and max points for a bounding box
	struct Bounds
	{
		Vector3 min = { Maths::special::infinity, Maths::special::infinity, Maths::special::infinity };
		Vector3 max = { -Maths::special::infinity, -Maths::special::infinity, -Maths::special::infinity };
	};

	// A class that generates and stores a bounding box based off objects size
	class AABB
	{
		private:
			struct Plane
			{
				Vector3 normal = { 0.0f, 0.0f, 0.0f };
				float near = Maths::special::infinity;
				float far = -Maths::special::infinity;
			};

			static constexpr int max_num_plane = 3;

			std::array<Plane, max_num_plane> m_planes;
			Bounds m_bounds;
			Vector3 m_centroid;

		public:
			AABB();
			~AABB() = default;

			// Loops through the obj vertex buffer and generate a bounding box using the slab method
			void generateBoundingBox(std::vector<Vertex>& vertex_buffer);
			void generateBoundingBox(const std::vector<Triangle>& triangles);

			// Computes a new bounding box around two separate bounding boxes
			static Bounds combineBounds(AABB& b1, AABB& b2);

			void setBounds(const Bounds _bounds);
			void setBounds(const Vector3 _min, const Vector3 _max);
			void setBoundsMinX(float min) { m_bounds.min.setX(min); }
			void setBoundsMinY(float min) { m_bounds.min.setY(min); }
			void setBoundsMinZ(float min) { m_bounds.min.setZ(min); }
			void setBoundsMaxX(float max) { m_bounds.max.setX(max); }
			void setBoundsMaxY(float max) { m_bounds.max.setY(max); }
			void setBoundsMaxZ(float max) { m_bounds.max.setZ(max); }

			// Returns the min and max points that make up the bounds
			const Bounds& getBounds() const { return m_bounds; }

			// Returns the planes used to generate the slabs
			const std::array<Plane, max_num_plane>& getPlanes() const { return m_planes; }

			// Returns the centre point of the bounding box
			const Vector3& getCentroid() const { return m_centroid; }
	};
}
