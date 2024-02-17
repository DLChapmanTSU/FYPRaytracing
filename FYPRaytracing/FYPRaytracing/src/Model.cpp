#include "Model.h"

Model::Model()
{
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
