
#include <mutex>
#include <atomic>
#include <future>

#include "Camera.h"
#include "Primitive.h"
#include "Intersection.h"
#include "ShaderMaths.h"
#include "ShaderFunc.h"
#include "Random.h"
#include "Logger.h"
#include "Random.h"
#include "Atmosphere.h"

Camera::Camera(Vector3 position, Vector3 direction, Vector2 cam_size, float fov, Options option)
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

	m_option = option;
}

void Camera::singleThreadRender(std::vector<Pixel>& buffer, BVH::Builder& bvh, std::vector<std::unique_ptr<Light::Light>>& sceneLights, Atmosphere& atmosphere, int depth, int antiAliasingSamples)
{
	// https://www.iquilezles.org/www/articles/cputiles/cputiles.htm
	const int tilesize = 16;
	const int numXtile = static_cast<int>(m_size.getX()) / tilesize;
	const int numYtile = static_cast<int>(m_size.getY()) / tilesize;
	const int numTiles = numXtile * numYtile;
	const int maxDepth = 5;

	for (int y = 0; y < m_size.getY(); y++)
	{
		for (int x = 0; x < m_size.getX(); x++)
		{
			const int iter = static_cast<int>(m_size.getX() * (y)+(x));

			// Create a pixel
			Pixel pixel;

			// Convert pixel from raster space to camera space
			float Px = (2.0f * (x + 0.5f) / m_size.getX() - 1.0f) * m_aspectRatio * m_cameraScale;
			float Py = (1.0f - 2.0f * (y + 0.5f) / m_size.getY()) * m_cameraScale;

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
			buffer.at(iter).colour += castRay(primary_ray, bvh, sceneLights, atmosphere, depth);
		}
	}

	//// Loop through each tile
	//for (int tile = 0; tile < numTiles; tile++)
	//{
	//	const float offset_x = static_cast<float>(tilesize * (tile % numXtile));
	//	const float offset_y = static_cast<float>(tilesize * (tile / numXtile));

	//	// Loop through the tiles width and height in pixels
	//	for (int y = 0; y < tilesize; y++)
	//	{
	//		for (int x = 0; x < tilesize; x++)
	//		{
	//			const float x_iter = offset_x + static_cast<float>(x);
	//			const float y_iter = offset_y + static_cast<float>(y);
	//			const int iter = static_cast<int>(m_size.getX() * (y_iter)+(x_iter));

	//			// Loop through all the Anti-aliasing samples.
	//			// This is the main render loop where the rays are cast into the scene
	//			// returing a colour if it has or has not hit anything
	//			float tile_x = x_iter + 0.5f;
	//			float tile_y = y_iter + 0.5f;

	//			// Create a pixel
	//			Pixel pixel;

	//			// Convert pixel from raster space to camera space
	//			float Px = (2.0f * (tile_x + 0.5f) / m_size.getX() - 1.0f) * m_aspectRatio * m_cameraScale;
	//			float Py = (1.0f - 2.0f * (tile_y + 0.5f) / m_size.getY()) * m_cameraScale;

	//			pixel.position.setX(Px);
	//			pixel.position.setY(Py);

	//			// Convert pixel camera space to world space
	//			Vector3 pixelPosWS;
	//			m_camToWorld.multDirByMatrix4x4(Vector3(pixel.position.getX(), pixel.position.getY(), m_direction.getZ()), pixelPosWS);
	//			Vector3::normalize(pixelPosWS);

	//			// Create ray that's origin is the camera and it's direction is towards the pixel
	//			Raycast::Ray primary_ray;
	//			primary_ray.setOrigin(m_position);
	//			primary_ray.setDirection(Vector3::normalize(pixelPosWS/* - primary_ray.getOrigin()*/));

	//			// Cast the ray and return a colour to the buffer
	//			buffer.at(iter).colour += castRay(primary_ray, bvh, sceneLights, atmosphere, depth);


	//			//for (int aaX = 0; aaX < antiAliasingSamples; ++aaX)
	//			//{
	//			//	for (int aaY = 0; aaY < antiAliasingSamples; aaY++)
	//			//	{

	//			//	}
	//			//	
	//			//}
	//			//// Once render loop is complete. Take the current pixel and apply anti-aliasing
	//			//float scale = 1.0f / antiAliasingSamples;

	//			//buffer.at(iter).colour /= Colour(scale, scale, scale);
	//		}
	//	}
	//}
}

