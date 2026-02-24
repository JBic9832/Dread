#include "Application.h"
#include "Time.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Dread {

Application::Application(EventSystem& eventSystem, unsigned int width, unsigned int height, ApplicationType appType) : m_EventSystem { eventSystem }, m_Window(width, height, "Hello, World!", eventSystem), m_InputManager(eventSystem) {
	// IMGUI Initialization
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_Window.WindowHandle(), true);
	ImGui_ImplOpenGL3_Init("#version 330");

	if (appType == DREAD_APP_TYPE_2D) {
		m_ApplicationProjectionMatrix = glm::ortho(0.0f, (float) width, (float) height, 0.0f, 0.1f, 100.0f);
	} else {
		m_ApplicationProjectionMatrix = glm::perspective(45.0f, (float) width / height, 0.1f, 1000.0f);
	}
}

Application::~Application() {
}

glm::vec2 Application::GetApplicationWindowSize() const {
	return m_Window.GetWindowSize();
}

void Application::Run() {
	glEnable(GL_DEPTH_TEST);

	bool cursorDisabled = true;

	glm::vec2 windowSize = m_Window.GetWindowSize();
	glfwSetCursorPos(m_Window.WindowHandle(), windowSize.x / 2, windowSize.y / 2);
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
