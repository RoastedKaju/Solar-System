#include "Application.h"

SOLAR::Application::Application()
{
	Init();
}

SOLAR::Application::~Application()
{

}

void SOLAR::Application::Run()
{
	while (!glfwWindowShouldClose(mainWindow->GetNativeWindow()))
	{
		float deltaTime = 0.016f;

		Update(deltaTime);					// Application logic
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

}

void SOLAR::Application::Update(float deltaTime)
{

}

void SOLAR::Application::Render()
{
	if (renderer)
	{
		renderer->BeginFrame();
		renderer->Draw();
		renderer->EndFrame();
	}
}

void SOLAR::Application::Shutdown()
{
	glfwDestroyWindow(mainWindow->GetNativeWindow());
	glfwTerminate();
}