#include "Bvh.h"
#include "Logger.h"
#include "Colour.h"
#include "Intersection.h"
#include "Primitive.h"

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

		// Logger::PrintDebug("Here be leaf");
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
		int axis = getGreatestAxis(midpoint);

		// Logger::PrintDebug("Here be node");

		// Create Left node and Right node
		node->sp_leftNode = std::make_shared<Node>();
		node->sp_rightNode = std::make_shared<Node>();

		//Logger::PrintDebug("Here be left node");
		//Logger::PrintDebug("Here be right node");

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

			if (Intersection::slab(ray, prim.getBoundingBox(), tn ,tf))
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

int BVH::getGreatestAxis(Vector3 vec)
{
	if (vec.getX() > vec.getY() && vec.getX() > vec.getZ()) return Maths::coord::x;
	else if (vec.getY() > vec.getZ()) return Maths::coord::y;
	else return Maths::coord::z;
}

void BVH::Builder::build(std::vector<Primitive>& primitives)
{
	// First, get every object within the scene and build a bvh out of its vertices and indices
	for (auto& prim : primitives)
	{
		BVH::Object::Accelerator bvh_builder;
		bvh_builder.buildBVHPrimitive(prim.getVertices(), prim.getIndices());
		prim.bvh = bvh_builder;
	}

	// Second, using the objects within the scene again, build a bvh for the scene.
	test.buildBVHScene(primitives);
}

bool BVH::Builder::hit(RayTrace::Ray& ray, std::vector<Primitive>& primitives)
{
	// Check if ray hits any bb in scene
	if (test.hit(ray))
	{
		// Loop through primitives within scene and check if bb
		// hit primitive triangle
		for (auto& prim : primitives)
		{
			if (prim.bvh.hitPrimitive(ray))
			{
				return true;
			}
		}
	}
	return false;
}

void BVH::Object::Accelerator::buildBVHPrimitive(const std::vector<Vertex>& vertex_buffer, const std::vector<Indices>& index_buffer)
{
	if (index_buffer.empty() || vertex_buffer.empty()  /*prim.getIndices().empty()*/)
	{
		Logger::PrintWarning("No indices or vertices in the mesh to build the BVH from");
		return;
	}

	// Loop through the primitives indices and re-create the triangles and push them
	// in the vector of triangles
	for (int i = 0; i < index_buffer.size()/*prim.getIndices().size()*/; i += 3)
	{
		//int vertex_idx_1 = ; //prim.getIndices().at(i);
		//int vertex_idx_2 = index_buffer.at(i + 1); //prim.getIndices().at(i + 1);
		//int vertex_idx_3 = index_buffer.at(i + 2); //prim.getIndices().at(i + 2);

		Triangle triangle;
		triangle.vert0.position = vertex_buffer.at(index_buffer.at(i)).position; //prim.getVertices().at(vertex_idx_1).position;
		triangle.vert0.normal	= vertex_buffer.at(index_buffer.at(i)).normal; //prim.getVertices().at(vertex_idx_1).normal;
		triangle.vert0.texcoord	= vertex_buffer.at(index_buffer.at(i)).texcoord; //prim.getVertices().at(vertex_idx_1).texcoord;

		triangle.vert1.position	= vertex_buffer.at(index_buffer.at(i + 1)).position; //prim.getVertices().at(vertex_idx_2).position;
		triangle.vert1.normal	= vertex_buffer.at(index_buffer.at(i + 1)).normal; //prim.getVertices().at(vertex_idx_2).normal;
		triangle.vert1.texcoord	= vertex_buffer.at(index_buffer.at(i + 1)).texcoord; //prim.getVertices().at(vertex_idx_2).texcoord;

		triangle.vert2.position	= vertex_buffer.at(index_buffer.at(i + 2)).position; //prim.getVertices().at(vertex_idx_3).position;
		triangle.vert2.normal	= vertex_buffer.at(index_buffer.at(i + 2)).normal; //prim.getVertices().at(vertex_idx_3).normal;
		triangle.vert2.texcoord	= vertex_buffer.at(index_buffer.at(i + 2)).texcoord; //prim.getVertices().at(vertex_idx_3).texcoord;
		
		m_triangles.push_back(triangle);
	}

	// Make the root node of the bvh
	sp_root = std::make_shared<Node>();

	// Pass the vector of triangles and root node to recusive function.
	buildRecursivePrimitive(m_triangles, sp_root, 0, m_max_depth);
}

