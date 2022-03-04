#pragma once
#include <vector>

#include "Vector3.h"
#include "Primitive.h"
#include "BoundingBox.h"

// https://pbr-book.org/3ed-2018/Primitives_and_Intersection_Acceleration/Bounding_Volume_Hierarchies#fragment-InitializemonoprimitiveInfoarrayforprimitives-0
class Bvh
{
public:
	Bvh(std::vector<Primitive>& prim, int _maxPrimInNode)
	{
		maxPrimInNode = std::min(255, _maxPrimInNode);
		primitives = prim;

		if (primitives.size() == 0) return;

		std::vector<PrimitiveInfo> primitive_info(primitives.size());

		for (int i = 0; i < primitives.size(); i++)
		{
			primitive_info.at(i).id = i;
			primitive_info.at(i).bounds = primitives.at(i).getBoundingBox();

			Vector3 min = primitive_info.at(i).bounds.getBounds().min_bounds;
			Vector3 max = primitive_info.at(i).bounds.getBounds().max_bounds;
			primitive_info.at(i).centroid = Vector3(0.5f, 0.5f, 0.5f) * min + Vector3(0.5f, 0.5f, 0.5f) * max;
		}
	}

private:
	int maxPrimInNode = 0;
	std::vector<Primitive> primitives;

	struct PrimitiveInfo
	{
		int id = 0;
		BoundingBox bounds;
		Vector3 centroid;
	};
};
