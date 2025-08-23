#include "Application.h"
#include <iostream>
#include "Logger.h"
#include "Event/EventType.h"
#include "Time.h"

namespace Dread {

Application::Application(EventSystem& eventSystem) : m_EventSystem { eventSystem }, m_Window(1260, 720, "Hello, World!", eventSystem), m_InputManager(eventSystem) {
}

Application::~Application() {
}

void Application::Run() {
	glEnable(GL_DEPTH_TEST);
	bool cursorDisabled = true;
	glfwSetCursorPos(m_Window.WindowHandle(), 1260 / 2, 720 / 2);
	glfwSetInputMode(m_Window.WindowHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	while (!m_Window.ShouldClose()) {
		m_Window.UpdateWindow();

		if (InputManager::GetKeyDown(GLFW_KEY_ESCAPE)) {
			cursorDisabled = !cursorDisabled;
		}

		if (cursorDisabled) {
			glfwSetInputMode(m_Window.WindowHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		} else {
			glfwSetInputMode(m_Window.WindowHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		Time::Tick();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		OnUpdate();

		OnRender();

		m_InputManager.EndFrame();
	}
}

GLFWwindow* Application::GetWindowHandle() const {
	return m_Window.WindowHandle();
}

}
