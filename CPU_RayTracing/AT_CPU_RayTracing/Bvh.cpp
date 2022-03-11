#include "Bvh.h"
#include "Logger.h"

void BVH::Accelerator::buildBVH(const std::vector<Primitive>& v_prims)
{
	// Checks if the vector of primitives is empty.
	if (v_prims.empty())
	{
		Logger::PrintWarning("No primitives to build the BVH from");
		return;
	}
	
	// Copy scenes prmitives into BVH
	m_shape.reserve(v_prims.size());
	std::copy(v_prims.begin(), v_prims.end(), std::back_inserter(m_shape));

	buildTree(m_shape);
}

void BVH::Accelerator::buildTree(std::vector<Primitive> primitive)
{
	// Make a leaf node if the number of primitives is less than an arbitrary number
	if (primitive.size() < m_numOfPrims) 
	{ 
		std::shared_ptr<Node> sp_leaf = std::make_shared<Node>();
		sp_leaf->m_leaf = true;
	}
	else
	{
		// Generate bounding box around primitives
		BoundingBox::AABB node_bounds = primitive.at(0).getBoundingBox();

		for (auto& prim : primitive)
		{
			BoundingBox::AABB box = prim.getBoundingBox();
			BoundingBox::AABB::combineBounds(node_bounds, box);
		}

		// Get parent nodes min and max bounding box
		Vector3 min = node_bounds.getBounds().min; //sp_root->m_boundingBox.getBounds().min;
		Vector3 max = node_bounds.getBounds().max; //sp_root->m_boundingBox.getBounds().max;

		// Find the mid-point using longest axis for the split index
		float mid_x = (max.getX() + min.getX()) / 2.0f;
		float mid_y = (max.getY() + min.getY()) / 2.0f;
		float mid_z = (max.getZ() + min.getZ()) / 2.0f;
		Vector3 midPoint = Vector3(mid_x, mid_y, mid_z);

		int axis = getGreatestAxis(midPoint);

		// Create list of left and right primitives for splitting
		std::vector<Primitive> left_list;
		std::vector<Primitive> right_list;

		// Split the primitives based on their position and the split position
		for (auto& prim : m_shape)
		{
			if (prim.getBoundingBox().getCentroid().getValue().at(axis) < node_bounds.getCentroid().getValue().at(axis))
			{
				left_list.push_back(prim);
			}
			else
			{
				right_list.push_back(prim);
			}
		}

		// Create Left node
		std::shared_ptr<Node> sp_leftNode = std::make_shared<Node>();
		buildTree(left_list); 		// Continue building tree until a condition is met

		// Create Left node
		std::shared_ptr<Node> sp_rightNode = std::make_shared<Node>();
		buildTree(right_list); 		// Continue building tree until a condition is met
	}
}

int BVH::Accelerator::getGreatestAxis(Vector3 vec)
{
	//if (vec.getX() > vec.getY()) return axis::x;
	//else
	//{
	//	return axis::z;
	//}
	//if (vec.getY() > vec.getZ()) return axis::y;
	//return axis::z;

	//if (vec.getX() > vec.getY() && vec.getX() > vec.getZ()) return axis::x;
	//if (vec.getY() > vec.getX() && vec.getY() > vec.getZ()) return axis::y;
	//if (vec.getZ() > vec.getX() && vec.getZ() > vec.getY()) return axis::z;

	if (vec.getX() > vec.getY() && vec.getX() > vec.getZ()) return axis::x;
	else if (vec.getY() > vec.getZ()) return axis::y;
	else return axis::z;
}
