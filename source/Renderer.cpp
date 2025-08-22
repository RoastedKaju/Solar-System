#include "Renderer.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

SOLAR::Renderer::Renderer()
{
	clearColor[0] = 0.5f;
	clearColor[1] = 0.5f;
	clearColor[2] = 0.3f;
	clearColor[3] = 1.0f;

	Init();
}

SOLAR::Renderer::~Renderer()
{
	fmt::print(fmt::fg(fmt::color::orange), "Renderer Object Destroyed\n");
}

void SOLAR::Renderer::Init()
{
	// Depth test
	glEnable(GL_DEPTH_TEST);
	// Blend etc

	// Shader
	defaultShader = std::make_shared<Shader>("resources/shaders/default.vert", "resources/shaders/default.frag");
}

void SOLAR::Renderer::BeginFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
}

void SOLAR::Renderer::Draw(double deltaTime)
{
	if (!mainScene)
		return;

	glUseProgram(defaultShader->GetProgramId());

	// Projection
	glm::mat4 project(1.0f);
	project = mainScene->GetCamera()->GetProjectionMatrix();
	defaultShader->SetMat4("project", project);

	// view
	mainScene->GetCamera()->Update(deltaTime);
	glm::mat4 view(1.0f);
	view = mainScene->GetCamera()->GetViewMatrix();
	defaultShader->SetMat4("view", view);

	// Primitive meshes list
	for (auto& mesh : mainScene->GetMeshes())
	{
		glm::mat4 model(1.0f);
		model = glm::translate(model, mesh->GetPosition());
		const glm::vec3 rotation = mesh->GetRotation();
		model *= glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
		model = glm::scale(model, mesh->GetScale());
		defaultShader->SetMat4("model", model);

		mesh->Bind();
		mesh->Draw(*defaultShader.get());
		mesh->Unbind();
	}

	// models list
	for (auto& mesh : mainScene->GetModels())
	{
		glm::mat4 model(1.0f);
		model = glm::translate(model, mesh->GetPosition());
		const glm::vec3 rotation = mesh->GetRotation();
		model *= glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
		model = glm::scale(model, mesh->GetScale());
		defaultShader->SetMat4("model", model);

		mesh->Draw(*defaultShader.get());	// Model's draw calls binds and unbinds the VAO inside it
	}
}

void SOLAR::Renderer::EndFrame()
{

}

void SOLAR::Renderer::SetClearColor(float r, float g, float b, float a)
{
	clearColor[0] = r;
	clearColor[1] = g;
	clearColor[2] = b;
	clearColor[3] = a;
}