#pragma once
#include <vector>

#include "Vector3.h"
#include "Primitive.h"
#include "BoundingBox.h"
#include "Ray.h"

namespace BVH
{
	// A node that makes up the tree of a BVH
	class Node
	{
		public:
			// Pointers to left node and right node
			std::shared_ptr<Node> sp_leftNode;
			std::shared_ptr<Node> sp_rightNode;

			BoundingBox::AABB m_boundingBox;
			bool m_leaf = false;

			std::vector<Primitive> left_list;
			std::vector<Primitive> right_list;
	};

	// Handles all the primitives within the scene
	class Accelerator
	{
		public:
			void buildBVH(const std::vector<Primitive>& primitive);
			void buildTree(const std::vector<Primitive>& primitive, std::shared_ptr<Node> node);

			bool hit(RayTrace::Ray& ray);
			bool hitRecursive(RayTrace::Ray& ray, std::shared_ptr<Node> node);
		
		private:
			static constexpr size_t m_numOfPrims = 2;
			std::shared_ptr<Node> sp_root;
			enum axis { x, y, z };
			int getGreatestAxis(Vector3 vec);
	};
}
