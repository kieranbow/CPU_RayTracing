#include "Bvh.h"

BVH::BVHAccel::BVHAccel(std::vector<Primitive>& prim, int _maxPrimInNode)
{
	maxPrimInNode = std::min(255, _maxPrimInNode);
	primitives = prim;

	if (primitives.size() == 0) return;

	// Init an array of primitive info
	std::vector<BVH::PrimitiveInfo> primitive_info(primitives.size());

	// Loop through all primitives and assign info about id and bounding box to
	// primtive_info
	for (int i = 0; i < primitives.size(); i++)
	{
		primitive_info.at(i) = { i, primitives.at(i).getBoundingBox() };
	}

	int total_nodes = 0;
	std::vector<std::shared_ptr<Primitive>> orderedPrims;
	//BVH::Node* root;

	//root = recusiveBuild

	//primitives.swap(orderedPrims);

}

std::shared_ptr<BVH::Node> BVH::BVHAccel::recursiveBuild(std::vector<BVH::PrimitiveInfo>& prim_info, int start, int end, int* total_nodes, std::vector<std::shared_ptr<Primitive>>& ordered_prims)
{
	std::shared_ptr<BVH::Node> node = std::make_unique<BVH::Node>();
	*total_nodes++;

	// Compute the bounds of all primitives within the BVH node
	BoundingBox::AABB bounds;
	for (int i = start; i < end; ++i)
	{
		bounds.setBounds(BoundingBox::AABB::unionBounds(bounds, prim_info.at(i).boundingbox));
	}

	int n_primitives = end - start;
	
	// Create leaf node
	if (n_primitives == 1)
	{
		size_t first_prim_offset = ordered_prims.size();
		for (int i = start; i < end; ++i)
		{
			int prim_num = prim_info.at(i).id;
			//ordered_prims.push_back(primitives.at(prim_num));
		}
		node->initLeaf(first_prim_offset, n_primitives, bounds);
		return node;
	}
	else
	{
		return nullptr;
	}
}
