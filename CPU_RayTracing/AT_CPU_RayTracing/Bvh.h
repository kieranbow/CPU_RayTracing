#pragma once
#include <vector>

#include "Vector3.h"
#include "Primitive.h"
#include "BoundingBox.h"
#include "Ray.h"

namespace BVH
{
	// Finds the biggest axis from a Vector3
	int getGreatestAxis(Vector3 vec);

	namespace Scene
	{
		// A node that makes up the tree of a BVH
		struct Node
		{
			// Pointers to left node and right node
			std::shared_ptr<BVH::Scene::Node> sp_leftNode;
			std::shared_ptr<BVH::Scene::Node> sp_rightNode;

			BoundingBox::AABB m_boundingBox;
			bool m_leaf = false;

			// Node will only contain primitives when it is a leaf.
			std::vector<Primitive> m_primitive;
		};

		// Handles all the bvh buidling and collision testing
		class Accelerator
		{
			public:
				// Builds a bvh from a scene of primitives. This tree is top down
				void buildBVHScene(const std::vector<Primitive>& primitive);

				// A recursive function that continues building the tree until the number of primitives < 2
				void buildRecursiveScene(const std::vector<Primitive>& primitive, std::shared_ptr<BVH::Scene::Node> node);

				// Checks if a ray has hit any of the bvh bounding boxes
				bool hit(RayTrace::Ray& ray);

				// Another recursive function that loops throught the tree finding and intersecting with
				// any bounding boxes and primitives
				bool hitRecursive(RayTrace::Ray& ray, std::shared_ptr<BVH::Scene::Node> parentNode);

			private:
				static constexpr size_t m_numOfPrims = 2;
				std::shared_ptr<BVH::Scene::Node> sp_root;
		};
	}

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
				void buildBVHPrimitive(Primitive& prim);

				// A recursive function that continues building the tree until a condition is met
				void buildRecursivePrimitive(const std::vector<Triangle>& triangles, std::shared_ptr<BVH::Object::Node> node, int depth, int maxDepth);

				// Checks if a ray has hit any of the bvh bounding boxes
				bool hitPrimitive(RayTrace::Ray& ray);

				// Another recursive function that loops throught the tree finding and intersecting with
				// any bounding boxes. This function stops when its found a leaf and intersected with the triangles.
				bool hitRecursivePrimitive(RayTrace::Ray& ray, std::shared_ptr<BVH::Object::Node> parentNode);

			private:
				static constexpr size_t m_numOfTris = 4;
				static constexpr int m_max_depth = 6;
				std::shared_ptr<BVH::Object::Node> sp_root;
				std::vector<Triangle> m_triangles;
		};
	}
}
