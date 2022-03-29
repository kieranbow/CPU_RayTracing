#pragma once
#include "Vector3.h"
#include "Colour.h"
#include "Ray.h"

class Atmosphere
{
	public:
		Atmosphere(Vector3 sd = { 0.0f, 1.0f, 0.0f }, Vector3 position = Vector3(0.0f, 0.0f, 0.0f), float er = 6360e3, float ar = 6420e3, float hr = 7994, float hm = 1200)
			: m_sunDirection(sd), m_position(position), m_planetRadius(er), m_atmosphereRadius(ar), m_hr(hr), m_hm(hm) {}

		void setSunDirection(Vector3 direction) { m_sunDirection = direction; }
		void setPosition(Vector3 position) { m_position = position; }
		void setPosition(float x, float y, float z) { m_position = Vector3(x, y, z); }
		void setPlanetRadius(float radius) { m_planetRadius = radius; }
		void setAtmosphereRadius(float radius) { m_atmosphereRadius = radius; }
		void setRayleighThickness(float thickness) { m_hr = thickness; }
		void setMieThickness(float thickness) { m_hm = thickness; }

		const Vector3& getPosition() const { return m_position; }
		const float& getPlanetRadius() const { return m_planetRadius; }
		const float& getAtmosphereRadius() const { return m_atmosphereRadius; }

		Vector3 computeIncidentLight(Raycast::Ray& ray, float tmin, float tmax);

	private:
		Vector3 m_sunDirection;
		Vector3 m_position;
		float m_planetRadius; // Radius of the planet
		float m_atmosphereRadius; // Radius of the atmosphere. Note, this need to be bigger than planet radius
		float m_hr; // Rayleigh Atmosphere thichness
		float m_hm; // Mie Atmosphere thickness

		const Vector3 m_betaR = { 3.8e-6f, 13.5e-6f, 33.1e-6f }; // Rayleigh scattering coefficients of the sky at sea level
		const Vector3 m_betaM = { 21e-6f, 21e-6f, 21e-6f }; //Mie scattering coefficients of the sky at sea level
		static constexpr int m_numSamples = 16;
		static constexpr int m_numSampleLight = 8;
		static constexpr float m_g = 0.76f; // Controls the anisotropy of mie
};