void Camera::multiThreadRender(std::vector<Pixel>& buffer, BVH::Builder& bvh, std::vector<std::unique_ptr<Light::Light>>& sceneLights, Atmosphere& atmosphere, int depth, int antiAliasingSamples)
{
	// https://medium.com/@phostershop/solving-multithreaded-raytracing-issues-with-c-11-7f018ecd76fa

	const int tilesize = 64;
	const int numXtile = static_cast<int>(m_size.getX()) / tilesize;
	const int numYtile = static_cast<int>(m_size.getY()) / tilesize;
	const int numTiles = numXtile * numYtile;

	size_t max = static_cast<size_t>(m_size.getX() * m_size.getY());
	size_t max_cores = std::thread::hardware_concurrency();
	volatile std::atomic<size_t> count = 0;
	std::vector<std::future<void>> future;

	float width = m_size.getX();
	float height = m_size.getY();

	for (size_t core = 0; core < max_cores; core++)
	{
		future.emplace_back(
			std::async(
				[=,&count, &width, &height, &buffer, &bvh, &sceneLights, &atmosphere, &depth, &antiAliasingSamples]()
				{
					for (size_t tile = 0; tile < numTiles; tile++) /*while(true)*/
					{
						const int tilesize = 32;
						const int numXtile = static_cast<int>(width) / tilesize;
						const int numYtile = static_cast<int>(height) / tilesize;
						const int numTiles = numXtile * numYtile;

						size_t idx = count++;
						if (idx >= numTiles) break;

						const float offset_x = static_cast<float>(tilesize * (idx % numXtile));
						const float offset_y = static_cast<float>(tilesize * (idx / numXtile));

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
								float Px = (2.0f * (tile_x + 0.5f) / m_size.getX() - 1.0f) * m_aspectRatio * m_cameraScale;
								float Py = (1.0f - 2.0f * (tile_y + 0.5f) / m_size.getY()) * m_cameraScale;

								pixel.position.setX(Px);
								pixel.position.setY(Py);

								// Convert pixel camera space to world space
								Vector3 pixelPosWS;
								m_camToWorld.multDirByMatrix4x4(Vector3(pixel.position.getX(), pixel.position.getY(), m_direction.getZ()), pixelPosWS);
								Vector3::normalize(pixelPosWS);

								// Create the primiary ray that's origin is the camera position and it's direction is towards the pixel
								Raycast::Ray primary_ray;
								primary_ray.setOrigin(m_position);
								primary_ray.setDirection(Vector3::normalize(pixelPosWS/* - primary_ray.getOrigin()*/));

								// Cast the ray and return a colour to the buffer
								buffer[iter].colour += castRay(primary_ray, bvh, sceneLights, atmosphere, depth);
							}
						}
					}
				}));
	}
}

