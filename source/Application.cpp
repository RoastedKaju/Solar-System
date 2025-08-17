#include "Application.h"

#include "Shader.h"
#include "Mesh.h"

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
	Shader defaultShader("resources/shaders/default.vert", "resources/shaders/default.frag");
	Mesh* mesh = new Mesh(debug_vertices, debug_indices);
/// Debug QUAD END

	while (!glfwWindowShouldClose(mainWindow->GetNativeWindow()))
	{
		const double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		Update();							// Application logic
		Render();							// Rendering

		mesh->Draw(defaultShader);

		mainWindow->Update(deltaTime);		// Window and event handling
	}

	delete mesh;

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