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

		void Init();
		void Update(float deltaTime);
		void Render();
		void Shutdown();
	};
}

#endif // !APPLICATION_H
