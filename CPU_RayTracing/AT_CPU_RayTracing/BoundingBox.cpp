#include "BoundingBox.h"

void BoundingBox::generateBoundingBox(std::vector<Vertex>& vertex_buffer)
{
	//min_bounds = vertex_buffer.at(0).position;
	//max_bounds = vertex_buffer.at(0).position;

	//for (auto& vert : vertex_buffer)
	//{
	//	// https://www.sebastianhaas.at/calculating-bounding-box/

	//	//if (vert.position < min_bounds) { min_bounds = vert.position; }
	//	//if (vert.position > max_bounds) { max_bounds = vert.position; }

	//	// x axis
	//	if (vert.position.getX() < min_bounds.getX()) { min_bounds.setX(vert.position.getX()); }
	//	if (vert.position.getX() > max_bounds.getX()) { max_bounds.setX(vert.position.getX()); }
	//	
	//	// y axis
	//	if (vert.position.getY() < min_bounds.getY()) { min_bounds.setY(vert.position.getY()); }
	//	if (vert.position.getY() > max_bounds.getY()) { max_bounds.setY(vert.position.getY()); }

	//	// z axis
	//	if (vert.position.getZ() < min_bounds.getZ()) { min_bounds.setZ(vert.position.getZ()); }
	//	if (vert.position.getZ() > max_bounds.getZ()) { max_bounds.setZ(vert.position.getZ()); }

	//}
	//std::cout << "Min bounds " << min_bounds << std::endl;
	//std::cout << "Max bounds " << max_bounds << std::endl;

	// If the mesh was a unit cube each point would be:
	// point0 [1, 1, 1] // Max bounds
	// point1 [-1, 1, 1]
	// point2 [-1, -1, 1]
	// point3 [1, -1, 1]
	// point4 [-1, 1, -1]
	// point5 [1, 1, -1]
	// point6 [1, -1, -1]
	// point7 [-1, -1, -1] // Min bounds

	//bounds.at(0) = max_bounds;
	//bounds.at(1) = Vector3(min_bounds.getX(), max_bounds.getY(), max_bounds.getZ());
	//bounds.at(2) = Vector3(min_bounds.getX(), min_bounds.getY(), max_bounds.getZ());
	//bounds.at(3) = Vector3(max_bounds.getX(), min_bounds.getY(), max_bounds.getZ());
	//bounds.at(4) = Vector3(min_bounds.getX(), max_bounds.getY(), min_bounds.getZ());
	//bounds.at(5) = Vector3(max_bounds.getX(), max_bounds.getY(), min_bounds.getZ());
	//bounds.at(6) = Vector3(max_bounds.getX(), min_bounds.getY(), min_bounds.getZ());
	//bounds.at(7) = min_bounds;


	//std::cout << "point0 " << bounds.at(0) << std::endl;
	//std::cout << "point1 " << bounds.at(1) << std::endl;
	//std::cout << "point2 " << bounds.at(2) << std::endl;
	//std::cout << "point3 " << bounds.at(3) << std::endl;
	//std::cout << "point4 " << bounds.at(4) << std::endl;
	//std::cout << "point5 " << bounds.at(5) << std::endl;
	//std::cout << "point6 " << bounds.at(6) << std::endl;
	//std::cout << "point7 " << bounds.at(7) << std::endl;

	//point0 = max_bounds;
	//point1 = Vector3(min_bounds.getX(), max_bounds.getY(), max_bounds.getZ());
	//point2 = Vector3(min_bounds.getX(), min_bounds.getY(), max_bounds.getZ());
	//point3 = Vector3(max_bounds.getX(), min_bounds.getY(), max_bounds.getZ());

	//point4 = Vector3(min_bounds.getX(), max_bounds.getY(), min_bounds.getZ());
	//point5 = Vector3(max_bounds.getX(), max_bounds.getY(), min_bounds.getZ());
	//point6 = Vector3(max_bounds.getX(), min_bounds.getY(), min_bounds.getZ());
	//point7 = min_bounds;

	// Generates a bounding box using the slab method as mention by Kay and Kajiya in 1986
	planes.at(0).normal = { 1.0f, 0.0f, 0.0f };
	planes.at(1).normal = { 0.0f, 1.0f, 0.0f };
	planes.at(2).normal = { 0.0f, 0.0f, 1.0f };

	for (auto& vert : vertex_buffer)
	{
		for (auto& plane : planes)
		{
			float d = Vector3::dot(plane.normal, vert.position);
			if (d < plane.near) plane.near = d;
			if (d > plane.far) plane.far = d;
		}
	}

	for (auto& plane : planes)
	{
		std::cout << plane.near << " " << plane.far << std::endl;
	}
}
