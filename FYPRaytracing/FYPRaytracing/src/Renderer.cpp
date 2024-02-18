#include "Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Helpers.h"
#include "Model.h"

Renderer::Renderer()
{
    std::string vertexDirectory = "src/Shaders/exampleVertex.glsl";
    std::string vertexShader = Helpers::FetchShaderCode(vertexDirectory);
    std::string fragmentDirectory = "src/Shaders/exampleFragment.glsl";
    std::string fragmentShader = Helpers::FetchShaderCode(fragmentDirectory);

    m_mainProgram = Helpers::CreateShader(vertexShader, fragmentShader);
    glUseProgram(m_mainProgram);
}

Renderer::~Renderer()
{
	glDeleteProgram(m_mainProgram);
}

bool Renderer::InitialiseGeometry(std::vector<Model*>& m)
{
    for (Model* model : m)
    {
        if (!model->LoadModelFiles())
            return false;

        model->Initialise();
    }

    return true;
}
