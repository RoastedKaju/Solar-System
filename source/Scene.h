#ifndef SCENE_H
#define SCENE_H

#include "PCH.h"
#include "Mesh.h"

namespace SOLAR
{
	class Scene
	{
	public:
		Scene(std::string sceneName) : sceneName{ sceneName } {};
		~Scene() {};

		inline void AddMesh(std::shared_ptr<Mesh> mesh) { meshes.push_back(mesh); }
		inline std::vector<std::shared_ptr<Mesh>> GetMeshes() const { return meshes; }

	private:
		std::string sceneName;
		std::vector<std::shared_ptr<Mesh>> meshes;
	};
}

#endif // !SCENE_H
