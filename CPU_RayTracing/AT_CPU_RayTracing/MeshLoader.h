#pragma once
// Assimp
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <assimp\matrix4x4.h>
#include <assimp\cimport.h>

// C++
#include <string>
#include <vector>

// Custom
#include "Vertex.h"

class MeshLoader
{
public:
	// Loads a mesh from file and writes contents to the vertex buffer
	MeshLoader(std::string file_path, std::vector<Vertex>& vertex_buffer);
	
	~MeshLoader() = default;

private:
	Assimp::Importer importer;
	const aiScene* pScene;
	const aiMesh* pMesh;

	bool LoadMeshData(std::vector<Vertex>& vertex_buffer);
};
