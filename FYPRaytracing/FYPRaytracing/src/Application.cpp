#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <assert.h>
#include "Helpers.h"
#include "Model.h"
#include "Renderer.h"
#include "Camera.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW Error!" << std::endl;
    else
        std::cout << "GLEW Initialised!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    /*float positions[8]
    {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f
    };

    unsigned int indices[]
    {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    std::string vertexDirectory = "src/Shaders/exampleVertex.glsl";
    std::string vertexShader = Helpers::FetchShaderCode(vertexDirectory);
    std::string fragmentDirectory = "src/Shaders/exampleFragment.glsl";
    std::string fragmentShader = Helpers::FetchShaderCode(fragmentDirectory);*/

    //obj test
    std::string objDirectory = "Data/Models/Jeep/jeep.obj";
    std::vector<std::string> jeepMeshes;
    jeepMeshes.push_back(objDirectory);
    std::vector<std::string> jeepTextures;
    Model* m = new Model(jeepMeshes, jeepTextures);
    m->SetWorldPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    std::vector<Model*> models;
    models.push_back(m);
    //Helpers::LoadObjFile(objDirectory, *m);

    Camera* mainCamera = new Camera();
    mainCamera->SetCameraPosition(glm::vec3(0.0f, 15.0f, 50.0f));

    Renderer renderer;
    renderer.InitialiseGeometry(models);

    //unsigned int shader = Helpers::CreateShader(vertexShader, fragmentShader);
    //glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
       // glClear(GL_COLOR_BUFFER_BIT);
        mainCamera->CalculateRotationMatrix();

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        renderer.Render(*mainCamera, models);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //glDeleteProgram(shader);
    renderer.DeleteProgram();

    glfwTerminate();
    return 0;
}