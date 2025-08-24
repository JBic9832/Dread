#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Dread {

class Camera
{
public:
	Camera(GLFWwindow* window);

	void update(GLFWwindow* window, float deltaTime);

	// TODO:
	// FIX THIS NONSENSE!!!
	// ALSO, make input checks use event system. We can't
	// be raw dawging that.
	glm::mat4 GetViewMatrix() const;
	glm::vec3 GetCameraPosition() const;
	float GetCameraPitch() { return m_Pitch; }

	void SetDisableRotation(bool disable);
	void SetCameraPosition(const glm::vec3& position);

	void InvertPitch();
	void UpdateViewMatrix(GLFWwindow* window);

private:
	void updateCameraRotation(GLFWwindow* window);
	void processInput(float deltaTime);

private:
	glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
	glm::vec3 m_CameraPosition = glm::vec3(0.0f, 1.0f, 3.0f);
	glm::vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float m_CameraSpeed = 5.0f;
	float m_SprintMultiplier = 1.0f;
	float m_LastMouseX;
	float m_LastMouseY;
	float m_Pitch = 0.0f;
	float m_Yaw = -90.0f;
	bool m_Disabled = false;


};

}

