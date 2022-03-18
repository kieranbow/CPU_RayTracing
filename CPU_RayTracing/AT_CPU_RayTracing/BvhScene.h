#pragma once
#include "Ray.h"
#include "BoundingBox.h"
#include "Primitive.h"

namespace BVH
{
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

				// Checks if a ray has hit any of the bvh bounding boxes
				bool hit(RayTrace::Ray& ray);

			private:
				static constexpr size_t m_numOfPrims = 2;
				std::shared_ptr<BVH::Scene::Node> sp_root;

				// A recursive function that continues building the tree until the number of primitives < 2
				void buildRecursiveScene(const std::vector<Primitive>& primitive, std::shared_ptr<BVH::Scene::Node> node);

				// Another recursive function that loops throught the tree finding and intersecting with
				// any bounding boxes and primitives
				bool hitRecursive(RayTrace::Ray& ray, std::shared_ptr<BVH::Scene::Node> parentNode);
		};
	}
}
