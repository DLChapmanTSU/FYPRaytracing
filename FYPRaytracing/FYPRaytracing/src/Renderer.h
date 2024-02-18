#pragma once
#include <vector>

class Model;

class Renderer
{
private:
	//TODO: List of lights when light class is done

	unsigned int m_mainProgram{ 0 };
public:
	Renderer();
	~Renderer();

	bool InitialiseGeometry(std::vector<Model*>& m);
};