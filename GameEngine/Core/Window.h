#pragma once 

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>
#include <glm/vec2.hpp>

#include "Event/EventSystem.h"

namespace Dread {

class Window {
public:
	Window(unsigned int width, unsigned int height, const std::string& windowName, EventSystem& eventSystem);
	~Window();

	bool ShouldClose() const;
	void UpdateWindow() const;
	GLFWwindow* WindowHandle() const;
	glm::vec2 GetWindowSize() const;

private:
	GLFWwindow* m_WindowHandle;
	unsigned int m_Width, m_Height;
	std::string m_WindowName;
	EventSystem& m_EventSystem;
	void SendKeyEvent(int key, int action);
	void SendMouseEvent(int x, int y) const;
	static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	static Window* createWindowUserPointer(GLFWwindow* window);
};

}
