#pragma once
#include <vector>

#include "Vector3.h"
#include "Primitive.h"
#include "BoundingBox.h"

class Ray;

namespace BVH
{
	// A node that makes up the tree of a BVH
	class Node
	{
		public:
			std::shared_ptr<Node> sp_leftNode;
			std::shared_ptr<Node> sp_rightNode;
			BoundingBox::AABB m_boundingBox;
			bool m_leaf = false;
	};

	// Handles all the primitives within the scene
	class Accelerator
	{
		public:
			void buildBVH(const std::vector<Primitive>& v_prims);
			void buildTree(std::vector<Primitive> primitive);

			bool hit();
			bool hitRecursive();

			std::vector<Primitive> m_shape;
			// std::shared_ptr<BVH::Node> sp_root;

			static constexpr size_t m_numOfPrims = 1;

			enum axis { x, y, z };

			int getGreatestAxis(Vector3 vec);
	};
}
