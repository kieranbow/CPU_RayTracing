#include "Bvh.h"
#include "Logger.h"
#include "Colour.h"

void BVH::Accelerator::buildBVH(const std::vector<Primitive>& primitive)
{
	// Checks if the vector of primitives is empty.
	if (primitive.empty())
	{
		Logger::PrintWarning("No primitives to build the BVH from");
		return;
	}

	// Make the root node of the bvh
	sp_root = std::make_shared<Node>();

	// Pass the primitives and root node to recusive function
	buildTree(primitive, sp_root);
}

void BVH::Accelerator::buildTree(const std::vector<Primitive>& primitive, std::shared_ptr<Node> node)
{
	// Make a leaf node if the number of primitives is less than an arbitrary number
	if (primitive.size() < m_numOfPrims) 
	{ 
		//std::shared_ptr<Node> sp_leaf = std::make_shared<Node>();
		//sp_leaf->m_leaf = true;
		
		node->m_leaf = true;
		std::cout << "Here be leaf\n";
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

		node->m_boundingBox = node_bounds;

		// Get node's min and max bounding box
		Vector3 min = node->m_boundingBox.getBounds().min;
		Vector3 max = node->m_boundingBox.getBounds().max;

		// Find the mid-point using longest axis for the split index
		Vector3 midpoint = Vector3::findMidPoint(max, min);

		int axis = getGreatestAxis(midpoint);

		// Create Left node and Right node
		node->sp_leftNode = std::make_shared<Node>();
		node->sp_rightNode = std::make_shared<Node>();

		// Split the primitives based on their position and the split position
		for (auto& prim : primitive)
		{
			if (prim.getBoundingBox().getCentroid().getValue().at(axis) < node->m_boundingBox.getCentroid().getValue().at(axis))
			{
				//sp_leftNode->left_list.push_back(prim);
				node->left_list.push_back(prim);
			}
			else
			{
				//sp_rightNode->right_list.push_back(prim);
				node->right_list.push_back(prim);
			}
		}
		//buildTree(sp_leftNode->left_list); 	// Continue building tree until a condition is met
		//buildTree(sp_rightNode->right_list); 	// Continue building tree until a condition is met

		buildTree(node->left_list, node->sp_leftNode);
		buildTree(node->right_list, node->sp_rightNode);

	}
}

bool BVH::Accelerator::hit(RayTrace::Ray& ray)
{
	float tn = -Maths::special::k_infinity;
	float tf = Maths::special::k_infinity;

	// Check if ray has hit the root bounding box
	if (sp_root->m_boundingBox.intersected(ray, tn, tf))
	{
		if (hitRecursive(ray, sp_root)) return true;
	}
}

bool BVH::Accelerator::hitRecursive(RayTrace::Ray& ray, std::shared_ptr<Node> node)
{
	float tn = -Maths::special::k_infinity;
	float tf = Maths::special::k_infinity;

	// If node is a leaf, return early since leafs don't have primitives
	if (node->m_leaf) return false;

	// If the node bb is intersected, check if primitives are intersected as well
	if (node->m_boundingBox.intersected(ray, tn, tf))
	{
		for (auto& prim : node->left_list)
		{
			Colour hitcolor;

			if (prim.intersected(ray, hitcolor)) return true;
		}

		for (auto& prim : node->right_list)
		{
			Colour hitcolor;

			if (prim.intersected(ray, hitcolor)) return true;
		}

		return false;
	}
	// else, loop through again and 
	else
	{
		hitRecursive(ray, node->sp_leftNode);
	}

	//if (node->sp_leftNode->m_boundingBox.intersected(ray, tn, tf))
	//{
	//	if (node->sp_leftNode->m_leaf)
	//	{
	//		for (auto& prim : node->left_list)
	//		{
	//			Colour hitcolor;

	//			if (prim.intersected(ray, hitcolor)) return true;
	//		}
	//		return false;
	//	}
	//	else
	//	{
	//		hitRecursive(ray, node->sp_leftNode);
	//	}

	//	if (node->sp_rightNode->m_leaf)
	//	{
	//		for (auto& prim : node->right_list)
	//		{
	//			Colour hitcolor;

	//			if (prim.intersected(ray, hitcolor)) return true;
	//		}
	//		return false;
	//	}
	//	else
	//	{
	//		hitRecursive(ray, node->sp_rightNode);
	//	}
	//}
	return false;
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
