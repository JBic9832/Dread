#pragma once

#include "Event/EventSystem.h"
#include "Window.h"
#include "Renderer/Renderer.h"
#include "Renderer/TriangleTest.h"
#include "InputManager/InputManager.h"

namespace Dread {

class Application {
public: 
	Application(EventSystem& eventSystem, unsigned int width, unsigned int height);
	virtual ~Application();

	void Run();
	GLFWwindow* GetWindowHandle() const;

protected:
	virtual void OnRender() = 0;
	virtual void OnUpdate() = 0;
	glm::vec2 GetApplicationWindowSize() const;
	EventSystem& m_EventSystem;

private:
	bool m_Running = true;
	Window m_Window;
	Renderer m_Renderer;
	InputManager m_InputManager;
	TriangleTest m_TriangleTest;
};

}
