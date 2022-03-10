#include "Bvh.h"
#include "Logger.h"

void BVH::Accelerator::buildBVH(const std::vector<Primitive>& v_prims)
{
	if (v_prims.empty())
	{
		Logger::PrintWarning("No primitives to build the BVH from");
		return;
	}
	
	// Copy scenes prmitives to change order of primitives for BVH
	m_shape.reserve(v_prims.size());
	std::copy(v_prims.begin(), v_prims.end(), std::back_inserter(m_shape));

	// Generate root bounding box around entire scene
	BoundingBox::AABB worldBounds = m_shape.at(0).getBoundingBox();

	for(auto& prim: m_shape)
	{
		BoundingBox::AABB box = prim.getBoundingBox();
		BoundingBox::AABB::combineBounds(worldBounds, box);
	}
	
	// Make root node
	sp_node = std::make_shared<BVH::Node>();
	sp_node->m_boundingBox = worldBounds;

	buildTree(sp_node);

	// Split primitives using mid-point to create child nodes from root
	// Find midpoint of largest axis
	// Sort each primitive and split between left and right nodes

	// Continue spliting until only one primitives is in each node

}

void BVH::Accelerator::buildTree(std::shared_ptr<Node> root)
{
	// Make leaf node if the number of prims is less than an arbitrary number
	size_t n = 2;
	if (m_shape.size() < n) { root->makeLeaf(); }
	else
	{
		// Find longest axis | sort prims along axis

		// Get parent nodes bounding box min and max
		Vector3 min = root->m_boundingBox.getBounds().min;
		Vector3 max = root->m_boundingBox.getBounds().max;

		Vector3 diff = max - min;

		int axis = getGreatestAxis(diff);

		// Find the split index mid-point using longest axis and divide left and right side

		// Create AABB bounds around the split primitives

		// Create Left and right node
		//sp_node->sp_leftNode = std::make_shared<Node>();

		root->sp_rightNode = std::make_shared<Node>();
	}
}

int BVH::Accelerator::getGreatestAxis(Vector3 vec)
{
	if (vec.getX() > vec.getY()) return axis::x;
	else
	{
		return axis::z;
	}
	if (vec.getY() > vec.getZ()) return axis::y;
	return axis::z;
}

void BVH::Node::makeLeaf()
{
	m_leaf = true;
}
