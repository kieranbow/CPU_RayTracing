#pragma once
#include <vector>
#include <string>

#include "MeshLoader.h"
#include "BoundingBox.h"
#include "Ray.h"
#include "Bvh.h"
#include "Material.h"
#include "Shader.h"

class Colour;

class Primitive
{
	public:
		// Creates a default cube primitive at world position [0.0, 0.0, 0.0]
		Primitive();
		Primitive(std::string file_path, Vector3 positionWS);
		~Primitive();

		// Checks a ray primitive's bounding box before checking if that ray hits the primitive's triangles
		bool triangleIntersected(Raycast::Ray&ray);
		
		// Debug function to see where the bounding box is.
		bool intersectedBoundingBoxDebug(Raycast::Ray& ray);

		bool generateBoundingBox();

		void setPosition(Vector3 position);
		//void setRotation(Vector3 rotation);
		void setScale(Vector3 scale);

		void setMaterial(const Material::Data& material) { m_material = material; }
		void setShader(std::shared_ptr<Shaders::Shader> shader) { sp_shader = shader; }

		const Vector3& getPosition() const { return m_position; }
		const Vector3& getRotation() const { return m_rotation; }
		const Vector3& getScale() const { return m_scale; }
		const std::vector<Vertex>& getVertices() const { return m_vertexBuffer; }
		const std::vector<Indices>& getIndices() const { return m_indexBuffer; }
		const BoundingBox::AABB& getBoundingBox() const { return m_boundingBox; }
		const Material::Data& getMaterial() const { return m_material; }

	private:
		// Mesh data
		std::vector<Vertex> m_vertexBuffer;
		std::vector<Indices> m_indexBuffer;

		// Bounding Box that surrounds the mesh
		BoundingBox::AABB m_boundingBox;

		// Primitives material
		Material::Data m_material;

		std::shared_ptr<Shaders::Shader> sp_shader;

		// Transformation
		Vector3 m_position	= { 0.0f, 0.0f, 0.0f };
		Vector3 m_rotation	= { 0.0f, 0.0f, 0.0f };
		Vector3 m_scale		= { 1.0f, 1.0f, 1.0f };
};
