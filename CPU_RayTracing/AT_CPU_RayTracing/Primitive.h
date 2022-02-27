#pragma once
#include <vector>

#include "MeshLoader.h"

class Ray;

class Primitive
{
	public:
		// Creates a default cube primitive at world position [0.0, 0.0, 0.0]
		Primitive();
		Primitive(std::string file_path, Vector3 positionWS);
		~Primitive();


		bool intersected(Ray &ray);

		void setPosition(Vector3 position);
		void setRotation(Vector3 rotation);
		void setScale(Vector3 scale);

		const Vector3& getPosition() const;
		const Vector3& getRotation() const;
		const Vector3& getScale() const;

		const std::vector<Vertex>& getVertices() const
		{
			return vertex_buffer;
		}

	private:
		// Mesh data
		std::vector<Vertex> vertex_buffer;
		std::vector<Indices> index_buffer;

		bool MollerTrumboreIntersection(Ray& ray, Vector3 vert0, Vector3 vert1, Vector3 vert2);

		Vector3 ws_position = { 0.0f, 0.0f, 0.0f };
		/*Vector3 rotation = { 0.0f, 0.0f, 0.0f };*/
		/*Vector3 scale = { 0.0f, 0.0f, 0.0f }*/
};
