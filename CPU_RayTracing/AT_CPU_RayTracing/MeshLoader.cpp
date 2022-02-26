#include "MeshLoader.h"

MeshLoader::MeshLoader(std::string file_path, std::vector<Vertex>& vertex_buffer)
{
	// Read the mesh file from assimp importer and process the files data using aiProcess flags
	pScene = importer.ReadFile(file_path, aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_Triangulate);

	// If pScene is null, then the importer failed to read the file
	if (pScene == NULL)
	{
		std::cerr << "failed to read " + file_path << std::endl;
	}

	// Check if assimp loaded the mesh data. 
	if (!LoadMeshData(vertex_buffer))
	{
		std::cerr << "Assimp failed to create mesh from " + file_path << std::endl;
	}
}

bool MeshLoader::LoadMeshData(std::vector<Vertex>& vertex_buffer)
{
	for (unsigned int m = 0; m < pScene->mNumMeshes; m++)
	{
		pMesh = pScene->mMeshes[m];

		for (unsigned int vrtIdx = 0; vrtIdx < pMesh->mNumVertices; vrtIdx++)
		{
			Vertex vertex;

			// Vertex position
			vertex.position.setX(pMesh->mVertices[vrtIdx].x);
			vertex.position.setY(pMesh->mVertices[vrtIdx].y);
			vertex.position.setZ(pMesh->mVertices[vrtIdx].z);

			// Vertex normal
			vertex.normal.setX(pMesh->mNormals[vrtIdx].x);
			vertex.normal.setY(pMesh->mNormals[vrtIdx].y);
			vertex.normal.setZ(pMesh->mNormals[vrtIdx].z);

			// Vertex texture coords
			if (pMesh->HasTextureCoords(0))
			{
				vertex.texcoord.setX(pMesh->mTextureCoords[0][vrtIdx].x);
				vertex.texcoord.setY(pMesh->mTextureCoords[0][vrtIdx].y);
			}

			vertex_buffer.push_back(vertex);
		}
	}
	return true;
}
