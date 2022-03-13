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
	if (primitive.size() <= m_numOfPrims) 
	{ 
		node->m_leaf = true;
		node->primitive = primitive;

		Logger::PrintDebug("Here be leaf");
	}
	else
	{
		// Generate bounding box around primitives
		BoundingBox::AABB node_bounds;
		node_bounds.setBoundsMinX(Maths::special::k_infinity);
		node_bounds.setBoundsMinY(Maths::special::k_infinity);
		node_bounds.setBoundsMinZ(Maths::special::k_infinity);

		node_bounds.setBoundsMaxX(-Maths::special::k_infinity);
		node_bounds.setBoundsMaxY(-Maths::special::k_infinity);
		node_bounds.setBoundsMaxZ(-Maths::special::k_infinity);

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

		Logger::PrintDebug("Here be node");

		// Create Left node and Right node
		node->sp_leftNode = std::make_shared<Node>();
		node->sp_rightNode = std::make_shared<Node>();

		Logger::PrintDebug("Here be left node");
		Logger::PrintDebug("Here be right node");

		std::vector<Primitive> left_list;
		std::vector<Primitive> right_list;

		// Split the primitives based on their position and the split position
		for (auto& prim : primitive)
		{
			if (prim.getBoundingBox().getCentroid().getValue().at(axis) < node->m_boundingBox.getCentroid().getValue().at(axis))
			{
				//node->left_list.push_back(prim);
				left_list.push_back(prim);
			}
			else
			{
				//node->right_list.push_back(prim);
				right_list.push_back(prim);
			}
		}

		buildTree(left_list, node->sp_leftNode);
		buildTree(right_list, node->sp_rightNode);

		//buildTree(node->left_list, node->sp_leftNode);	// Continue building tree until a condition is met
		//buildTree(node->right_list, node->sp_rightNode);// Continue building tree until a condition is met

	}
}

bool BVH::Accelerator::hit(RayTrace::Ray& ray)
{
	float tn = -Maths::special::k_infinity;
	float tf = Maths::special::k_infinity;

	// Check if ray has hit the root bounding box
	//if (sp_root->m_boundingBox.intersected(ray, tn, tf))
	//{	
		// if (hitRecursive(ray, sp_root)) return true;
	//}

	if (sp_root->m_boundingBox.minMaxIntersected(ray))
	{
		// ray.data.colour = Colour(1.0f, 0.0f, 0.0f);
		
		if (sp_root->sp_leftNode->sp_leftNode != nullptr)
		{
			// hit node bounding box
			std::cout << "recusrive";
		}
		else if (sp_root->sp_leftNode->m_leaf)
		{
			for (auto& prim : sp_root->sp_leftNode->primitive)
			{
				if (prim.intersected(ray))
				{
					return true;
				}
			}
		}

		if (sp_root->sp_rightNode->sp_rightNode != nullptr)
		{
			// hit node bounding box
			std::cout << "recusrive";
		}
		else if (sp_root->sp_rightNode->m_leaf)
		{
			for (auto& prim : sp_root->sp_rightNode->primitive)
			{
				if (prim.intersected(ray))
				{
					return true;
				}
			}
		}
		return false;
		//if (sp_root->sp_rightNode->m_leaf)
		//{
		//	for (auto& prim : sp_root->sp_rightNode->primitive)
		//	{
		//		if (prim.intersected(ray))
		//		{
		//			return true;
		//		}
		//	}
		//}

	}
	return false;


	
	//if (sp_root->m_boundingBox.intersected(ray, tn, tf))
	//{
	//	ray.data.colour = Colour(1.0f, 0.0f, 0.0f);
	//	return true;
	//}
	//if (sp_root->sp_leftNode == nullptr) return false;
	//if (sp_root->sp_leftNode->m_boundingBox.intersected(ray, tn, tf))
	//{
	//	ray.data.colour = Colour(0.0f, 1.0f, 0.0f);
	//	return true;
	//}
	//if (sp_root->sp_rightNode == nullptr) return false;
	//if (sp_root->sp_rightNode->m_boundingBox.intersected(ray, tn, tf))
	//{
	//	ray.data.colour = Colour(0.0f, 0.0f, 1.0f);
	//	return true;
	//}
	//return false;

	//if (sp_root->m_boundingBox.intersected(ray, tn, tf))
	//{
	//	ray.data.colour = Colour(1.0f, 1.0f, 1.0f);
	//	return true;
	//	//return hitRecursive(ray, sp_root);
	//}
	//return false;
}

