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
    GLCall(glUseProgram(m_mainProgram));
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

	//Everything below is for the cube
	//Setting VBOs for the vertices, colours and elements
	std::vector<GLfloat> vertices{
		-10.0f,-10.0f,-10.0f, //V0
		10.0f,-10.0f,-10.0f,  //V1
		10.0f,10.0f,-10.0f,   //V2
		-10.0f,10.0f,-10.0f,  //V3
		10.0f,-10.0f,-10.0f,  //V1
		10.0f,-10.0f,10.0f,   //V5
		10.0f,10.0f,10.0f,    //V7
		10.0f,10.0f,-10.0f,   //V2
		-10.0f,-10.0f,10.0f,  //V4
		10.0f,-10.0f,10.0f,   //V5
		10.0f,10.0f,10.0f,    //V7
		-10.0f,10.0f,10.0f,   //V6
		-10.0f,-10.0f,-10.0f, //V0
		-10.0f,-10.0f,10.0f,  //V4
		-10.0f,10.0f,10.0f,   //V6
		-10.0f,10.0f,-10.0f,  //V3
		-10.0f,10.0f,-10.0f,  //V3
		10.0f,10.0f,-10.0f,   //V2
		10.0f,10.0f,10.0f,    //V7
		-10.0f,10.0f,10.0f,   //V6
		-10.0f,-10.0f,-10.0f, //V0
		10.0f,-10.0f,-10.0f,  //V1
		10.0f,-10.0f,10.0f,   //V5
		-10.0f,-10.0f,10.0f   //V4
	};

	std::vector<GLfloat> colours{
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.5f, 0.0f,
		1.0f, 0.5f, 0.0f,
		1.0f, 0.5f, 0.0f,
		1.0f, 0.5f, 0.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};

	std::vector<GLuint> elements{
		2,1,0,0,3,2,
		6,5,4,4,7,6,
		8,9,10,10,11,8,
		12,13,14,14,15,12,
		18,17,16,16,19,18,
		20,21,22,22,23,20
	};

	/*
		TODO 2: Next you need to create VBOs for the vertices and the colours
		You can look back to last week for examples
	*/

	GLuint vertexVBO;

	glGenBuffers(1, &vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint coloursVBO;

	glGenBuffers(1, &coloursVBO);
	glBindBuffer(GL_ARRAY_BUFFER, coloursVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * colours.size(), colours.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	/*
		TODO 3: You also need to create an element buffer
		Store the number of elements in the member variable m_numElements
	*/

	GLuint elementsVBO;

	glGenBuffers(1, &elementsVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * elements.size(), elements.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/*
		TODO 4: Finally create a VAO to wrap the buffers. You need to specify the streams for the positions
		(attribute 0) and colours (attribute 1). You also need to bind the element buffer.
		Use the member variable m_VAO
	*/

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, coloursVBO);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsVBO);

	glBindVertexArray(0);

    return true;
}

void Renderer::Render(Camera& camera, std::vector<Model*>& models)
{
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int viewport[4];
    GLCall(glGetIntegerv(GL_VIEWPORT, viewport));
    const float aspectRatio = viewport[2] / (float)viewport[3];
    glm::mat4 projectionXForm = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 10000.0f);

    //camera xform
    glm::mat4 viewXForm = glm::lookAt(camera.GetCameraPosition(), camera.GetCameraPosition() + camera.GetForwardVector(), glm::vec3(0, 1, 0));
    glm::mat4 combinedXForm = projectionXForm * viewXForm;
    
    GLCall(glUseProgram(m_mainProgram));

	// Send the combined matrix to the shader in a uniform
	GLuint combined_xform_id = glGetUniformLocation(m_mainProgram, "combined_xform");
	glUniformMatrix4fv(combined_xform_id, 1, GL_FALSE, glm::value_ptr(combinedXForm));

	glm::mat4 model_xform = glm::mat4(1);

	// Uncomment all the lines below to rotate cube first round y then round x
	static float angle = 0;
	static bool rotateY = true;

	//if (rotateY) // Rotate around y axis		
	//	model_xform = glm::rotate(model_xform, angle, glm::vec3{ 0 ,1,0 });
	//else // Rotate around x axis		
	//	model_xform = glm::rotate(model_xform, angle, glm::vec3{ 1 ,0,0 });

	//angle += 0.001f;
	//if (angle > glm::two_pi<float>())
	//{
	//	angle = 0;
	//	rotateY = !rotateY;
	//}

	// Send the model matrix to the shader in a uniform
	GLuint model_xform_id = glGetUniformLocation(m_mainProgram, "model_xform");
	glUniformMatrix4fv(model_xform_id, 1, GL_FALSE, glm::value_ptr(model_xform));



	// Bind our VAO and render
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_numElements, GL_UNSIGNED_INT, (void*)0);

    /*unsigned int camera_direction_id = glGetUniformLocation(m_mainProgram, "camera_direction");
    GLCall(glUniform3fv(camera_direction_id, 1, glm::value_ptr(camera.GetForwardVector())));

    for (Model* m : models)
    {
        if (m)
        {
            for (Model::Mesh mesh : m->GetMeshes())
            {
                unsigned int combinedXFormId = glGetUniformLocation(m_mainProgram, "combined_xform");
                GLCall(glUniformMatrix4fv(combinedXFormId, 0, GL_FALSE, glm::value_ptr(combinedXForm)));

                // Send the model matrix to the shader in a uniform
                unsigned int modelXFormId = glGetUniformLocation(m_mainProgram, "model_xform");
                glm::mat4 translation = glm::translate(glm::mat4(1), m->GetWorldPosition());
                glm::mat4 newWorldPosition = translation * mesh.m_modelXForm;
                GLCall(glUniformMatrix4fv(modelXFormId, 1, GL_FALSE, glm::value_ptr(newWorldPosition)));

                //int location = glGetUniformLocation(m_mainProgram, "u_color");
                //assert(location != -1);
                //glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f);

                GLCall(glBindVertexArray(mesh.m_VAO));
                GLCall(glDrawElements(GL_TRIANGLES, (GLsizei)mesh.m_elementCount, GL_UNSIGNED_INT, (void*)0));
                GLCall(glBindVertexArray(0));
            }
        }
    }*/
}

void Renderer::DeleteProgram()
{
    glDeleteProgram(m_mainProgram);
}
