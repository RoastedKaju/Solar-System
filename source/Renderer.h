#ifndef RENDERER_H
#define RENDERER_H

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
		void EndFrame();

		void SetClearColor(float r, float g, float b, float a);
		void Draw();

	private:
		float clearColor[4];
	};
}

#endif // !RENDERER_H
