#include "Renderer.h"

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
	// Blend etc

	// Shader
	defaultShader = std::make_shared<Shader>("resources/shaders/default.vert", "resources/shaders/default.frag");
}

void SOLAR::Renderer::BeginFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
}

void SOLAR::Renderer::Draw()
{
	if (!mainScene)
		return;

	glUseProgram(defaultShader->GetProgramId());

	for (auto& mesh : mainScene->GetMeshes())
	{
		mesh->Bind();
		mesh->Draw();
		mesh->Unbind();
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