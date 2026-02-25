#include "Camera.h"

namespace Dread {

Camera::Camera()
{}

void Camera::UpdateCamera(GLFWwindow* window, float deltaTime)
{
	m_ViewMatrix = glm::lookAt(m_Transform.m_Position, m_Transform.m_Position + m_Transform.Forward(), m_Transform.Up());
	GameObject::Update();
}

glm::mat4 Camera::GetViewMatrix() const {
	return m_ViewMatrix;
}

glm::vec3 Camera::GetCameraPosition() const {
	return m_Transform.m_Position;
}

void Camera::SetDisableRotation(bool disabled) {
	m_Disabled = disabled;
}

void Camera::SetCameraPosition(const glm::vec3& position) {
	m_Transform.m_Position = position;
}

void Camera::InvertPitch() {
	m_Pitch = -m_Pitch;
}
}
