#ifndef INPUT_PROCESSOR_H
#define INPUT_PROCESSOR_H

#include <GLFW/glfw3.h>

#include "PCH.h"
#include "Event.h"
#include "EventDispatcher.h"

namespace SOLAR
{
	class InputProcessor
	{
	public:
		InputProcessor(GLFWwindow* window);
		~InputProcessor();

		void ProcessInput(double deltaTime);

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	private:
		GLFWwindow* window;

		bool isFirstMove = true;
		double lastx = 400.0;
		double lasty = 300.0;
	};
}

#endif // INPUT_PROCESSOR_H
