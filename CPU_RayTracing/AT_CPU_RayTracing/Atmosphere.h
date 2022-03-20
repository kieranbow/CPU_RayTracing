#pragma once
#include "Vector3.h"
#include "Ray.h"

class Atmosphere
{
public:
	Atmosphere(Vector3 sd = { 0.0f, 1.0f, 0.0f }, float er = 6360e3, float ar = 6420e3, float hr = 7994, float hm = 1200)
		: m_sunDirection(sd), m_earthRadius(er), m_atmosphereRadius(ar), m_hr(hr), m_hm(hm) {}

	Vector3 computeIncidentLight(RayTrace::Ray& ray, float tmin, float tmax);

	Vector3 m_sunDirection;
	float m_earthRadius;
	float m_atmosphereRadius;
	float m_hr; // Rielay Atmosphere thichness
	float m_hm; // Mie Atmosphere thickness

	const Vector3 m_betaR = { 3.8e-6f, 13.5e-6f, 33.1e-6f };
	const Vector3 m_betaM = { 21e-6f, 21e-6f, 21e-6f };
};