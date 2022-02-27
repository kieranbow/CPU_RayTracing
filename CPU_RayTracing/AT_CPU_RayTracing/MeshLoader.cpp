#include "MeshLoader.h"

MeshLoader::MeshLoader(std::string file_path, std::vector<Vertex>& vertex_buffer, std::vector<Indices>& index_buffer)
{
	// Read the mesh file from assimp importer and process the files data using aiProcess flags
	pScene = importer.ReadFile(file_path, aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_Triangulate);

	// If pScene is null, then the importer failed to read the file
	if (pScene == NULL)
	{
		std::cerr << "failed to read " + file_path << std::endl;
	}

	// Check if assimp loaded the mesh data. 
	if (!LoadMeshData(vertex_buffer, index_buffer))
	{
		std::cerr << "Assimp failed to create mesh from " + file_path << std::endl;
	}
}

bool MeshLoader::LoadMeshData(std::vector<Vertex>& vertex_buffer, std::vector<Indices>& index_buffer)
{
	// Loop through all the meshes within the 'scene' and assign each mesh to pMesh.
	// This only works if the imported mesh has seperate meshes within the same file.
	for (unsigned int m = 0; m < pScene->mNumMeshes; m++)
	{
		pMesh = pScene->mMeshes[m];

		// Loop through each vertex and transfer the position, normals and texcoord 
		// to vertex buffer
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

			// Check if the vertex has texcoord data
			if (pMesh->HasTextureCoords(0))
			{
				vertex.texcoord.setX(pMesh->mTextureCoords[0][vrtIdx].x);
				vertex.texcoord.setY(pMesh->mTextureCoords[0][vrtIdx].y);
			}
			vertex_buffer.push_back(vertex);
		}

		// Since 3 indices make a triangle in assimp, loop through the meshes faces and
		// store each indice in the index buffer
		for (unsigned int i = 0; i < pMesh->mNumFaces; i++)
		{
			aiFace* face = &pMesh->mFaces[i];

			if (face->mNumIndices == 3)
			{
				index_buffer.push_back(face->mIndices[0]);
				index_buffer.push_back(face->mIndices[1]);
				index_buffer.push_back(face->mIndices[2]);
			}
		}
	}
	return true;
}
