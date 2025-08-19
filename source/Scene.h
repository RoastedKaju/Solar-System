#ifndef SCENE_H
#define SCENE_H

#include "PCH.h"
#include "Mesh.h"
#include "Camera.h"

namespace SOLAR
{
	class Scene
	{
	public:
		Scene(std::string sceneName);
		~Scene() {};

		inline void AddMesh(std::shared_ptr<Mesh> mesh) { meshes.push_back(mesh); }
		inline std::vector<std::shared_ptr<Mesh>> GetMeshes() const { return meshes; }

		inline std::shared_ptr<Camera> GetCamera() const { return mainCamera; }

	private:
		std::string sceneName;
		std::shared_ptr<Camera> mainCamera;
		std::vector<std::shared_ptr<Mesh>> meshes;
	};
}

#endif // !SCENE_H
