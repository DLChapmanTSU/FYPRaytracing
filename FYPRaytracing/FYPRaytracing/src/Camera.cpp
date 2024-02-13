#include "Camera.h"

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
}
