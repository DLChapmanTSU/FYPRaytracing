#include "Helpers.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <assert.h>

std::string Helpers::FetchShaderCode(std::string& directory)
{
	std::string fileContents;
	std::string lineContents;

	std::ifstream shaderReader(directory);

	while (std::getline(shaderReader, lineContents))
	{
		fileContents += lineContents;
		fileContents += '\n';
	}

	shaderReader.close();

	std::cout << std::endl;
	std::cout << fileContents << std::endl;

	return fileContents;
}

unsigned int Helpers::CreateShader(const std::string& vertex, const std::string& fragment)
{
	unsigned int program = glCreateProgram();
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertex);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragment);

	assert(vertexShader != 0 && fragmentShader != 0);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return program;
}

unsigned int Helpers::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//Error checks
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed shader compile!" << std::endl;
		switch (type)
		{
		case GL_VERTEX_SHADER:
			std::cout << "VERTEX SHADER" << std::endl;
			break;
		case GL_FRAGMENT_SHADER:
			std::cout << "FRAGMENT SHADER" << std::endl;
			break;
		case GL_COMPUTE_SHADER:
			std::cout << "COMPUTE SHADER" << std::endl;
			break;
		default:
			std::cout << "UNEXPECTED TYPE" << std::endl;
			break;
		}
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}
