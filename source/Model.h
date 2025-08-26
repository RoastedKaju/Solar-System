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

		void ReplaceTexture(const std::string& textureType, const std::string& texturePath);

		inline void SetPosition(const glm::vec3& position) { this->position = position; }
		inline void SetRotation(const glm::vec3& rotation) { this->rotation = rotation; }
		inline void SetScale(const glm::vec3& scale) { this->scale = scale; }

		void SetRelativePosition(const glm::vec3& position);

		inline const glm::vec3& GetPosition() const { return position; }
		inline const glm::vec3& GetRotation() const { return rotation; }
		inline const glm::vec3& GetScale() const { return scale; }

		inline void SetParent(std::shared_ptr<Model> newParent) { this->parent = newParent; }
		inline std::shared_ptr<Model> GetParent() const { return parent; }

		// quick and dirty solution for planet orbits
		float theta = 0.0f;
		// Orbit speed in degrees per second
		float orbitSpeed = 75.0f;
		float orbitRadius = 50.0f;

	private:
		std::vector<Mesh> meshes;
		std::vector<Texture> texturesLoaded;
		std::string directory;
		bool gammaCorrection;

		void LoadModel(std::string path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		
		std::vector<Texture> LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);

		glm::vec3 position = glm::vec3(0.0f);
		glm::vec3 rotation = glm::vec3(0.0f);
		glm::vec3 scale = glm::vec3(1.0f);

		std::shared_ptr<Model> parent;
	};
}

#endif // !MODEL_H
