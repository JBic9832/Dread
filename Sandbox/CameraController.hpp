#pragma once
#include "SceneManagement/Scripting/Behavior.h"
#include "SceneManagement/GameObject.h"
#include "InputManager/InputManager.h"
#include "Core/Time.h"
#include "Core/Logger.h"
#include <GLFW/glfw3.h>
#include <algorithm>

class CameraController : public Dread::Behavior {
public:
	float m_LastMouseX, m_LastMouseY;
	bool m_Disabled = false;

	float m_CameraSpeed = 10.0f;
	float m_Pitch = 0.0f;
	float m_Yaw = -90.0f;

	void OnCreate() override {
		m_LastMouseX = Dread::InputManager::GetMousePosition().x;
		m_LastMouseY = Dread::InputManager::GetMousePosition().y;
	}

	void OnUpdate() override {
		processInput();
		updateRotation();
	}

private:
	void processInput() {
		if (Dread::InputManager::GetKey(GLFW_KEY_W))
			gameObject->m_Transform.m_Position= (gameObject->m_Transform.m_Position + (m_CameraSpeed * gameObject->m_Transform.Forward() * Dread::Time::deltaTime));

		if (Dread::InputManager::GetKey(GLFW_KEY_S))
			gameObject->m_Transform.m_Position = (gameObject->m_Transform.m_Position - (m_CameraSpeed * gameObject->m_Transform.Forward() * Dread::Time::deltaTime));

		if (Dread::InputManager::GetKey(GLFW_KEY_A))
			gameObject->m_Transform.m_Position = (gameObject->m_Transform.m_Position - glm::normalize(glm::cross(gameObject->m_Transform.Forward(), gameObject->m_Transform.Up())) * m_CameraSpeed * Dread::Time::deltaTime);

		if (Dread::InputManager::GetKey(GLFW_KEY_D))
			gameObject->m_Transform.m_Position = (gameObject->m_Transform.m_Position + glm::normalize(glm::cross(gameObject->m_Transform.Forward(), gameObject->m_Transform.Up())) * m_CameraSpeed * Dread::Time::deltaTime);

		if (Dread::InputManager::GetKey(GLFW_KEY_SPACE))
			gameObject->m_Transform.m_Position = (gameObject->m_Transform.m_Position + (gameObject->m_Transform.Up() * m_CameraSpeed * Dread::Time::deltaTime));

		if (Dread::InputManager::GetKey(GLFW_KEY_LEFT_SHIFT) || Dread::InputManager::GetKey(GLFW_KEY_LEFT_CONTROL))
			gameObject->m_Transform.m_Position = (gameObject->m_Transform.m_Position - (gameObject->m_Transform.Up() * m_CameraSpeed * Dread::Time::deltaTime));

		if (Dread::InputManager::GetKeyDown(GLFW_KEY_M))
			DREAD_CORE_INFO(
					"CAMERA POSITION -> X: {0}, Y: {1}, Z: {2}\n", 
					gameObject->m_Transform.m_Position.x, 
					gameObject->m_Transform.m_Position.y, 
					gameObject->m_Transform.m_Position.z);

		if (Dread::InputManager::GetKeyDown(GLFW_KEY_T))
			DREAD_CORE_INFO(
					"CAMERA ROTATION -> X: {0}, Y: {1}, Z: {2}, W: {3}\n", 
					gameObject->m_Transform.m_Rotation.x, 
					gameObject->m_Transform.m_Rotation.y, 
					gameObject->m_Transform.m_Rotation.z,
					gameObject->m_Transform.m_Rotation.w);

		if (Dread::InputManager::GetKeyDown(GLFW_KEY_ESCAPE)) {
			m_Disabled = !m_Disabled;
			DREAD_CORE_INFO("CAMERA DISABLE STATE {0}", m_Disabled);
		}
	}

	void updateRotation() {
		Dread::MousePosition mousePos = Dread::InputManager::GetMousePosition();

		float xoffset = static_cast<float>(mousePos.x) - m_LastMouseX;
		float yoffset = m_LastMouseY - static_cast<float>(mousePos.y);

		m_LastMouseX = mousePos.x;
		m_LastMouseY = mousePos.y;

		// work this into some config later
		float sens = 0.1f;
		xoffset *= sens;
		yoffset *= sens;

		if (!m_Disabled) {
			m_Yaw += xoffset;
			m_Pitch += yoffset;
		}

		// Clamp the pitch so the player can't look at their ass
		m_Pitch = std::clamp(m_Pitch, -89.0f, 89.0f);

		glm::quat qPitch = glm::angleAxis(glm::radians(m_Pitch), glm::vec3(1, 0, 0));
		glm::quat qYaw = glm::angleAxis(glm::radians(m_Yaw), glm::vec3(0, -1, 0));

		gameObject->m_Transform.m_Rotation = glm::normalize(qYaw * qPitch);
	}
};














