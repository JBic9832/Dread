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

void Camera::update(GLFWwindow* window, float deltaTime)
{
	processInput(deltaTime);
	updateCameraRotation(window);
	m_ViewMatrix = glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp);
}


void Camera::processInput(float deltaTime) {
	if (InputManager::GetKey(GLFW_KEY_W))
		m_CameraPosition += m_CameraSpeed * m_CameraFront * deltaTime;
	if (InputManager::GetKey(GLFW_KEY_S))
		m_CameraPosition -= m_CameraSpeed * m_CameraFront * deltaTime;
	if (InputManager::GetKey(GLFW_KEY_A))
		m_CameraPosition -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_CameraSpeed * deltaTime;
	if (InputManager::GetKey(GLFW_KEY_D))
		m_CameraPosition += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_CameraSpeed * deltaTime;
	if (InputManager::GetKey(GLFW_KEY_SPACE))
		m_CameraPosition += m_CameraUp * m_CameraSpeed * deltaTime;
	if (InputManager::GetKey(GLFW_KEY_LEFT_SHIFT) || InputManager::GetKey(GLFW_KEY_LEFT_CONTROL))
		m_CameraPosition -= m_CameraUp * m_CameraSpeed * deltaTime;
	if (InputManager::GetKeyDown(GLFW_KEY_M))
		std::cout << "X: " << m_CameraPosition.x << "Y: " << m_CameraPosition.y << "Z: " << m_CameraPosition.z << std::endl;
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

}
