#include "Mesh.h"

SOLAR::Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indicies) :
	vertices{ vertices },
	indices{ indicies },
	VAO{ 0 },
	VBO{ 0 },
	EBO{ 0 },
	position{ glm::vec3(0.0f) },
	rotation{ glm::vec3(0.0f) },
	scale{ glm::vec3(1.0f) }
{
	SetupMesh();
}

SOLAR::Mesh::~Mesh()
{

}

void SOLAR::Mesh::Draw()
{
	// Draw Mesh
	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
}

void SOLAR::Mesh::Bind()
{
	glBindVertexArray(VAO);
}

void SOLAR::Mesh::Unbind()
{
	glBindVertexArray(0);
}

void SOLAR::Mesh::SetupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);
}