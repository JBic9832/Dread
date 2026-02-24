#pragma once
#include "SceneManagement/Scripting/Behavior.h"
#include "SceneManagement/GameObject.h"
#include "InputManager/InputManager.h"
#include "Core/Time.h"
#include "Core/Logger.h"
#include <GLFW/glfw3.h>

class CameraController : public Dread::Behavior {
public:
	float m_LastMouseX, m_LastMouseY;
	bool m_Disabled = true;

	glm::vec3 m_CameraFront = gameObject->m_Transform.Forward();
	glm::vec3 m_CameraUp = gameObject->m_Transform.Up();

	float m_CameraSpeed = 10.0f;

	void OnCreate() override {
		m_LastMouseX = Dread::InputManager::GetMousePosition().x;
		m_LastMouseY = Dread::InputManager::GetMousePosition().y;
	}

	void OnUpdate() override {
		processInput();
	}

private:
	void processInput() {
		if (Dread::InputManager::GetKey(GLFW_KEY_W))
			gameObject->m_Transform.SetPosition(gameObject->m_Transform.GetPosition() + (m_CameraSpeed * m_CameraFront * Dread::Time::deltaTime));

		if (Dread::InputManager::GetKey(GLFW_KEY_S))
			gameObject->m_Transform.SetPosition(gameObject->m_Transform.GetPosition() - (m_CameraSpeed * m_CameraFront * Dread::Time::deltaTime));

		if (Dread::InputManager::GetKey(GLFW_KEY_A))
			gameObject->m_Transform.SetPosition(gameObject->m_Transform.GetPosition() - glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_CameraSpeed * Dread::Time::deltaTime);

		if (Dread::InputManager::GetKey(GLFW_KEY_D))
			gameObject->m_Transform.SetPosition(gameObject->m_Transform.GetPosition() + glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_CameraSpeed * Dread::Time::deltaTime);

		if (Dread::InputManager::GetKey(GLFW_KEY_SPACE))
			gameObject->m_Transform.SetPosition(gameObject->m_Transform.GetPosition() + (m_CameraUp * m_CameraSpeed * Dread::Time::deltaTime));

		if (Dread::InputManager::GetKey(GLFW_KEY_LEFT_SHIFT) || Dread::InputManager::GetKey(GLFW_KEY_LEFT_CONTROL))
			gameObject->m_Transform.SetPosition(gameObject->m_Transform.GetPosition() - (m_CameraUp * m_CameraSpeed * Dread::Time::deltaTime));

		if (Dread::InputManager::GetKeyDown(GLFW_KEY_M))
			DREAD_CORE_INFO(
					"CAMERA POSITION -> X: {0}, Y: {1}, Z: {2}\n", 
					gameObject->m_Transform.GetPosition().x, 
					gameObject->m_Transform.GetPosition().y, 
					gameObject->m_Transform.GetPosition().z);

		if (Dread::InputManager::GetKeyDown(GLFW_KEY_ESCAPE)) {
			m_Disabled = !m_Disabled;
			DREAD_CORE_INFO("CAMERA DISABLE STATE {0}", m_Disabled);
		}
	}
};
