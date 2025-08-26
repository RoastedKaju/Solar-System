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
		~Scene() { fmt::print(fmt::fg(fmt::color::orange), "Scene destroyed.\n"); };

		inline void AddMesh(std::shared_ptr<Mesh> mesh) { meshes.push_back(mesh); }
		inline void AddModel(std::shared_ptr<Model> model) { models.push_back(model); }
		inline std::vector<std::shared_ptr<Mesh>> GetMeshes() const { return meshes; }
		inline std::vector<std::shared_ptr<Model>> GetModels() const { return models; }

		inline std::shared_ptr<Camera> GetCamera() const { return mainCamera; }

		inline void SetSkybox(std::shared_ptr<Skybox> skybox) { skyboxMesh = skybox; }
		inline std::shared_ptr<Skybox> GetSkybox() const { return skyboxMesh; }

		void Update(double deltaTime);

	private:
		std::string sceneName;
		std::shared_ptr<Camera> mainCamera;
		std::vector<std::shared_ptr<Mesh>> meshes;
		std::vector<std::shared_ptr<Model>> models;
		std::shared_ptr<Skybox> skyboxMesh;

		std::unordered_map<std::string, std::shared_ptr<Model>> nameToPlanetMap;

		float rotationScale;

		void InitSolarScene();
		void OribitPlanet(std::shared_ptr<Model> planet, float deltaTime);
	};
}

#endif // !SCENE_H
