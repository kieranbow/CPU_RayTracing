#include "BvhScene.h"
#include "Intersection.h"
#include "Logger.h"

void BVH::Scene::Accelerator::buildBVHScene(const std::vector<Primitive>& primitive)
{
	// Checks if the vector of primitives is empty.
	if (primitive.empty())
	{
		Logger::PrintWarning("No primitives to build the BVH from");
		return;
	}

	// Make the root node of the bvh
	sp_root = std::make_shared<Node>();

	// Pass the primitives and root node to recusive function.
	buildRecursiveScene(primitive, sp_root);
}

void BVH::Scene::Accelerator::buildRecursiveScene(const std::vector<Primitive>& primitive, std::shared_ptr<BVH::Scene::Node> node)
{
	// Make a leaf node if the number of primitives is less than an arbitrary number
	if (primitive.size() <= m_numOfPrims)
	{
		node->m_leaf = true;
		node->m_primitive = primitive;
	}
	else
	{
		// Generate a bounding box around all the primitives
		BoundingBox::AABB node_bounds;
		node_bounds.setBoundsMinX(Maths::special::infinity);
		node_bounds.setBoundsMinY(Maths::special::infinity);
		node_bounds.setBoundsMinZ(Maths::special::infinity);

		node_bounds.setBoundsMaxX(-Maths::special::infinity);
		node_bounds.setBoundsMaxY(-Maths::special::infinity);
		node_bounds.setBoundsMaxZ(-Maths::special::infinity);

		for (auto& prim : primitive)
		{
			BoundingBox::AABB box = prim.getBoundingBox();
			BoundingBox::AABB::combineBounds(node_bounds, box);
		}

		node->m_boundingBox = node_bounds;

		// Get node's min and max bounding box points
		Vector3 min = node->m_boundingBox.getBounds().min;
		Vector3 max = node->m_boundingBox.getBounds().max;

		// Find the mid-point using longest axis for the split index
		Vector3 midpoint = Vector3::findMidPoint(max, min);
		int axis = Vector3::getGreatestAxis(midpoint);

		// Create Left node and Right node
		node->sp_leftNode = std::make_shared<Node>();
		node->sp_rightNode = std::make_shared<Node>();

		// Create two list of primitives and split them based on their position and the splits position
		std::vector<Primitive> left_list;
		std::vector<Primitive> right_list;

		for (auto& prim : primitive)
		{
			if (prim.getBoundingBox().getCentroid().getValue().at(axis) < node->m_boundingBox.getCentroid().getValue().at(axis))
			{
				left_list.push_back(prim);
			}
			else
			{
				right_list.push_back(prim);
			}
		}

		// Continue making nodes and splitting primitives until a condition is met 
		buildRecursiveScene(left_list, node->sp_leftNode);
		buildRecursiveScene(right_list, node->sp_rightNode);

		// Clear both list since they won't be used again.
		left_list.clear();
		right_list.clear();
	}
}

bool BVH::Scene::Accelerator::hit(RayTrace::Ray& ray)
{
	// If a ray hits the root node's bounding box, begin the recusion and step through
	// the bvh tree until a primitive is hit
	if (Intersection::minMaxBounds(ray, sp_root->m_boundingBox))
	{
		if (hitRecursive(ray, sp_root))
		{
			return true;
		}
	}
	return false;
}

bool BVH::Scene::Accelerator::hitRecursive(RayTrace::Ray& ray, std::shared_ptr<BVH::Scene::Node> parentNode)
{
	// If the node is a leaf, loop through all its primitives and test if the ray has hit
	// both the bounding box and triangles.
	if (parentNode->m_leaf)
	{
		for (auto& prim : parentNode->m_primitive)
		{
			float tn = -Maths::special::infinity;
			float tf = Maths::special::infinity;

			if (Intersection::slab(ray, prim.getBoundingBox(), tn, tf))
			{
				return true;
			}

			//if (prim.triangleIntersected(ray))
			//{
			//	return true;
			//}
		}
	}

	// If either sp_leftNode or sp_rightNode are NULL. This means that the node is a leaf
	// and any intersection checks can be skipped.
	// If either sp_leftNode or sp_rightNode are not NULL, check that both it's bounding box
	// and hitRecusive are true.

	if (parentNode->sp_leftNode != nullptr)
	{
		if (Intersection::minMaxBounds(ray, parentNode->sp_leftNode->m_boundingBox) && hitRecursive(ray, parentNode->sp_leftNode))
		{
			return true;
		}
	}
	if (parentNode->sp_rightNode != nullptr)
	{
		if (Intersection::minMaxBounds(ray, parentNode->sp_rightNode->m_boundingBox) && hitRecursive(ray, parentNode->sp_rightNode))
		{
			return true;
		}
	}

	// If none of the checks return true, return false since nothing was hit
	return false;
}
