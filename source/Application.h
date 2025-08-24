#ifndef APPLICATION_H
#define APPLICATION_H

#include "PCH.h"
#include "Window.h"
#include "Renderer.h"
#include "InputProcessor.h"

namespace SOLAR
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

		double GetDeltaTime() const { return deltaTime; }

	private:
		std::unique_ptr<Window> mainWindow;
		std::unique_ptr<Renderer> renderer;
		std::unique_ptr<InputProcessor> inputManager;
		std::shared_ptr<Scene> solarScene;

		double lastFrame = 0.0;
		double deltaTime = 0.0;

		void Init();
		void Update();
		void Render();
		void Shutdown();
	};
}

#endif // !APPLICATION_H
