#include "Camera.h"

#include <iostream>

#include "InputManager/InputManager.h"
#include "Core/Logger.h"

namespace Dread {

Camera::Camera()
{
	m_LastMouseX = InputManager::GetMousePosition().x;
	m_LastMouseY = InputManager::GetMousePosition().y;
}

void Camera::UpdateCamera(GLFWwindow* window, float deltaTime)
{
	m_ViewMatrix = glm::lookAt(m_Transform.GetPosition(), m_Transform.GetPosition() + m_CameraFront, m_CameraUp);
	GameObject::Update();
}


void Camera::updateCameraRotation(GLFWwindow* window) {
	MousePosition mousePos = InputManager::GetMousePosition();

	float xoffset = static_cast<float>(mousePos.x) - m_LastMouseX;
	float yoffset = m_LastMouseY - static_cast<float>(mousePos.y);

	m_LastMouseX = mousePos.x;
	m_LastMouseY = mousePos.y;

	float sens = 0.1f;
	xoffset *= sens;
	yoffset *= sens;

	if (!m_Disabled) {
		m_Yaw += xoffset;
		m_Pitch += yoffset;
	}

	if (m_Pitch > 89.0f)
		m_Pitch = 89.0f;
	if (m_Pitch < -89.0f)
		m_Pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_CameraFront = glm::normalize(front);
}

glm::mat4 Camera::GetViewMatrix() const {
	return m_ViewMatrix;
}

glm::vec3 Camera::GetCameraPosition() const {
	return m_Transform.GetPosition();
}

void Camera::SetDisableRotation(bool disabled) {
	m_Disabled = disabled;
}

void Camera::SetCameraPosition(const glm::vec3& position) {
	m_Transform.SetPosition(position);
}

void Camera::InvertPitch() {
	m_Pitch = -m_Pitch;
}

void Camera::UpdateViewMatrix(GLFWwindow* window) {
	updateCameraRotation(window);
	m_ViewMatrix = glm::lookAt(m_Transform.GetPosition(), m_Transform.GetPosition() + m_CameraFront, m_CameraUp);
}

}
