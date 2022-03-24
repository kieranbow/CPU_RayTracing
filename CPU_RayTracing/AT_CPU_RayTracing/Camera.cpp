#include <thread>

#include "Camera.h"
#include "Primitive.h"
#include "Intersection.h"
#include "ShaderMaths.h"
#include "ShaderFunc.h"
#include "Random.h"
#include "Logger.h"
#include "Random.h"

Camera::Camera(Vector3 position, Vector3 direction, Vector2 cam_size, float fov)
{
	// Set world space position and direction
	m_position = m_camToWorld.multVecByMatrix4x4(position);
	m_direction = direction;

	// Set the dimension of the camera
	m_size = cam_size;

	// Sets the field of view
	m_fov = fov;

	// Set the aspect ratio based on camera size
	m_aspectRatio = m_size.getX() / m_size.getY();
	m_cameraScale = std::tan(Maths::deg2rad(m_fov) * 0.5f);

	m_camToWorld.multVecMatrix(Vector3(0.0f, 0.0f, 0.0f), position);
}

void Camera::Render(std::vector<Pixel>& buffer, BVH::Builder& bvh, std::vector<std::unique_ptr<Light::Light>>& sceneLights, int depth, int antiAliasingSamples)
{
	// https://www.iquilezles.org/www/articles/cputiles/cputiles.htm
	const int tilesize = 32;
	const int numXtile = static_cast<int>(m_size.getX()) / tilesize;
	const int numYtile = static_cast<int>(m_size.getY()) / tilesize;
	const int numTiles = numXtile * numYtile;
	const int maxDepth = 5;

	// Loop through each tile
	for (int tile = 0; tile < numTiles; tile++)
	{
		const float offset_x = static_cast<float>(tilesize * (tile % numXtile));
		const float offset_y = static_cast<float>(tilesize * (tile / numXtile));

		// Loop through the tiles width and height in pixels
		for (int y = 0; y < tilesize; y++)
		{
			for (int x = 0; x < tilesize; x++)
			{
				const float x_iter = offset_x + static_cast<float>(x);
				const float y_iter = offset_y + static_cast<float>(y);
				const int iter = static_cast<int>(m_size.getX() * (y_iter)+(x_iter));

				// Loop through all the Anti-aliasing samples.
				// This is the main render loop where the rays are cast into the scene
				// returing a colour if it has or has not hit anything
				float tile_x = x_iter + 0.5f;
				float tile_y = y_iter + 0.5f;

				// Create a pixel
				Pixel pixel;

				// Convert pixel from raster space to camera space
				//float Px = (2.0f * (tile_x + (aaX + Maths::Random::randomFloat()) / antiAliasingSamples) / m_size.getX() - 1.0f) * m_aspectRatio * m_scale;	// * tan(fov / 2.0f * Maths::special::pi / 180.0f) * aspect_ratio * scale;
				//float Py = (1.0f - (tile_y + (aaX + Maths::Random::randomFloat()) / antiAliasingSamples) / m_size.getY() * 2.0f) * m_scale;	// * tan(fov / 2.0f * Maths::special::pi / 180.0f));

				float Px = (2.0f * (tile_x + 0.5f) / m_size.getX() - 1.0f) * m_aspectRatio * m_cameraScale;
				float Py = (1.0f - 2.0f * (tile_y + 0.5f) / m_size.getY()) * m_cameraScale;

				pixel.position.setX(Px);
				pixel.position.setY(Py);

				// Convert pixel camera space to world space
				Vector3 pixelPosWS;
				m_camToWorld.multDirByMatrix4x4(Vector3(pixel.position.getX(), pixel.position.getY(), m_direction.getZ()), pixelPosWS);
				Vector3::normalize(pixelPosWS);

				// Create ray that's origin is the camera and it's direction is towards the pixel
				Raycast::Ray primary_ray;
				primary_ray.setOrigin(m_position);
				primary_ray.setDirection(Vector3::normalize(pixelPosWS/* - primary_ray.getOrigin()*/));

				// Cast the ray and return a colour to the buffer
				buffer.at(iter).colour += castRay(primary_ray, bvh, sceneLights, depth);


				//for (int aaX = 0; aaX < antiAliasingSamples; ++aaX)
				//{
				//	for (int aaY = 0; aaY < antiAliasingSamples; aaY++)
				//	{

				//	}
				//	
				//}
				//// Once render loop is complete. Take the current pixel and apply anti-aliasing
				//float scale = 1.0f / antiAliasingSamples;

				//buffer.at(iter).colour /= Colour(scale, scale, scale);
			}
		}
	}
}

