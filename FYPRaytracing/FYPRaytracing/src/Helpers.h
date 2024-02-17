#pragma once
#include <string>

class Model;

class Helpers
{
public:
	static std::string FetchShaderCode(std::string& directory);
	static unsigned int CreateShader(const std::string& vertex, const std::string& fragment);
	static unsigned int CompileShader(unsigned int type, const std::string& source);
	static bool LoadObjFile(std::string& directory, Model& m);
};