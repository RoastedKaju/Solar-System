#ifndef SCENE_H
#define SCENE_H

#include "PCH.h"
#include "Model.h"
#include "Mesh.h"
#include "Camera.h"
#include "Skybox.h"

namespace SOLAR
{
	class Scene
	{
	public:
		Scene(std::string sceneName);
		~Scene() {};

		inline void AddMesh(std::shared_ptr<Mesh> mesh) { meshes.push_back(mesh); }
		inline void AddModel(std::shared_ptr<Model> model) { models.push_back(model); }
		inline std::vector<std::shared_ptr<Mesh>> GetMeshes() const { return meshes; }
		inline std::vector<std::shared_ptr<Model>> GetModels() const { return models; }

		inline std::shared_ptr<Camera> GetCamera() const { return mainCamera; }

		inline void SetSkybox(std::shared_ptr<Skybox> skybox) { skyboxMesh = skybox; }
		inline std::shared_ptr<Skybox> GetSkybox() const { return skyboxMesh; }

	private:
		std::string sceneName;
		std::shared_ptr<Camera> mainCamera;
		std::vector<std::shared_ptr<Mesh>> meshes;
		std::vector<std::shared_ptr<Model>> models;
		std::shared_ptr<Skybox> skyboxMesh;
	};
}

#endif // !SCENE_H
