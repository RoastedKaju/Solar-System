#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "PCH.h"

#include <GLFW/glfw3.h>

namespace SOLAR
{
	class UserInterface
	{
	public:
		UserInterface(GLFWwindow* window);
		~UserInterface();

		void ShowHint();
		void CameraModePicker();

		inline GLFWwindow* GetWindow() const { return window; }

	private:
		GLFWwindow* window;

		std::vector<std::string> cameraModes;
	};
}

#endif // !USER_INTERFACE_H
