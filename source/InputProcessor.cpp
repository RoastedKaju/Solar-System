#include "InputProcessor.h"

SOLAR::InputProcessor::InputProcessor(GLFWwindow* window)
{
	this->window = window;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetWindowUserPointer(window, this);

	glfwSetKeyCallback(window, &SOLAR::InputProcessor::KeyCallback);
	glfwSetCursorPosCallback(window, &SOLAR::InputProcessor::MouseCallback);
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

void SOLAR::InputProcessor::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	InputProcessor* inputProcessor = static_cast<InputProcessor*>(glfwGetWindowUserPointer(window));
	if (!inputProcessor)
		return;

	if (inputProcessor->isFirstMove)
	{
		inputProcessor->lastx = xpos;
		inputProcessor->lasty = ypos;
		inputProcessor->isFirstMove = false;
		return;
	}

	double xoffset = xpos - inputProcessor->lastx;
	double yoffset = inputProcessor->lasty - ypos;
	inputProcessor->lastx = xpos;
	inputProcessor->lasty = ypos;

	EventDispatcher::Get().Broadcast(MouseMovedEvent(xoffset, yoffset));
}
