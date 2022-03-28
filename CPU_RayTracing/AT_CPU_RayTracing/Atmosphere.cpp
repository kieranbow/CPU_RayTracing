#include "Atmosphere.h"
#include "Intersection.h"

Vector3 Atmosphere::computeIncidentLight(Raycast::Ray& ray, float tmin, float tmax)
{
	float t0 = 0.0f, t1 = 0.0f;
	if (!Intersection::inplicitSphere(ray, Vector3(0.0f, 0.0f, 0.0f), m_atmosphereRadius, t0, t1) || t1 < 0.0f) return Vector3();

	if (t0 > tmin && t0 > 0.0f) tmin = t0;
	if (t1 < tmax) tmax = t1;

	const int numSamples = 16;
	const int numSamplesLight = 8;

	float segmentLength = (tmax - tmin) / numSamples;
	float tCurrent = tmin;

	// Mie and rayleigh contribution
	Vector3 sumR, sumM;

	float opticalDepthR = 0.0f, opticalDepthM = 0.0f;
	float mu = Vector3::dot(ray.getDirection(), m_sunDirection);

	float phaseR = 3.0f / (16.0f * Maths::special::pi) * (1.0f + mu * mu);
	float g = 0.76f;
	float phaseM = 3.0f / (8.0f * Maths::special::pi) * ((1.0f - g * g) * (1.0f + mu * mu)) / ((2.0f + g * g) * std::powf(1.0f + g * g - 2.0f * g * mu, 1.5f));

	for (int i = 0; i < numSamples; ++i)
	{
		Vector3 samplePosition = ray.getOrigin() + (tCurrent + segmentLength * 0.5f) * ray.getDirection();
		float height = Vector3::length(samplePosition) - m_earthRadius;

		float hr = std::exp(-height / m_hr) * segmentLength;
		float hm = std::exp(-height / m_hm) * segmentLength;

		opticalDepthR += hr;
		opticalDepthM += hm;

		float t0Light = 0.0f, t1Light = 0.0f;

		Raycast::Ray raySky;
		raySky.setOrigin(samplePosition);
		raySky.setDirection(m_sunDirection);

		Intersection::inplicitSphere(raySky, Vector3(0.0f, 0.0f, 0.0f), m_atmosphereRadius, t0Light, t1Light);
		float segmentLengthLight = t1Light / numSamplesLight;
		float tCurrentLight = 0.0f;
		float opticalDepthLightR = 0.0f, opticalDepthLightM = 0.0f;
		int j = 0;
		for (j = 0; j < numSamplesLight; ++j)
		{
			Vector3 samplePositionLight = samplePosition + (tCurrentLight + segmentLengthLight * 0.5f) * m_sunDirection;
			float heightLight = Vector3::length(samplePositionLight) - m_earthRadius;
			if (heightLight < 0.0f) break;
			opticalDepthLightR += std::exp(-heightLight / m_hr) * segmentLengthLight;
			opticalDepthLightM += std::exp(-heightLight / m_hm) * segmentLengthLight;
			tCurrentLight += segmentLengthLight;
		}
		if (j == numSamplesLight)
		{
			Vector3 tau = m_betaR * (opticalDepthR + opticalDepthLightR) + m_betaM * 1.1f * (opticalDepthM + opticalDepthLightM);
			Vector3 attenuation = { std::exp(-tau.getX()), std::exp(-tau.getY()), std::exp(-tau.getZ()) };
			sumR += attenuation * hr;
			sumM += attenuation * hm;
		}
		tCurrent += segmentLength;
	}
	return (sumR * m_betaR * phaseR + sumM * m_betaM * phaseM) * 20.0f;
}
