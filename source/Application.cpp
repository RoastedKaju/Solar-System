#include "Application.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Shader.h"
#include "Mesh.h"
#include "Scene.h"

SOLAR::Application::Application()
{
	Init();
}

SOLAR::Application::~Application()
{

}

void SOLAR::Application::Run()
{
	lastFrame = glfwGetTime();

	while (!glfwWindowShouldClose(mainWindow->GetNativeWindow()))
	{
		const double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		Update();							// Application logic
		Render();							// Rendering

		mainWindow->Update(deltaTime);		// Window and event handling
	}

	Shutdown();
}

void SOLAR::Application::Init()
{
	if (!glfwInit())
	{
		fmt::print(fmt::fg(fmt::color::crimson), "Failed to Init GLFW\n");
		return;
	}

	mainWindow = std::make_unique<Window>("Solar System", 1280, 720);

	if (!mainWindow->GetNativeWindow())
	{
		fmt::print(fmt::fg(fmt::color::crimson), "Window initialization failed\n");
		glfwTerminate();
		return;
	}

	// Renderer
	renderer = std::make_unique<Renderer>();

	// Input manager
	inputManager = std::make_unique<InputProcessor>(mainWindow->GetNativeWindow());

	// UI
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(mainWindow->GetNativeWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Scene
	solarScene = std::make_shared<Scene>("Solar System");
	renderer->SetScene(solarScene);
}

void SOLAR::Application::Update()
{
	if (inputManager)
	{
		inputManager->ProcessInput(deltaTime);
	}

	if (solarScene)
	{
		solarScene->Update(deltaTime);
	}
}

void SOLAR::Application::Render()
{
	if (renderer)
	{
		renderer->BeginFrame();
		renderer->Draw(deltaTime);
		renderer->EndFrame();

		renderer->DrawUI(*mainWindow->GetNativeWindow());
	}
}

void SOLAR::Application::Shutdown()
{
	// UI
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(mainWindow->GetNativeWindow());
	glfwTerminate();
}