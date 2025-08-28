#include "InputProcessor.h"

SOLAR::InputProcessor::InputProcessor(GLFWwindow* window)
{
	this->window = window;

	glfwSetWindowUserPointer(window, this);

	glfwSetKeyCallback(window, &SOLAR::InputProcessor::KeyCallback);
	glfwSetCursorPosCallback(window, &SOLAR::InputProcessor::MouseCallback);
	glfwSetMouseButtonCallback(window, &SOLAR::InputProcessor::MouseButtonCallback);
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

void SOLAR::InputProcessor::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		// To reset the offset once we switch back to moving camera
		InputProcessor* inputProcessor = static_cast<InputProcessor*>(glfwGetWindowUserPointer(window));
		if (!inputProcessor)
			return;
		inputProcessor->isFirstMove = true;

		EventDispatcher::Get().Broadcast(MousePressedEvent(GLFW_MOUSE_BUTTON_1, window));
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE)
	{
		EventDispatcher::Get().Broadcast(MouseReleasedEvent(GLFW_MOUSE_BUTTON_1, window));
	}
}