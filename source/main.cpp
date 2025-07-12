#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/format.h>

int main()
{
	if (!glfwInit())
	{
		fmt::print(fmt::fg(fmt::color::crimson), "Failed to init GLFW");
		return EXIT_FAILURE;
	}

	// Windows
	GLFWwindow* mainWindow = glfwCreateWindow(800, 600, "Solar System", nullptr, nullptr);

	if (!mainWindow)
	{
		fmt::print(fmt::fg(fmt::color::crimson), "Invalid window");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Hints
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GL_TRUE);

	glfwMakeContextCurrent(mainWindow);

	if (glewInit() != GLEW_OK)
	{
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		fmt::print(fmt::fg(fmt::color::crimson), "GLEW failed to init.");
		return EXIT_FAILURE;
	}

	glViewport(0, 0, 800, 600);

	while (!glfwWindowShouldClose(mainWindow))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		glfwSwapBuffers(mainWindow);
	}

	glfwDestroyWindow(mainWindow);
	glfwTerminate();
	return EXIT_SUCCESS;
}