#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "PCH.h"

namespace SOLAR
{
	class Shader
	{
	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		std::string ReadShaderFile(const char* path);

		inline GLuint GetProgramId() const { return programId; }

	private:
		GLuint programId;

		std::string vertShader;
		std::string fragShader;

		GLuint CompileShader(const char* source, GLenum type);
		void CreateShaders();
	};
}

#endif // !SHADER_H
