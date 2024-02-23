#pragma once
#include <vector>

class Model;
class Camera;

class Renderer
{
private:
	//TODO: List of lights when light class is done

	unsigned int m_mainProgram{ 0 };
	unsigned int m_VAO{ 0 };
	int m_numElements{ 36 };
public:
	Renderer();
	~Renderer();

	bool InitialiseGeometry(std::vector<Model*>& m);
	void Render(Camera& camera, std::vector<Model*>& models);
	void DeleteProgram();
};