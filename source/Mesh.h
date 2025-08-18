#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>

#include "PCH.h"
#include "Shader.h"

namespace SOLAR
{
	class Mesh
	{
	public:
		Mesh(std::vector<float> vertices, std::vector<unsigned int> indicies);
		~Mesh();

		void Draw();

		void Bind();
		void Unbind();

	private:
		std::vector<float> vertices;
		std::vector<unsigned int> indices;

		unsigned int VAO, VBO, EBO;

		void SetupMesh();
	};
}

#endif // !MESH_H
