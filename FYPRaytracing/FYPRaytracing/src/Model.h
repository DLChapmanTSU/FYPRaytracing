#pragma once

#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Model
{
public:
	struct Mesh
	{
		std::vector<glm::vec3> m_vertices;
		std::vector<glm::vec2> m_uvs;
		std::vector<glm::vec3> m_normals;
		std::vector<unsigned int> m_vertexElements;
		std::vector<unsigned int> m_uvElements;
		std::vector<unsigned int> m_normalElements;
		unsigned int m_elementCount{ 0 };
		GLuint m_VAO{ 0 };
		glm::mat4 m_modelXForm{ glm::mat4(1) };
	};

private:
	std::vector<Mesh> m_meshes;
	std::vector<std::string> m_objDirectories;
	std::vector<std::string> m_texDirectories;
	glm::vec3 m_worldPosition{0};
public:
	Model(std::vector<std::string>& obj, std::vector<std::string>& tex);
	~Model();

	void MakeNewMesh(std::vector<glm::vec3>& vert, std::vector<glm::vec2>& uv, std::vector<glm::vec3>& norm, std::vector<unsigned int>& vertE, std::vector<unsigned int>& uvE, std::vector<unsigned int>& normE);
	bool LoadModelFiles();
	void Initialise();
	std::vector<Model::Mesh>& GetMeshes();
	glm::vec3 GetWorldPosition();
	void SetWorldPosition(glm::vec3 p);
};