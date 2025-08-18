#include "Application.h"

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

	/// Debug QUAD
	std::vector<float> debug_vertices = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};

	std::vector<unsigned int> debug_indices = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	// Scene
	std::shared_ptr<Scene> quadScene = std::make_shared<Scene>("quadScene");
	std::shared_ptr<Mesh> quadMesh = std::make_shared<Mesh>(debug_vertices, debug_indices);

	quadScene->AddMesh(quadMesh);

	renderer->SetScene(quadScene);
	/// Debug QUAD END

}

void SOLAR::Application::Update()
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