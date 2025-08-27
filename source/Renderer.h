#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "PCH.h"
#include "Scene.h"
#include "Shader.h"

namespace SOLAR
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void Init();
		void BeginFrame();
		void Draw(double deltaTime);
		void EndFrame();

		void DrawUI(GLFWwindow& window);

		void SetClearColor(float r, float g, float b, float a);

		inline void SetScene(std::shared_ptr<Scene> scene) { mainScene = scene; }

	private:
		float clearColor[4];

		std::shared_ptr<Shader> defaultShader;
		std::shared_ptr<Shader> skyboxShader;
		std::shared_ptr<Scene> mainScene;
	};
}

#endif // !RENDERER_H
