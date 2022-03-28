#pragma once
// C++
#include <vector>

// Maths
#include "Vector3.h"
#include "Vector2.h"
#include "Matrix4x4.h"

// Accelerator
#include "Bvh.h"

// Graphics
#include "Ray.h"
#include "Pixel.h"

// Scene
#include "Light.h"

class Primitive;
class Atmosphere;

class Camera
{
	public:
		Camera(Vector3 position, Vector3 direction, Vector2 cam_size, float fov);

		void Render(std::vector<Pixel>& buffer, BVH::Builder& bvh, std::vector<std::unique_ptr<Light::Light>>& sceneLights, Atmosphere& atmosphere, int depth, int antiAliasingSamples);

		Vector3& getPosition() { return m_position; }
		const Matrix4x4& getMatrix() const { return m_camToWorld; }

	private:
		Vector3 m_position	= { 0.0f, 0.0f, 0.0f };
		Vector3 m_direction = { 0.0f, 0.0f, 0.0f };
		Matrix4x4 m_camToWorld;
		Vector2 m_size;

		float m_fov			= 0.0f;
		float m_aspectRatio	= 0.0f;
		float m_cameraScale	= 0.0f;

		static constexpr int max_depth = 3;

		Colour castRay(Raycast::Ray& ray, BVH::Builder& bvh, std::vector<std::unique_ptr<Light::Light>>& sceneLights, Atmosphere& atmosphere,int depth);
};
