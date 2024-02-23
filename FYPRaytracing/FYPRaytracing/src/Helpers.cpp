#include "Helpers.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <sstream>
#include "Model.h"

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

	GLCall(glAttachShader(program, vertexShader));
	GLCall(glAttachShader(program, fragmentShader));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vertexShader));
	GLCall(glDeleteShader(fragmentShader));
	return program;
}

unsigned int Helpers::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	//Error checks
	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
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
		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

bool Helpers::LoadObjFile(std::string& directory, Model& m)
{
	//Will load an obj file and add it as a mesh to a given model
	//Will break with different file types
	//I used the tutorial below to write this. I'm not taking credit for this function
	//https://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	std::ifstream reader(directory);

	if (reader.bad())
		return false;

	std::string lineContents;
	while (std::getline(reader, lineContents))
	{
		if (lineContents.length() < 3)
			continue;

		if ((lineContents[0] == 'v' || lineContents[0] == 'V') && (lineContents[1] != 't' && lineContents[1] != 'T') && (lineContents[1] != 'n' && lineContents[1] != 'N'))
		{
			lineContents.erase(0, 2);
			std::stringstream stream(lineContents);
			glm::vec3 vertex;
			stream >> vertex.x >> vertex.y >> vertex.z;
			temp_vertices.push_back(vertex);
		}
		else if ((lineContents[0] == 'v' || lineContents[0] == 'V') && (lineContents[1] == 't' || lineContents[1] == 'T'))
		{
			lineContents.erase(0, 3);
			std::stringstream stream(lineContents);
			glm::vec2 uv;
			stream >> uv.x >> uv.y;
			temp_uvs.push_back(uv);
		}
		else if ((lineContents[0] == 'v' || lineContents[0] == 'V') && (lineContents[1] == 'n' || lineContents[1] == 'N'))
		{
			lineContents.erase(0, 3);
			std::stringstream stream(lineContents);
			glm::vec3 normal;
			stream >> normal.x >> normal.y >> normal.z;
			temp_normals.push_back(normal);
		}
		else if (lineContents[0] == 'f' || lineContents[0] == 'f')
		{
			//If indices don't follow the format X/X/X X/X/X X/X/X then this will fail
			//TODO: Handle different F formats
			int dashCount = 0;
			for (size_t i = 0; i < lineContents.length(); i++)
			{
				if (lineContents[i] == '/')
				{
					lineContents.replace(i, 1, " ");
					dashCount++;
				}
			}

			if (dashCount != 6)
				return false;

			lineContents.erase(0, 2);

			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			std::stringstream stream(lineContents);
			stream >> vertexIndex[0] >> uvIndex[0] >> normalIndex[0] >> vertexIndex[1] >> uvIndex[1] >> normalIndex[1] >> vertexIndex[2] >> uvIndex[2] >> normalIndex[2];
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	m.MakeNewMesh(temp_vertices, temp_uvs, temp_normals, vertexIndices, uvIndices, normalIndices);

	return true;
}

bool Helpers::LoadTexFile(std::string& directory, Model& m)
{
	return false;
}
