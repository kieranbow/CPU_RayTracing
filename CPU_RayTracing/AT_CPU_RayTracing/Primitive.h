#pragma once
#include <vector>

#include "MeshLoader.h"
#include "BoundingBox.h"

class Ray;

class Primitive
{
	public:
		// Creates a default cube primitive at world position [0.0, 0.0, 0.0]
		Primitive();
		Primitive(std::string file_path, Vector3 positionWS);
		~Primitive();

		// Checks a ray primitive's bounding box before checking if that ray
		// hits the primitive's triangles
		bool intersected(Ray &ray);
		// Debug function to see where the bounding box is.
		bool intersectedBoundingBoxDebug(Ray& ray);

		bool generateBoundingBox();

		void setPosition(Vector3 position);
		void setRotation(Vector3 rotation);
		void setScale(Vector3 scale);

		const Vector3& getPosition() const { return ws_position; }
		const Vector3& getRotation() const { return rotation; }
		const Vector3& getScale() const { return scale; }
		const std::vector<Vertex>& getVertices() const { return vertex_buffer; }
		const std::vector<Indices>& getIndices() const { return index_buffer; }
		const BoundingBox::AABB& getBoundingBox() const { return boundingBox; }

	private:
		// Mesh data
		std::vector<Vertex> vertex_buffer;
		std::vector<Indices> index_buffer;

		BoundingBox::AABB boundingBox;

		bool MollerTrumboreIntersection(Ray& ray, Vector3 vert0, Vector3 vert1, Vector3 vert2);

		// Transformation
		Vector3 ws_position = { 0.0f, 0.0f, 0.0f }; // World origin
		Vector3 rotation = { 0.0f, 0.0f, 0.0f };
		Vector3 scale = { 1.0f, 1.0f, 1.0f };
};
