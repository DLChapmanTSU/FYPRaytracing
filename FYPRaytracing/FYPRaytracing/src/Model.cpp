#include "Model.h"
#include "Helpers.h"

Model::Model(std::vector<std::string>& obj, std::vector<std::string>& tex)
{
	m_objDirectories = obj;
	m_texDirectories = tex;
}

Model::~Model()
{
}

void Model::MakeNewMesh(std::vector<glm::vec3>& vert, std::vector<glm::vec2>& uv, std::vector<glm::vec3>& norm, std::vector<unsigned int>& vertE, std::vector<unsigned int>& uvE, std::vector<unsigned int>& normE)
{
	Mesh m;
	m.m_vertices = vert;
	m.m_uvs = uv;
	m.m_normals = norm;
	m.m_vertexElements = vertE;
	m.m_uvElements = uvE;
	m.m_normalElements = normE;
	m.m_elementCount = vertE.size();

	m_meshes.push_back(m);
}

bool Model::LoadModelFiles()
{
	for (std::string dir : m_objDirectories)
	{
		if (!Helpers::LoadObjFile(dir, *this))
			return false;
	}

	//TODO: Texture stuff here
	return true;
}

void Model::Initialise()
{
	for (Mesh& mesh : m_meshes)
	{
		//Creates VBOs out of loaded data
		GLuint vertexVBO;
		
		GLCall(glGenBuffers(1, &vertexVBO));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexVBO));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh.m_vertices.size(), mesh.m_vertices.data(), GL_STATIC_DRAW));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

		GLuint normalsVBO;

		GLCall(glGenBuffers(1, &normalsVBO));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, normalsVBO));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh.m_normals.size(), mesh.m_normals.data(), GL_STATIC_DRAW));

		GLuint elementsVBO;

		GLCall(glGenBuffers(1, &elementsVBO));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsVBO));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.m_vertexElements.size(), mesh.m_vertexElements.data(), GL_STATIC_DRAW));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

		//TODO: Add in other elements

		/*GLuint textureCoordsVBO;

		glGenBuffers(1, &textureCoordsVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textureCoordsVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::vec2) * mesh.m_uvs.size(), mesh.m_uvs.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/

		
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

		//Binds all VBOs to the VAO
		GLCall(glGenVertexArrays(1, &mesh.m_VAO));
		GLCall(glBindVertexArray(mesh.m_VAO));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexVBO));
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));

		//glBindBuffer(GL_ARRAY_BUFFER, textureCoordsVBO);
		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, normalsVBO));
		GLCall(glEnableVertexAttribArray(1));
		GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));

		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsVBO));

		GLCall(glBindVertexArray(0));
	}
}

std::vector<Model::Mesh>& Model::GetMeshes()
{
	return m_meshes;
}

glm::vec3 Model::GetWorldPosition()
{
	return m_worldPosition;
}

void Model::SetWorldPosition(glm::vec3 p)
{
	m_worldPosition = p;
}
