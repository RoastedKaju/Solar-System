#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "PCH.h"
#include "Shader.h"
#include "Mesh.h"

namespace SOLAR
{
	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

	class Model
	{
	public:
		Model(std::string path, bool gammaCorrection = false);
		~Model();

		void Draw(Shader& shader);

	private:
		std::vector<Mesh> meshes;
		std::vector<Texture> texturesLoaded;
		std::string directory;
		bool gammaCorrection;

		void LoadModel(std::string path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		glm::mat4 ConvertMatrix(const aiMatrix4x4& matrix);
		
		std::vector<Texture> LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);
	};
}

#endif // !MODEL_H
