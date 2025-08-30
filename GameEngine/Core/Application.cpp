#include "Application.h"
#include <iostream>
#include "Logger.h"
#include "Event/EventType.h"
#include "Time.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

namespace Dread {

Application::Application(EventSystem& eventSystem) : m_EventSystem { eventSystem }, m_Window(1260, 720, "Hello, World!", eventSystem), m_InputManager(eventSystem) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_Window.WindowHandle(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
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

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

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
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}

GLFWwindow* Application::GetWindowHandle() const {
	return m_Window.WindowHandle();
}

}
