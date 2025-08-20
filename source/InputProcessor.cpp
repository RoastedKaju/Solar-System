#include "InputProcessor.h"

SOLAR::InputProcessor::InputProcessor(GLFWwindow* window)
{
	this->window = window;
	glfwSetKeyCallback(window, &SOLAR::InputProcessor::KeyCallback);
}

SOLAR::InputProcessor::~InputProcessor()
{

}

void SOLAR::InputProcessor::ProcessInput(double deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		EventDispatcher::Get().Broadcast(KeyPressedEvent(GLFW_KEY_W));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		EventDispatcher::Get().Broadcast(KeyPressedEvent(GLFW_KEY_A));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		EventDispatcher::Get().Broadcast(KeyPressedEvent(GLFW_KEY_S));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		EventDispatcher::Get().Broadcast(KeyPressedEvent(GLFW_KEY_D));
	}
}

void SOLAR::InputProcessor::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	EventDispatcher::Get().Broadcast(KeyPressedEvent(key));
}