Colour Camera::castRay(Raycast::Ray& ray, BVH::Builder& bvh, std::vector<std::unique_ptr<Light::Light>>& sceneLights, Atmosphere& atmosphere, int depth)
{
	using namespace Shaders::Math;

	Colour hitColour;
	if (depth > max_depth) return Colour(0.235294f, 0.67451f, 0.843137f);

	float tnear = Maths::special::infinity;

	if (bvh.hit(ray, tnear))
	{
		// Rays hit point
		Vector3 hitpoint = ray.getHitData().hitPoint;
		
		// Material properties from the hit point
		Colour albedo		= ray.getHitData().material.albedo;
		float roughness		= ray.getHitData().material.roughness;
		float metallic		= ray.getHitData().material.metallic;
		float specIntensity = ray.getHitData().material.specular_intensity;
		Vector3 normal		= ray.getHitData().material.normal;
		Vector3 viewDir		= normalize(ray.getDirection());

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
				Shaders::Functions::fresnel(ray.getDirection(), normal, 1.5f, kr);
				Vector3 reflectionDir = reflect(ray.getDirection(), normal);
				Vector3 reflectionOrigin = (dot(reflectionDir, normal) < 0.0f) ? hitpoint + normal * m_option.shadowBias : hitpoint - normal * m_option.shadowBias;

				Raycast::Ray reflectionRay;
				reflectionRay.setOrigin(reflectionOrigin);
				reflectionRay.setDirection(reflectionDir);

				hitColour = albedo * castRay(reflectionRay, bvh, sceneLights, atmosphere, depth + 1) * kr;
			}
			break;

			case Material::Types::Refractive:
			{
				Vector3 reflectionDir = normalize(reflect(ray.getDirection(), normal));
				Vector3 reflectionOrigin = (dot(reflectionDir, normal) < 0.0f) ? hitpoint + normal * m_option.shadowBias : hitpoint - normal * m_option.shadowBias;

				Raycast::Ray reflectionRay;
				reflectionRay.setOrigin(reflectionOrigin);
				reflectionRay.setDirection(reflectionDir);

				Vector3 refractiveDir = normalize(refract(ray.getDirection(), normal, 1.33f));
				Vector3 refractiveOrigin = (dot(refractiveDir, normal) < 0.0f) ? hitpoint - normal * m_option.shadowBias : hitpoint + normal * m_option.shadowBias;

				Raycast::Ray refractiveRay;
				refractiveRay.setOrigin(refractiveOrigin);
				refractiveRay.setDirection(refractiveDir);

				float kr = 0.0f;
				Shaders::Functions::fresnel(ray.getDirection(), normal, 1.33f, kr);

				Colour refractColour = castRay(refractiveRay, bvh, sceneLights, atmosphere, depth + 1);
				Colour reflectColour = castRay(reflectionRay, bvh, sceneLights, atmosphere, depth + 1);
				hitColour = /*reflectColour * kr + */refractColour /** (1.0f - kr)*/;
			}
			break;

			case Material::Types::Phong:
			{
				for (auto& light : sceneLights)
				{
					Vector3 lightDirection;
					Colour lightColour;

					// Get lighting information
					light->illuminate(hitpoint, lightDirection, lightColour, /*ray.getHitData().tnear*/tnear);

					const float NdotL = saturate(dot(normal, lightDirection));

					// Shoot shadow rays into scene
					Raycast::Ray shadowRay;
					shadowRay.setOrigin(hitpoint + normal * m_option.shadowBias);
					shadowRay.setDirection(lightDirection);
					shadowRay.m_tNear = ray.getHitData().tnear;
					bool shadow = !bvh.hit(shadowRay, tnear);

					Colour diffuse = Shaders::Functions::lambertCosineLaw(NdotL, lightColour, albedo) * shadow;
					Vector3 R = reflect(lightDirection, normal);
					float specular = light->m_intensity * power(max(0.0f, dot(R, viewDir)), 10.0f) * shadow;
					hitColour += diffuse * 0.8f + specular * 0.2f;
				}
				return hitColour;
			}
			break;

			case Material::Types::Dielectic:
			{
				Colour f0 = Colour(0.04f, 0.04f, 0.04f);
				f0 = lerp(f0, albedo, metallic);

				Colour lo = Colour();

				// Loop through all the lights in the scene and add them linearly 
				for (auto& light : sceneLights)
				{
					Vector3 lightDirection;
					Colour lightColour;

					// Get lighting information
					light->illuminate(hitpoint, lightDirection, lightColour, tnear /*ray.getHitData().tnear*/);

					Vector3 halfVector = normalize(-viewDir + lightDirection);

					float NdotL = saturate(dot(normal, lightDirection));
					float NdotH = saturate(dot(normal, halfVector));
					float NdotV = saturate(dot(normal, -viewDir));
					float HdotV = saturate(dot(halfVector, -viewDir));

					float d = Shaders::BRDF::trowbridge_reitz_ggx(NdotH, roughness);
					float g = Shaders::BRDF::geometry_smith(NdotV, NdotL, roughness);
					Colour f = Shaders::BRDF::fresnel_schlick(HdotV, f0, 1.0f);

					Colour ks = f;
					Colour kd = Colour(1.0f, 1.0f, 1.0f) - ks;
					kd *= 1.0f - metallic;

					Colour specular = Shaders::BRDF::cookTorranceBRDF(f, d, g, NdotV, NdotL) * specIntensity;

					// Shoot shadow rays into scene
					Raycast::Ray shadowRay;
					shadowRay.setOrigin(hitpoint + normal * m_option.shadowBias);
					shadowRay.setDirection(lightDirection);
					shadowRay.m_tNear = tnear; /*ray.getHitData().tnear*/;
					bool shadow = !bvh.hit(shadowRay, tnear);

					Colour diffuse = Shaders::Functions::lambertCosineLaw(NdotL, lightColour, albedo);

					lo += ((kd * diffuse + specular) * NdotL) * shadow;
				}
				Colour ambient = Colour(0.03f, 0.03f, 0.03f) * albedo;
				hitColour = ambient + lo;
				return hitColour;
			}
			break;
		}
	}
	else
	{
		// Create ray to intersect with the atmosphere
		Raycast::Ray skyray;
		skyray.setOrigin(Vector3(0.0f, atmosphere.getPlanetRadius() + 1.0f, 0.0f));
		skyray.setDirection(ray.getDirection());

		// Here, scratchaPixel uses a for loop with a range of 4 to add brightness to the sky.
		// However, this causes a loss of performance. So instead, the result from computeIncidentLight() is multiplied by an intensity value
		// which is set by default to 4.
		float t0, t1, tmax = Maths::special::infinity;
		if (Intersection::raySphere(skyray, atmosphere.getPosition(), atmosphere.getPlanetRadius(), t0, t1) && t1 > 0.0f) tmax = std::max(0.0f, t0);
		hitColour += atmosphere.computeIncidentLight(skyray, 0.0f, tmax) * atmosphere.getBrightness();

		// Background colour
		//hitColour = Colour(0.235294f, 0.67451f, 0.843137f);
	}
	return hitColour;
}
