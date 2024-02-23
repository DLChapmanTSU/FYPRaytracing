#pragma once
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL_Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}

	return true;
}

class Model;

class Helpers
{
public:
	static std::string FetchShaderCode(std::string& directory);
	static unsigned int CreateShader(const std::string& vertex, const std::string& fragment);
	static unsigned int CompileShader(unsigned int type, const std::string& source);
	static bool LoadObjFile(std::string& directory, Model& m);
	static bool LoadTexFile(std::string& directory, Model& m);
};