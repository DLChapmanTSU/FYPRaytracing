#include "Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "Helpers.h"
#include "Model.h"
#include "Camera.h"

Renderer::Renderer()
{
    std::string vertexDirectory = "src/Shaders/mainVertex.glsl";
    std::string vertexShader = Helpers::FetchShaderCode(vertexDirectory);
    std::string fragmentDirectory = "src/Shaders/mainFragment.glsl";
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

void Renderer::Render(Camera& camera, std::vector<Model*>& models)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    const float aspectRatio = viewport[2] / (float)viewport[3];
    glm::mat4 projectionXForm = glm::perspective(glm::radians(45.0f), aspectRatio, 1.0f, 10000.0f);

    //camera xform
    glm::mat4 viewXForm = glm::lookAt(camera.GetCameraPosition(), camera.GetCameraPosition() + camera.GetForwardVector(), camera.GetUpVector());
    glm::mat4 combinedXForm = projectionXForm * viewXForm;
    
    glUseProgram(m_mainProgram);

    unsigned int camera_direction_id = glGetUniformLocation(m_mainProgram, "camera_direction");
    glUniform3fv(camera_direction_id, 1, glm::value_ptr(camera.GetForwardVector()));

    for (Model* m : models)
    {
        if (m)
        {
            for (Model::Mesh mesh : m->GetMeshes())
            {
                unsigned int combinedXFormId = glGetUniformLocation(m_mainProgram, "combined_xform");
                glUniformMatrix4fv(combinedXFormId, 0, GL_FALSE, glm::value_ptr(combinedXForm));

                // Send the model matrix to the shader in a uniform
                unsigned int modelXFormId = glGetUniformLocation(m_mainProgram, "model_xform");
                glm::mat4 translation = glm::translate(glm::mat4(1), m->GetWorldPosition());
                glm::mat4 newWorldPosition = translation * mesh.m_modelXForm;
                glUniformMatrix4fv(modelXFormId, 1, GL_FALSE, glm::value_ptr(newWorldPosition));

                //int location = glGetUniformLocation(m_mainProgram, "u_color");
                //assert(location != -1);
                //glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f);

                glBindVertexArray(mesh.m_VAO);
                glDrawElements(GL_TRIANGLES, (GLsizei)mesh.m_elementCount, GL_UNSIGNED_INT, (void*)0);
                glBindVertexArray(0);
            }
        }
    }
}

void Renderer::DeleteProgram()
{
    glDeleteProgram(m_mainProgram);
}
