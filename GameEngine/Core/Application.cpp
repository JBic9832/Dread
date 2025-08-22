#include "Application.h"
#include <iostream>
#include "Logger.h"
#include "Event/EventType.h"

namespace Dread {

Application::Application(EventSystem& eventSystem) : m_EventSystem { eventSystem }, m_Window(1260, 720, "Hello, World!", eventSystem), m_InputManager(eventSystem) {
}

Application::~Application() {
}

void Application::Run() {
	glEnable(GL_DEPTH_TEST);
	glfwSetCursorPos(m_Window.WindowHandle(), 1260 / 2, 720 / 2);
	glfwSetInputMode(m_Window.WindowHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	while (!m_Window.ShouldClose()) {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		OnUpdate();
		OnRender();
		m_Window.UpdateWindow();
	}
}

GLFWwindow* Application::GetWindowHandle() const {
	return m_Window.WindowHandle();
}

}