bool BVH::Accelerator::hitRecursive(RayTrace::Ray& ray, std::shared_ptr<Node> parentNode)
{
	float tn = -Maths::special::k_infinity;
	float tf = Maths::special::k_infinity;

	if (parentNode->m_leaf)
	{
		for (auto& prim : parentNode->primitive)
		{
			// std::cout << prim.name << ", ";

			if (prim.intersected(ray))
			{
				if (prim.name == "cube")
				{
					std::cout << "hello";
				}
				//return true;
			}
		}
	}
	else
	{
		if (parentNode->sp_leftNode == nullptr) return false;
		if (parentNode->sp_leftNode->m_boundingBox.slabIntersected(ray, tn, tf))
		{
			hitRecursive(ray, parentNode->sp_leftNode);
		}

		if (parentNode->sp_rightNode == nullptr) return false;
		if (parentNode->sp_rightNode->m_boundingBox.slabIntersected(ray, tn, tf))
		{
			hitRecursive(ray, parentNode->sp_rightNode);
		}
	}
	return true;




	//if (node->m_boundingBox.intersected(ray, tn, tf))
	//{
	//	if (node->sp_leftNode != nullptr && node->sp_leftNode->m_boundingBox.intersected(ray, tn, tf))
	//	{
	//		if (hitRecursive(ray, node->sp_leftNode))
	//		{
	//			return true;
	//		}
	//	}
	//	if (node->sp_rightNode != nullptr && node->sp_rightNode->m_boundingBox.intersected(ray, tn, tf))
	//	{
	//		if (hitRecursive(ray, node->sp_rightNode)) 
	//		{ 
	//			return true;
	//		}
	//	}
	//	if (node->m_leaf)
	//	{
	//		for (auto& prim : node->primitive)
	//		{
	//			if (prim.intersected(ray))
	//			{
	//				std::cout << "\r" << prim.name;
	//				ray.data.colour = Colour(1.0f, 0.0f, 0.0f);
	//				return true;
	//			}
	//		}
	//	}
	//}

	//// Return false is nothing was hit
	//return false;

	//if (node->m_boundingBox.intersected(ray, tn, tf))
	//{
	//	if (node->m_leaf)
	//	{
	//		for (auto& prim : node->primitive)
	//		{
	//			if (prim.intersected(ray))
	//			{
	//				ray.data.colour = Colour(1.0f, 0.0f, 0.0f);
	//				// return true;
	//			}
	//		}
	//	}
	//	else
	//	{
	//		return hitRecursive(ray, node->sp_leftNode);
	//		return hitRecursive(ray, node->sp_rightNode);
	//	}
	//}
	//return false;
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


//for (auto& prim : node->primitive/*node->left_list*/)
//{
//	if (prim.intersected(ray))
//	{
//		ray.data.colour = Colour(1.0f, 0.0f, 0.0f);
//	}
//}

//for (auto& prim : node->right_list)
//{
//	if (prim.intersected(ray))
//	{
//		ray.data.colour = Colour(0.0f, 1.0f, 0.0f);
//	}
//}

//// If node is a leaf, return early since leafs don't have primitives
//if (node->m_leaf) return false;

//// If the node bb is intersected, check if primitives are intersected as well
//else if (node->m_boundingBox.intersected(ray, tn, tf))
//{
//	for (auto& prim : node->left_list)
//	{
//		if (prim.intersected(ray))
//		{
//			ray.data.colour = Colour(1.0f, 0.0f, 0.0f);
//		}
//	}

//	for (auto& prim : node->right_list)
//	{
//		if (prim.intersected(ray))
//		{
//			ray.data.colour = Colour(0.0f, 1.0f, 0.0f);
//		}
//	}
//	return true;
//}
//// else, loop through again and 
//else
//{
//	hitRecursive(ray, node->sp_leftNode);
//	hitRecursive(ray, node->sp_rightNode);
//}