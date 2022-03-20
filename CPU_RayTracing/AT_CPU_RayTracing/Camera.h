#pragma once
#include <vector>

#include "Vector3.h"
#include "Vector2.h"
#include "Matrix4x4.h"
#include "Ray.h"
#include "Pixel.h"
#include "Bvh.h"
#include "Light.h"

class Primitive;

class Camera
{
	public:
		Camera(Vector3 position, Vector3 direction, Vector2 cam_size, float fov);

		void Render(std::vector<Primitive> primitives, std::vector<Pixel>& buffer, BVH::Builder& bvh, std::vector<std::unique_ptr<Light::Light>>& sceneLights, int depth);

		void setPositionWS(Vector3 positionWS);
		void setDirectionWS(Vector3 directionWS);

		Vector3& getPosition() { return m_position; }
		const Matrix4x4& getMatrix() const { return m_camToWorld; }

	private:
		Vector3 m_position	= { 0.0f, 0.0f, 0.0f };
		Vector3 m_direction = { 0.0f, 0.0f, 0.0f };
		
		//Vector3 m_forward	= { 0.0f, 0.0f, -1.0f };
		//Vector3 m_up		= { 0.0f, 1.0f, 0.0f };
		//Vector3 m_right	= { 0.0f, 0.0f, 0.0f };

		Matrix4x4 m_camToWorld;
		Vector2 m_size;

		float m_fov			= 0.0f;
		float m_aspectRatio	= 0.0f;
		float m_scale		= 0.0f;

		static constexpr int max_depth = 3;

		Colour castRay(RayTrace::Ray& ray, BVH::Builder& bvh, std::vector<std::unique_ptr<Light::Light>>& sceneLights, int depth);
};
