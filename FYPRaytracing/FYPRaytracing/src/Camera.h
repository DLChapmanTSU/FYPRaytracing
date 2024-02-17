#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera
{
private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::mat4 m_rotationMatrix;
public:
	Camera();

	glm::vec3 GetCameraPosition();
	void SetCameraPosition(glm::vec3 p);
	glm::vec3 GetCameraRotation();
	void SetCameraRotation(glm::vec3 r);
	glm::mat4 GetRotationMatrix();
	void CalculateRotationMatrix();
};