#include "Bvh.h"
#include "Logger.h"

void BVH::Accelerator::buildBVH(const std::vector<Primitive>& v_prims)
{
	// Copy scenes prmitives to change order of primitives for BVH
	if (v_prims.empty())
	{
		Logger::PrintWarning("No primitives to build the BVH from");
		return;
	}
	
	m_shape.reserve(v_prims.size());
	std::copy(v_prims.begin(), v_prims.end(), std::back_inserter(m_shape));

	std::vector<std::shared_ptr<BVH::Node>> sp_nodes;
	int left_idx = 0;
	int right_idx = m_shape.size();
	int n_nodes = 1;

	// Generate root bounding box around entire scene
	
	BoundingBox::AABB worldBounds = m_shape.at(0).getBoundingBox();

	Vector3 world_min = { -k_infinity, -k_infinity, -k_infinity };
	Vector3 world_max = { k_infinity, k_infinity, k_infinity };
	for(auto& prim: m_shape)
	{
		BoundingBox::AABB box = prim.getBoundingBox();

		BoundingBox::AABB::combineBounds(worldBounds, box);

		//if (world_min.getX() < box.min.getX()) worldBounds.setBoundsMinX(box.min.getX());
		//if (world_min.getY() < box.min.getY()) worldBounds.setBoundsMinY(box.min.getY());
		//if (world_min.getZ() < box.min.getZ()) worldBounds.setBoundsMinZ(box.min.getZ());

		//if (world_max.getX() > box.max.getX()) worldBounds.setBoundsMaxX(box.max.getX());
		//if (world_max.getY() > box.max.getY()) worldBounds.setBoundsMaxY(box.max.getY());
		//if (world_max.getZ() > box.max.getZ()) worldBounds.setBoundsMaxZ(box.max.getZ());

	}
	
	
	//sp_root->m_boundingBox = ;


	// Split primitives using mid-point to create child nodes from root
	// Find midpoint of largest axis
	// Sort each primitive and split between left and right nodes

	// Continue spliting until only one primitives is in each node

}