Colour Camera::castRay(Raycast::Ray& ray, BVH::Builder& bvh, std::vector<std::unique_ptr<Light::Light>>& sceneLights, int depth)
{
	using namespace Shaders::Math;

	Colour hitColour;
	if (depth > max_depth) return Colour(0.5f, 0.5f, 1.0f);

	if (bvh.hit(ray))
	{
		Vector3 hitpoint	= ray.getOrigin() + ray.getDirection() * ray.getHitData().tnear;
		Vector3 N			= ray.getHitData().material.normal;
		Colour albedo		= ray.getHitData().material.albedo;
		float roughness		= ray.getHitData().material.roughness;
		float metallic		= ray.getHitData().material.metallic;

		// Rendering of multiple materials is based off Whitted Light-Transport Algorithm 
		switch (ray.getHitData().material.type)
		{
			// Render the pixel based off the type of material that the ray hits.
			default:
			{
				// If the hit data doesn't contain a valid type of material, return the colour pink
				hitColour = Colour(1.0f, 0.0f, 1.0f);
				return hitColour;
			}
			break;

			case Material::Types::Reflective:
			{
				float kr = 0.0f;
				Shaders::Functions::fresnel(ray.getDirection(), N, 1.5, kr);
				Vector3 reflectionDir = reflect(ray.getDirection(), N);
				Vector3 reflectionOrigin = (dot(reflectionDir, N) < 0.0f) ? hitpoint + N * 0.1f : hitpoint - N * 0.1f;

				Raycast::Ray reflectionRay;
				reflectionRay.setOrigin(reflectionOrigin);
				reflectionRay.setDirection(reflectionDir);

				hitColour = albedo * castRay(reflectionRay, bvh, sceneLights, depth + 1);// * kr;
			}
			break;

			case Material::Types::Refractive:
			{
				Vector3 reflectionDir = normalize(reflect(ray.getDirection(), N));
				Vector3 reflectionOrigin = (dot(reflectionDir, N) < 0.0f) ? hitpoint + N * 0.1f : hitpoint - N * 0.1f;

				Raycast::Ray reflectionRay;
				reflectionRay.setOrigin(reflectionOrigin);
				reflectionRay.setDirection(reflectionDir);


				Vector3 refractiveDir = normalize(refract(ray.getDirection(), N, 1.52f));
				Vector3 refractiveOrigin = (dot(refractiveDir, N) < 0.0f) ? hitpoint - N * 0.1f : hitpoint + N * 0.1f;
				
				float kr = 0.0f;
				Shaders::Functions::fresnel(ray.getDirection(), N, 1.52f, kr);

				Raycast::Ray refractiveRay;
				refractiveRay.setOrigin(refractiveOrigin);
				refractiveRay.setDirection(refractiveDir);

				Colour refractColour = castRay(refractiveRay, bvh, sceneLights, depth + 1);
				Colour reflectColour = castRay(reflectionRay, bvh, sceneLights, depth + 1);
				hitColour = reflectColour * kr + refractColour * (1.0f - kr);
				//hitColour = refractColour * (1.0f - kr);
			}
			break;

			case Material::Types::Conductive:
				break;

			case Material::Types::Dielectic:
			{
				// Loop through all the lights in the scene and add them linearly 
				for (auto& light : sceneLights)
				{
					Vector3 lightDirection;
					Colour lightColour;

					// Get lighting information
					light->illuminate(hitpoint, lightDirection, lightColour, ray.getHitData().tnear);
					
					Vector3 V = normalize(ray.getDirection());
					//Vector3 halfVector = normalize(-V + lightDirection);

					float NdotL = saturate(dot(N, lightDirection));
					//float NdotH = saturate(dot(N, halfVector));
					//float NdotV = saturate(dot(N, -V));
					//float LdotH = saturate(dot(lightDirection, halfVector));

					//Colour f0 = Colour(0.04f, 0.04f, 0.04f);
					//f0 = lerp(f0, pow(albedo, 2.2f), metallic);

					//float d = Shaders::BRDF::trowbridge_reitz_ggx(NdotH, roughness);
					//float g = Shaders::BRDF::geometry_smith(NdotV, NdotL, roughness) * Shaders::BRDF::geometry_smith(NdotV, NdotL, roughness);
					//Colour f = Shaders::BRDF::fresnel_schlick(NdotL, f0, 1.0f);

					//Colour ks = f;
					//Colour kd = 1.0f - ks;
					//kd *= Colour(1.0f, 1.0f, 1.0f) - metallic;

					//Colour specular = Shaders::BRDF::cookTorranceBRDF(f, d, g, NdotV, NdotL) * light->m_intensity * 0.5f;
					//Colour outgoing_radiance = albedo + specular.getRed() * NdotL;


					// Shoot shadow rays into scene
					Raycast::Ray shadowRay;
					shadowRay.setOrigin(hitpoint + N * 0.1f);
					shadowRay.setDirection(lightDirection);
					shadowRay.m_tNear = ray.getHitData().tnear;

					bool shadow = !bvh.hit(shadowRay);

					Colour diffuse = Shaders::Functions::lambertCosineLaw(NdotL, lightColour, albedo);


					// Colour albedo = ray.getHitData().material.albedo;
					// Colour diffuse = albedo / Maths::special::pi * lightColour * std::max(0.0f, Vector3::dot(lightDirection, N));
					hitColour += albedo * shadow;
				}
				return hitColour;
			}
			break;
		}
	}
	else
	{
		hitColour = Colour(0.235294f, 0.67451f, 0.843137f);
	}
	return hitColour;
}
