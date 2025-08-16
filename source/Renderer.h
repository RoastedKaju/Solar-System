#ifndef RENDERER_H
#define RENDERER_H

#include <GLFW/glfw3.h>

#include "PCH.h"

namespace SOLAR
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void Init();
		void BeginFrame();
		void Draw();
		void EndFrame();

		void SetClearColor(float r, float g, float b, float a);

	private:
		float clearColor[4];
	};
}

#endif // !RENDERER_H
