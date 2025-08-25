#include "Camera.h"

#include <iostream>

#include "InputManager/InputManager.h"
#include "Core/Logger.h"

namespace Dread {

Camera::Camera(GLFWwindow* window)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	m_LastMouseX = width / 2.0f;
	m_LastMouseY = height / 2.0f;
}

void Camera::Update(GLFWwindow* window, float deltaTime)
{
	processInput(deltaTime);
	updateCameraRotation(window);
	m_ViewMatrix = glm::lookAt(m_Transform.GetPosition(), m_Transform.GetPosition() + m_CameraFront, m_CameraUp);
}


void Camera::processInput(float deltaTime) {
	if (InputManager::GetKey(GLFW_KEY_W))
		m_Transform.SetPosition(m_Transform.GetPosition() + (m_CameraSpeed * m_CameraFront * deltaTime));
	if (InputManager::GetKey(GLFW_KEY_S))
		m_Transform.SetPosition(m_Transform.GetPosition() - (m_CameraSpeed * m_CameraFront * deltaTime));
	if (InputManager::GetKey(GLFW_KEY_A))
		m_Transform.SetPosition(m_Transform.GetPosition() - glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_CameraSpeed * deltaTime);
	if (InputManager::GetKey(GLFW_KEY_D))
		m_Transform.SetPosition(m_Transform.GetPosition() + glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_CameraSpeed * deltaTime);
	if (InputManager::GetKey(GLFW_KEY_SPACE))
		m_Transform.SetPosition(m_Transform.GetPosition() + (m_CameraUp * m_CameraSpeed * deltaTime));
	if (InputManager::GetKey(GLFW_KEY_LEFT_SHIFT) || InputManager::GetKey(GLFW_KEY_LEFT_CONTROL))
		m_Transform.SetPosition(m_Transform.GetPosition() - (m_CameraUp * m_CameraSpeed * deltaTime));
	if (InputManager::GetKeyDown(GLFW_KEY_M))
		DREAD_CORE_INFO("CAMERA POSITION -> X: {0}, Y: {1}, Z: {2}\n", m_Transform.GetPosition().x, m_Transform.GetPosition().y, m_Transform.GetPosition().z);
	if (InputManager::GetKeyDown(GLFW_KEY_ESCAPE)) {
		m_Disabled = !m_Disabled;
		DREAD_CORE_INFO("CAMERA DISABLE STATE {0}", m_Disabled);
	}
}

void Camera::updateCameraRotation(GLFWwindow* window) {
	double xpos;
	double ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	float xoffset = static_cast<float>(xpos) - m_LastMouseX;
	float yoffset = m_LastMouseY - static_cast<float>(ypos);

	m_LastMouseX = xpos;
	m_LastMouseY = ypos;

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
