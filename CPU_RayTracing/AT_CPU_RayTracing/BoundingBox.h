#pragma once
#include <vector>
#include <array>

#include "Vector3.h"
#include "Vertex.h"
#include "Maths.h"

class Ray;

namespace BoundingBox
{
	// Contains the min and max points for a bounding box
	struct Bounds
	{
		Vector3 min = { Maths::special::k_infinity, Maths::special::k_infinity, Maths::special::k_infinity };
		Vector3 max = { -Maths::special::k_infinity, -Maths::special::k_infinity, -Maths::special::k_infinity };
	};

	// A class that generates and stores a bounding box based off objects size
	class AABB
	{
	private:
		struct Plane
		{
			Vector3 normal = { 0.0f, 0.0f, 0.0f };
			float near = Maths::special::k_infinity;
			float far = -Maths::special::k_infinity;
		};

		enum axis { x, y, z };
		static const int max_num_plane = 3;

		std::array<Plane, max_num_plane> planes;
		Bounds bounds;
		Vector3 centroid;

		public:
			AABB() = default;
			~AABB() = default;

			// Loops through the obj vertex buffer and generate a bounding box using the slab method
			void generateBoundingBox(std::vector<Vertex>& _vertex_buffer);

			// Checks if a ray has intersected the slab planes that make up the bounding box
			bool intersected(Ray& ray, float& tnear, float& tfar);

			// Computes a new bounding box around two separate bounding boxes
			static Bounds combineBounds(AABB& b1, AABB& b2);

			void setBounds(const Bounds _bounds);
			void setBounds(const Vector3 _min, const Vector3 _max);
			void setBoundsMinX(float min) { bounds.min.setX(min); }
			void setBoundsMinY(float min) { bounds.min.setY(min); }
			void setBoundsMinZ(float min) { bounds.min.setZ(min); }
			void setBoundsMaxX(float max) { bounds.max.setX(max); }
			void setBoundsMaxY(float max) { bounds.max.setY(max); }
			void setBoundsMaxZ(float max) { bounds.max.setZ(max); }

			// Returns the min and max points that make up the bounds
			const Bounds& getBounds() const { return bounds; }
			const std::array<Plane, max_num_plane>& getPlanes() const { return planes; }
			const Vector3& getCentroid() const { return centroid; }
	};
}
