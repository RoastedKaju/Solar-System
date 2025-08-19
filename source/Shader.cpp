#include "Shader.h"

#include <istream>
#include <fstream>
#include <sstream>

SOLAR::Shader::Shader(const char* vertPath, const char* fragPath)
{
	programId = 0;

	vertShader = ReadShaderFile(vertPath);
	fragShader = ReadShaderFile(fragPath);

	CreateShaders();
}

SOLAR::Shader::~Shader()
{

}

std::string SOLAR::Shader::ReadShaderFile(const char* path)
{
	std::string sourceCode;
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		shaderFile.open(path);
		std::stringstream shaderStream;

		// stream buffer into stream
		shaderStream << shaderFile.rdbuf();

		// Close handles
		shaderFile.close();

		return shaderStream.str();
	}
	catch (std::ifstream::failure error)
	{
		fmt::print(fmt::fg(fmt::color::crimson), "Could not read file {} Error encountered: {}\n", path, error.what());
	}

	return std::string{};
}

GLint SOLAR::Shader::GetUniformLocation(const char* name) const
{
	GLint location = glGetUniformLocation(programId, name);

	if (location == -1) 
		fmt::print(fmt::fg(fmt::color::crimson), "Uniform {} Location Not Found.\n", name);

	return location;
}

GLuint SOLAR::Shader::CompileShader(const char* source, GLenum type)
{
	GLuint shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, &source, nullptr);

	glCompileShader(shaderId);
	// Error checking
	int result;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);

		glGetShaderInfoLog(shaderId, length, &length, log.data());
		fmt::print(fmt::fg(fmt::color::crimson), "COMPILE SHADER ERROR: {}", log.data());
	}

	return shaderId;
}

void SOLAR::Shader::CreateShaders()
{
	programId = glCreateProgram();
	GLuint vs = CompileShader(vertShader.c_str(), GL_VERTEX_SHADER);
	GLuint fs = CompileShader(fragShader.c_str(), GL_FRAGMENT_SHADER);

	glAttachShader(programId, vs);
	glAttachShader(programId, fs);

	glLinkProgram(programId);
	// Error checking
	int result;
	glGetProgramiv(programId, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);

		glGetProgramInfoLog(programId, length, &length, log.data());
		fmt::print(fmt::fg(fmt::color::crimson), "LINK PROGRAM ERROR: {}", log.data());
	}

	glValidateProgram(programId);

	glDeleteShader(vs);
	glDeleteShader(fs);
}