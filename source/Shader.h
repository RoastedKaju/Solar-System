#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

		GLint GetUniformLocation(const char* name) const;

		inline void SetInt(const char* name, int value) const
		{
			glUniform1i(GetUniformLocation(name), value);
		}

		inline void SetFloat(const char* name, float value) const
		{
			glUniform1f(GetUniformLocation(name), value);
		}

		inline void SetVec3(const char* name, const glm::vec3& value) const
		{
			glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
		}

		inline void SetMat4(const char* name, const glm::mat4& value) const
		{
			glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
		}

	private:
		GLuint programId;

		std::string vertShader;
		std::string fragShader;

		GLuint CompileShader(const char* source, GLenum type);
		void CreateShaders();
	};
}

#endif // !SHADER_H