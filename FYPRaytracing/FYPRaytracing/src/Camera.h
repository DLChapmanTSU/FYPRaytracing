#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum class CameraInputs
{
	E_FORWARD,
	E_BACKWARD,
	E_LEFT,
	E_RIGHT,
	E_UP,
	E_DOWN,
	E_ROTATE_RIGHT,
	E_ROTATE_LEFT,
	E_ROTATE_UP,
	E_ROTATE_DOWN,
	E_NUM_OF_INPUTS
};

class Camera
{
private:
	glm::vec3 m_position{0};
	glm::vec3 m_rotation{0};
	glm::mat4 m_rotationMatrix{1};
	bool m_cameraInputs[(int)CameraInputs::E_NUM_OF_INPUTS];
	float m_cameraSpeed{ 50.0f };
	float m_rotationSpeed{ 2.0f };
public:
	Camera();
	void Update(float delta);

	glm::vec3 GetCameraPosition();
	void SetCameraPosition(glm::vec3 p);
	glm::vec3 GetCameraRotation();
	void SetCameraRotation(glm::vec3 r);
	glm::mat4 GetRotationMatrix();
	void CalculateRotationMatrix();
	glm::vec3 GetForwardVector();
	glm::vec3 GetUpVector();
	glm::vec3 GetRightVector();
	void MoveCamera(GLFWwindow* window, float timePassedSecs);
	void ToggleInput(CameraInputs input);
};