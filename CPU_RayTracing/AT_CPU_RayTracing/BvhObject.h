#pragma once
#include "Ray.h"
#include "BoundingBox.h"
#include "Primitive.h"

namespace BVH
{
	namespace Object
	{
		// A node that makes up the tree of a BVH
		struct Node
		{
			// Pointers to left node and right node
			std::shared_ptr<BVH::Object::Node> sp_leftNode;
			std::shared_ptr<BVH::Object::Node> sp_rightNode;

			BoundingBox::AABB m_boundingBox;
			bool m_leaf = false;

			// Node will only contain triangles when it is a leaf.
			std::vector<Triangle> m_triangles;
		};

		// Handles all the bvh buidling and collision testing
		class Accelerator
		{
		public:
			// Builds a bvh from the triangles of a primitives. This tree is top down
			void buildBVHPrimitive(const std::vector<Vertex>& vertex_buffer, const std::vector<Indices>& index_buffer);

			// Checks if a ray has hit any of the bvh bounding boxes
			bool hitPrimitive(RayTrace::Ray& ray, float& tnear);

		private:
			static constexpr size_t m_numOfTris = 4;
			static constexpr int m_max_depth = 6;
			std::shared_ptr<BVH::Object::Node> sp_root;
			std::vector<Triangle> m_triangles;

			// A recursive function that continues building the tree until a condition is met
			void buildRecursivePrimitive(const std::vector<Triangle>& triangles, const std::shared_ptr<BVH::Object::Node> node, int depth, const int maxDepth);

			// Another recursive function that loops throught the tree finding and intersecting with
			// any bounding boxes. This function stops when its found a leaf and intersected with the triangles.
			bool hitRecursivePrimitive(RayTrace::Ray& ray, std::shared_ptr<BVH::Object::Node> parentNode);
		};
	}
}
