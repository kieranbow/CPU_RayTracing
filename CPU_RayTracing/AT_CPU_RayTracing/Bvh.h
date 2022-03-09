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
			
			void setNodeAABB();
			void makeLeaf();
			void makeNode();
			

			std::shared_ptr<Node> sp_leftNode;
			std::shared_ptr<Node> sp_rightNode;
			BoundingBox::AABB m_boundingBox;
			bool m_leaf;
			size_t m_idx;
			size_t m_objs;
	};

	// Handles all the primitives within the scene
	class Accelerator
	{
		public:
			void buildBVH(const std::vector<Primitive>& v_prims);
			void buildRecursive(size_t leftIdx, size_t rightIdx, BoundingBox::AABB box, std::shared_ptr<BVH::Node> sp_node, int depth);

			bool hit();
			bool hitRecursive();

			std::vector<Primitive> m_shape;
			std::shared_ptr<BVH::Node> sp_root;
			std::vector<std::shared_ptr<BVH::Node>> sp_nodes;
	};
}
