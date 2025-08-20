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

	private:
		GLFWwindow* window;
	};
}

#endif // INPUT_PROCESSOR_H
