#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera
{
private:
	glm::vec3 m_position{0};
	glm::vec3 m_rotation{0};
	glm::mat4 m_rotationMatrix{0};
public:
	Camera();

	glm::vec3 GetCameraPosition();
	void SetCameraPosition(glm::vec3 p);
	glm::vec3 GetCameraRotation();
	void SetCameraRotation(glm::vec3 r);
	glm::mat4 GetRotationMatrix();
	void CalculateRotationMatrix();
	glm::vec3 GetForwardVector();
	glm::vec3 GetUpVector();
};