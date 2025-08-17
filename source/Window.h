#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "PCH.h"

namespace SOLAR
{
	class Window
	{
	public:
		Window(const char* title, unsigned int width, unsigned int height);
		~Window();

		void Update(double deltaTime);

		void SetVsync(bool enabled);
		bool IsVsync() const;

		inline unsigned int GetWidth() const { return width; }
		inline unsigned int GetHeight() const { return height; }

		inline GLFWwindow* GetNativeWindow() const { return window; }

	private:
		GLFWwindow* window;
		std::string title;
		unsigned int width;
		unsigned int height;
		bool vsync;

		void Init();
	};
}

#endif // !WINDOW_H