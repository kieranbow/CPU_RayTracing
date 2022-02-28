#pragma once
#include <vector>
#include <array>

#include "Vector3.h"
#include "Vertex.h"

struct Plane
{
	Vector3 normal = { 0.0f, 0.0f, 0.0f };
	float near = k_infinity;
	float far = -k_infinity;
};

class BoundingBox
{
public:
	BoundingBox() = default;
	
	// Loops through obj vertex buffer and generate a bounding box
	void generateBoundingBox(std::vector<Vertex>& vertex_buffer);

	const std::array<Vector3, 8>& getBounds() const { return bounds; }
	const Vector3& getMinBounds() const { return min_bounds; }
	const Vector3& getMaxBounds() const { return max_bounds; }

private:
	Vector3 min_bounds	= { 0.0f, 0.0f, 0.0f };
	Vector3 max_bounds	= { 0.0f, 0.0f, 0.0f };

	std::array<Vector3, 8> bounds;
	
	std::array<Plane, 3> planes;



	Vector3 x_plane = { 1.0f, 0.0f, 0.0f };
	Vector3 y_plane = { 0.0f, 1.0f, 0.0f };
	Vector3 z_plane = { 0.0f, 0.0f, 1.0f };

	Vector3 point0		= { 0.0f, 0.0f, 0.0f };
	Vector3 point1		= { 0.0f, 0.0f, 0.0f };
	Vector3 point2		= { 0.0f, 0.0f, 0.0f };
	Vector3 point3		= { 0.0f, 0.0f, 0.0f };
	Vector3 point4		= { 0.0f, 0.0f, 0.0f };
	Vector3 point5		= { 0.0f, 0.0f, 0.0f };
	Vector3 point6		= { 0.0f, 0.0f, 0.0f };
	Vector3 point7		= { 0.0f, 0.0f, 0.0f };
};
