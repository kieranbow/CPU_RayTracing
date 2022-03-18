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
	// https://raytracing.github.io/books/RayTracingInOneWeekend.html#positionablecamera
	public:
		Camera(Vector3 positionWS, Vector3 directionWS, Vector2 cam_size, float _fov);

		// void Update();
		void Render(std::vector<Primitive> primitives, std::vector<Pixel>& buffer, BVH::Builder bvh, Light::DirectionLight light);

		void setPositionWS(Vector3 positionWS);
		void setDirectionWS(Vector3 directionWS);

		Vector3& getPosition() { return m_position; }
		const Matrix4x4& getMatrix() const { return cam_to_world; }

	private:
		Vector3 m_position	= { 0.0f, 0.0f, 0.0f };
		Vector3 m_forward	= { 0.0f, 0.0f, -1.0f };
		Vector3 m_up		= { 0.0f, 1.0f, 0.0f };
		Vector3 m_right		= { 0.0f, 0.0f, 0.0f };
		Vector3 m_direction	= { 0.0f, 0.0f, 0.0f };

		Matrix4x4 cam_to_world;

		Vector2 size;

		float fov			= 0.0f;
		float aspect_ratio	= 0.0f;
		float scale			= 0.0f;
};
