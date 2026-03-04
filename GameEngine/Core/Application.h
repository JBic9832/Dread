#pragma once

#include "Event/EventSystem.h"
#include "Window.h"
#include "Renderer/Renderer.h"
#include "InputManager/InputManager.h"
#include "glm/ext/vector_float2.hpp"
#include <glm/glm.hpp>

namespace Dread {

enum ApplicationType {
	DREAD_APP_TYPE_2D = 0,
	DREAD_APP_TYPE_3D
};

class Application {
public: 
	Application(EventSystem& eventSystem, unsigned int width, unsigned int height, ApplicationType appType);
	virtual ~Application();

	void Run();
	GLFWwindow* GetWindowHandle() const;

	Renderer& GetRenderer();

	static glm::vec2 GetWindowSize();
	static glm::mat4 GetProjectionMatrix();

protected:
	virtual void OnRender() = 0;
	virtual void OnUpdate() = 0;
	glm::vec2 GetApplicationWindowSize() const;
	EventSystem& m_EventSystem;
	static glm::mat4 s_ApplicationProjectionMatrix;
	static glm::vec2 s_WindowSize;

private:
	bool m_Running = true;
	Window m_Window;
	InputManager m_InputManager;
};

}
