#ifndef APPLICATION_H
#define APPLICATION_H

#include "PCH.h"
#include "Window.h"
#include "Renderer.h"

namespace SOLAR
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

	private:
		std::unique_ptr<Window> mainWindow;
		std::unique_ptr<Renderer> renderer;

		double lastFrame = 0.0;
		double deltaTime = 0.0;

		void Init();
		void Update();
		void Render();
		void Shutdown();
	};
}

#endif // !APPLICATION_H
