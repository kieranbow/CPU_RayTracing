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
		std::shared_ptr<std::vector<Primitive>> primitive;
		BoundingBox::AABB m_boundingBox;
		bool m_leaf;
		//size_t m_idx;
		//size_t m_objs;

		int size = 0;
	};

	// Handles all the primitives within the scene
	class Accelerator
	{
		public:
			void buildBVH(const std::vector<Primitive>& v_prims);
			void buildTree(std::shared_ptr<Node> root);

			bool hit();
			bool hitRecursive();

			std::vector<Primitive> m_shape;
			std::shared_ptr<BVH::Node> sp_node;

			enum axis { x, y, z };

			int getGreatestAxis(Vector3 vec);
	};
}
