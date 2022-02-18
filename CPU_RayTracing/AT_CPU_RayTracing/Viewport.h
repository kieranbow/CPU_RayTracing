#pragma once
#include <utility>
#include <vector>

class Viewport
{
	public:
		Viewport() : size(640, 480) {}
		Viewport(int _width, int _height) : size(_width, _height) {}

		~Viewport() = default;

		void draw();

	private:
		std::pair<int, int> size = { 0, 0 };
		std::vector<int> pixels;
};