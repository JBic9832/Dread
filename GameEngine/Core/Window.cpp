#include "Window.h"
#include "Logger.h"

#include "Event/EventType.h"

namespace Dread {

void Window::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (win) {
		win->SendKeyEvent(key, action);
	}
}

Window::Window(unsigned int width, unsigned int height, const std::string& windowName, EventSystem& eventSystem)
	: m_Width { width }
	, m_Height { height }
	, m_WindowName { windowName }
	, m_EventSystem { eventSystem }
{
	if (!glfwInit())
		DREAD_CORE_ERROR("FAILED TO INITIALIZE GLFW!");

	m_WindowHandle = glfwCreateWindow(m_Width, m_Height, m_WindowName.c_str(), nullptr, nullptr);
	if (!m_WindowHandle) {
		glfwTerminate();
		DREAD_CORE_ERROR("FAILED TO CREATE THE WINDOW!");
	}

	glfwMakeContextCurrent(m_WindowHandle);
	glfwSetWindowUserPointer(m_WindowHandle, this);
	glfwSetKeyCallback(m_WindowHandle, glfwKeyCallback);
}

Window::~Window() {
	glfwTerminate();
}

bool Window::ShouldClose() const {
	return glfwWindowShouldClose(m_WindowHandle);
}

void Window::UpdateWindow() const {
	glfwSwapBuffers(m_WindowHandle);
	glfwPollEvents();
}

void Window::SendKeyEvent(int key, int action) {
	if (action == GLFW_PRESS) {
		m_EventSystem.Notify(KeyPressedEvent(key));
	} else if (action == GLFW_RELEASE) {
		m_EventSystem.Notify(KeyReleasedEvent(key));
	}
}

GLFWwindow* Window::WindowHandle() const {
	return m_WindowHandle;
}

}
