#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
	for (size_t i = 0; i < (size_t)CameraInputs::E_NUM_OF_INPUTS; i++)
	{
		m_cameraInputs[i] = false;
	}
}

void Camera::Update(float delta)
{
	glm::vec3 rotation{ 0 };

	if (m_cameraInputs[(int)CameraInputs::E_ROTATE_RIGHT])
		rotation.y += 1.0f;

	if (m_cameraInputs[(int)CameraInputs::E_ROTATE_LEFT])
		rotation.y -= 1.0f;

	if (m_cameraInputs[(int)CameraInputs::E_ROTATE_UP])
		rotation.x -= 1.0f;

	if (m_cameraInputs[(int)CameraInputs::E_ROTATE_DOWN])
		rotation.x += 1.0f;

	if (rotation != glm::vec3(0, 0, 0))
	{
		rotation = glm::normalize(rotation);
		rotation = rotation * m_rotationSpeed * delta;
		m_rotation += rotation;
		CalculateRotationMatrix();
	}

	glm::vec3 velocity{ 0 };

	if (m_cameraInputs[(int)CameraInputs::E_FORWARD])
		velocity += GetForwardVector();

	if (m_cameraInputs[(int)CameraInputs::E_BACKWARD])
		velocity -= GetForwardVector();

	if (m_cameraInputs[(int)CameraInputs::E_RIGHT])
		velocity += GetRightVector();

	if (m_cameraInputs[(int)CameraInputs::E_LEFT])
		velocity -= GetRightVector();

	if (m_cameraInputs[(int)CameraInputs::E_UP])
		velocity += GetUpVector();

	if (m_cameraInputs[(int)CameraInputs::E_DOWN])
		velocity -= GetUpVector();

	if (velocity == glm::vec3(0, 0, 0))
		return;

	velocity = glm::normalize(velocity);

	velocity = velocity * m_cameraSpeed * delta;

	m_position += velocity;
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

//Taken from example project from the year 2 3gp module
void Camera::CalculateRotationMatrix()
{
	glm::mat4 rot{1};
	rot = glm::rotate(rot, m_rotation.x, glm::vec3(1, 0, 0));
	rot = glm::rotate(rot, m_rotation.y, glm::vec3(0, 1, 0));
	m_rotationMatrix = rot;
}

//Taken from example project from the year 2 3gp module
glm::vec3 Camera::GetForwardVector()
{
	glm::vec4 forward{ glm::inverse(m_rotationMatrix) * glm::vec4(0, 0, -1, 1) };
	return glm::vec3(forward);
}

//Taken from example project from the year 2 3gp module
glm::vec3 Camera::GetUpVector()
{
	glm::vec4 up{ glm::inverse(m_rotationMatrix) * glm::vec4(0, 1, 0, 1) };
	return glm::vec3(up);
}

//Taken from example project from the year 2 3gp module
glm::vec3 Camera::GetRightVector()
{
	glm::vec4 right{ glm::inverse(m_rotationMatrix) * glm::vec4(1, 0, 0, 1) };
	return glm::vec3(right);
}

void Camera::MoveCamera(GLFWwindow* window, float timePassedSecs)
{
	
}

void Camera::ToggleInput(CameraInputs input)
{
	if (input >= CameraInputs::E_NUM_OF_INPUTS || (int)input < 0)
		return;

	m_cameraInputs[(int)input] = !m_cameraInputs[(int)input];
}