void BVH::Object::Accelerator::buildRecursivePrimitive(const std::vector<Triangle>& triangles, const std::shared_ptr<BVH::Object::Node> node, int depth, const int maxDepth)
{
	// Make a leaf node if the number of triangles is less than an arbitrary number
	if (triangles.size() <= m_numOfTris || depth >= maxDepth)
	{
		node->m_leaf = true;
		node->m_triangles = triangles;
	}
	else
	{
		// Generate a bounding box around all the triangles
		BoundingBox::AABB node_bounds;
		//node_bounds.setBoundsMinX(Maths::special::infinity);
		//node_bounds.setBoundsMinY(Maths::special::infinity);
		//node_bounds.setBoundsMinZ(Maths::special::infinity);

		//node_bounds.setBoundsMaxX(-Maths::special::infinity);
		//node_bounds.setBoundsMaxY(-Maths::special::infinity);
		//node_bounds.setBoundsMaxZ(-Maths::special::infinity);

		BoundingBox::AABB box;
		box.generateBoundingBox(triangles);

		BoundingBox::AABB::combineBounds(node_bounds, box);

		node->m_boundingBox = node_bounds;

		// Get node's min and max bounding box points
		Vector3 min = node->m_boundingBox.getBounds().min;
		Vector3 max = node->m_boundingBox.getBounds().max;

		// Find the mid-point using longest axis for the split index
		Vector3 midpoint = Vector3::findMidPoint(max, min);
		int axis = getGreatestAxis(midpoint);

		// Create Left node and Right node
		node->sp_leftNode = std::make_shared<Node>();
		node->sp_rightNode = std::make_shared<Node>();

		// Create two list of primitives and split them based on their position and the splits position
		std::vector<Triangle> left_list;
		std::vector<Triangle> right_list;

		for (auto& tri : triangles)
		{
			Vector3 vert0 = tri.vert0.position;
			Vector3 vert1 = tri.vert1.position;
			Vector3 vert2 = tri.vert2.position;

			// https://www.quora.com/How-do-I-find-centre-of-a-triangle
			Vector3 tri_centroid;
			tri_centroid.setX((vert0.getX() + vert1.getX() + vert2.getX()) / 3);
			tri_centroid.setY((vert0.getY() + vert1.getY() + vert2.getY()) / 3);
			tri_centroid.setZ((vert0.getZ() + vert1.getZ() + vert2.getZ()) / 3);

			if (tri_centroid.getValue().at(axis) < node->m_boundingBox.getCentroid().getValue().at(axis))
			{
				left_list.push_back(tri);
			}
			else
			{
				right_list.push_back(tri);
			}
		}

		// Continue making nodes and splitting primitives until a condition is met 
		buildRecursivePrimitive(left_list, node->sp_leftNode, depth + 1, m_max_depth);
		buildRecursivePrimitive(right_list, node->sp_rightNode, depth + 1, m_max_depth);

		// Clear both list since they won't be used again.
		left_list.clear();
		right_list.clear();
	}
}

bool BVH::Object::Accelerator::hitPrimitive(RayTrace::Ray& ray)
{
	// If a ray hits the root node's bounding box, begin the recusion and step through
	// the bvh tree until a primitive is hit
	if (Intersection::minMaxBounds(ray, sp_root->m_boundingBox))
	{
		if (hitRecursivePrimitive(ray, sp_root))
		{
			return true;
		}
	}
	return false;
}

bool BVH::Object::Accelerator::hitRecursivePrimitive(RayTrace::Ray& ray, std::shared_ptr<BVH::Object::Node> parentNode)
{
	// If the node is a leaf, loop through all its primitives and test if the ray has hit
	// both the bounding box and triangles.
	if (parentNode->m_leaf)
	{
		for (auto& tri : parentNode->m_triangles)
		{
			if (Intersection::MollerTrumbore(ray, tri))
			{
				Vector3 vert0_normal = tri.vert0.normal;
				Vector3 vert1_normal = tri.vert1.normal;
				Vector3 vert2_normal = tri.vert2.normal;

				ray.data.normal = Vector3::normalize((1.0f - ray.data.uv.getX() - ray.data.uv.getY()) * vert0_normal + ray.data.uv.getX() * vert1_normal + ray.data.uv.getY() * vert2_normal);
				return true;
			}
		}
	}

	// If either sp_leftNode or sp_rightNode are NULL. This means that the node is a leaf
	// and any intersection checks can be skipped.
	// If either sp_leftNode or sp_rightNode are not NULL, check that both it's bounding box
	// and hitRecusive are true.

	if (parentNode->sp_leftNode != nullptr)
	{
		if (Intersection::minMaxBounds(ray, parentNode->sp_leftNode->m_boundingBox) && hitRecursivePrimitive(ray, parentNode->sp_leftNode))
		{
			return true;
		}
	}
	if (parentNode->sp_rightNode != nullptr)
	{
		if (Intersection::minMaxBounds(ray, parentNode->sp_rightNode->m_boundingBox) && hitRecursivePrimitive(ray, parentNode->sp_rightNode))
		{
			return true;
		}
	}

	// If none of the checks return true, return false since nothing was hit
	return false;
}
