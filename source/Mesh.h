#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "PCH.h"
#include "Shader.h"

namespace SOLAR
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
		glm::vec3 tangent;
		glm::vec3 bitangent;
	};

	struct Texture
	{
		unsigned int id;
		std::string type;
		std::string path;
	};

	class Mesh
	{
	public:
		Mesh(std::vector<float> vertices, std::vector<unsigned int> indicies);
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indicies, std::vector<Texture> textures);
		~Mesh();

		void Draw(Shader& shader);

		void Bind();
		void Unbind();

		inline void SetPosition(const glm::vec3& position) { this->position = position; }
		inline void SetRotation(const glm::vec3& rotation) { this->rotation = rotation; }
		inline void SetScale(const glm::vec3& scale) { this->scale = scale; }

		inline const glm::vec3& GetPosition() const { return position; }
		inline const glm::vec3& GetRotation() const { return rotation; }
		inline const glm::vec3& GetScale() const { return scale; }

	private:
		std::vector<float> vertices;
		std::vector<Vertex> vertexList;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		unsigned int VAO, VBO, EBO;

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		void SetupMesh(bool primitive);

	};
}

#endif // !MESH_H
