#include <stb_image.h>

#include "Skybox.h"

SOLAR::Skybox::Skybox(const std::vector<std::string>& texturePaths) :
	VAO{ 0 },
	VBO{ 0 },
	id{ 0 }
{
	LoadTextures(texturePaths);
	SetupSkybox();
}

SOLAR::Skybox::~Skybox()
{

}

void SOLAR::Skybox::Draw(Shader& shader) const
{
	// Texture
	glUniform1i(shader.GetUniformLocation("skybox"), 0);
	// Remember to use bind texture when creating texture objects (Gen Texture) else it would automatically bind it to next Slot i.e. 1 in this case
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void SOLAR::Skybox::Bind() const
{
	glBindVertexArray(VAO);
}

void SOLAR::Skybox::Unbind() const
{
	glBindVertexArray(0);
}

void SOLAR::Skybox::LoadTextures(const std::vector<std::string>& textureFaces)
{
	// Generate Texture object
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);

	// Because a cubemap has 6 sides we have to call glTexImage2D six times
	int width, height, nrChannels;
	unsigned char* data;
	for (unsigned int i = 0; i < textureFaces.size(); i++)
	{
		data = stbi_load(textureFaces.at(i).c_str(), &width, &height, &nrChannels, 0);
		if (!data)
		{
			fmt::print(fg(fmt::color::crimson), "Skybox texture loading error: No Data\n");
			stbi_image_free(data);
			return;
		}

		// Channel
		GLenum imageFormat = GL_RGB;
		switch (nrChannels)
		{
		case 1:
			imageFormat = GL_RED;
			break;
		case 2:
			imageFormat = GL_RG;
			break;
		case 3:
			imageFormat = GL_RGB;
			break;
		case 4:
			imageFormat = GL_RGBA;
			break;
		default:
			fmt::print(fg(fmt::color::crimson), "Skybox texture loading error: Invalid channel\n");
			break;
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, imageFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void SOLAR::Skybox::SetupSkybox()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);

	// Attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // position
	glEnableVertexAttribArray(0);

	// Reset
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}