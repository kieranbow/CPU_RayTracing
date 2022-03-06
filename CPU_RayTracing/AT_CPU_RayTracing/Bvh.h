#pragma once
#include <vector>

#include "Vector3.h"
#include "Primitive.h"
#include "BoundingBox.h"

namespace BVH
{
	struct PrimitiveInfo
	{
		PrimitiveInfo() {}
		PrimitiveInfo(int prim_id, BoundingBox::AABB bounds) :
			id(prim_id),
			boundingbox(bounds),
			centroid(Vector3(0.5f, 0.5f, 0.5f)* bounds.getBounds().min_extent + Vector3(0.5f, 0.5f, 0.5f) * bounds.getBounds().max_extent) {}

		int id = 0;
		BoundingBox::AABB boundingbox;
		Vector3 centroid;
	};

	struct Node
	{
		Node() = default;
		void initLeaf(size_t first, int n, BoundingBox::AABB& bounds)
		{
			first_prim_offset = first;
			n_primitives = n;
			boundingBox = bounds;
			children.at(0) = children.at(1) = nullptr;
			// ++leafNodes;
			// ++totalLeafNodes;
			// totalPrimitives += n;
		}
		void initInterior(int axis, Node *c0, Node *c1)
		{
			children.at(0) = c0;
			children.at(1) = c1;
			// boundingBox = Union(c0->getBounds(), c1->getBounds()
			split_axis = axis;
			n_primitives = 0;
			// ++interiorNode;
		}

		BoundingBox::AABB boundingBox;
		std::array<BVH::Node*, 2> children;
		size_t first_prim_offset = 0;
		int split_axis = 0, n_primitives = 0;
	};

	// https://pbr-book.org/3ed-2018/Primitives_and_Intersection_Acceleration/Bounding_Volume_Hierarchies#fragment-InitializemonoprimitiveInfoarrayforprimitives-0
	class BVHAccel
	{
	public:
		BVHAccel(std::vector<Primitive>& prim, int _maxPrimInNode);
		std::shared_ptr<BVH::Node> recursiveBuild(std::vector<BVH::PrimitiveInfo>& prim_info, int start, int end, int *total_nodes, std::vector<std::shared_ptr<Primitive>>& ordered_prims);

	private:
		int maxPrimInNode = 1;
		std::vector<Primitive> primitives;
	};
}
