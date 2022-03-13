#pragma once
#include "Vector3.h"
#include "Vector2.h"

using Indices = unsigned short;

struct Vertex
{
	Vertex() {}
	
	Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v) 
		: position(x, y, z), normal(nx, ny, nz), texcoord(u, v) {}
	
	Vertex(Vector3 _position, Vector3 _normal, Vector2 _uv) 
		: position(_position), normal(_normal), texcoord(_uv) {}

	Vector3 position	= { 0.0f, 0.0f, 0.0f };
	Vector3 normal		= { 0.0f, 0.0f, 0.0f };
	Vector2 texcoord	= { 0.0f, 0.0f };
};

struct Triangle
{
	Vertex vert0;
	Vertex vert1;
	Vertex vert2;
};
