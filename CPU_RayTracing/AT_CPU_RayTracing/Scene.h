#pragma once
#include <string>
#include <vector>
#include <memory>

#include "Pixel.h"
#include "Primitive.h"

class Camera;
/*class Light;*/

class Scene
{
	public:
		Scene() = default;
		virtual ~Scene() = default;

		// Constructs everything in the scene like lighting and 
		// primitives
		void initialize();
		
		// Destroy all the data in the scene when the program closes
		void destroy();

		// 
		void update();

		// Renders everything to the camera
		void Render();

		void Output();

	private:
		std::string name = "Default";
		Vector2 image_size = { 0.0f, 0.0f };

		std::vector<std::unique_ptr<Primitive>> p_primitives;
		//std::vector<Camera> cameras;
		/*std::vector<Light> lights;*/	
		std::vector<Pixel> framebuffer;
};
