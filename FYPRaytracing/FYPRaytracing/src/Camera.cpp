#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
}

glm::vec3 Camera::GetCameraPosition()
{
	return m_position;
}

void Camera::SetCameraPosition(glm::vec3 p)
{
	m_position = p;
}

glm::vec3 Camera::GetCameraRotation()
{
	return m_rotation;
}

void Camera::SetCameraRotation(glm::vec3 r)
{
	m_rotation = r;
}

glm::mat4 Camera::GetRotationMatrix()
{
	return m_rotationMatrix;
}

void Camera::CalculateRotationMatrix()
{
	glm::mat4 rot{1};
	rot = glm::rotate(rot, m_rotation.x, glm::vec3(1, 0, 0));
	rot = glm::rotate(rot, m_rotation.y, glm::vec3(0, 1, 0));
	m_rotationMatrix = rot;
}
