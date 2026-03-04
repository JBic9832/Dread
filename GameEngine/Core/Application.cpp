#include "Application.h"
#include "InputManager/InputManager.h"
#include "Renderer/RenderPasses/GeometryPass.h"
#include "Renderer/Renderer.h"
#include "Renderer/ResourceManager.h"
#include "Renderer/Shader.h"
#include "SceneManagement/GameObject.h"
#include "Time.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Dread {
glm::mat4 Application::s_ApplicationProjectionMatrix{};
glm::vec2 Application::s_WindowSize{};

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
		s_ApplicationProjectionMatrix = glm::ortho(0.0f, (float) width, (float) height, 0.0f, 0.1f, 100.0f);
	} else {
		s_ApplicationProjectionMatrix = glm::perspective(45.0f, (float) width / height, 0.1f, 1000.0f);
	}

	s_WindowSize = m_Window.GetWindowSize();
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
	Shader shader = ResourceManager::GetShader("basic");

	GeometryPass gPass{};
	bool gPassEnable = false;

	while (!m_Window.ShouldClose()) {
		glfwPollEvents();
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
		// Begin Frame
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		OnUpdate();

		if (InputManager::GetKeyDown(GLFW_KEY_1)) {
			gPassEnable = !gPassEnable;
		}

		if (gPassEnable) {
			gPass.Render();
		} else {
			glm::mat4 model = glm::mat4(1);

			for (GameObject& go : Renderer::GameObjectContainer) {
				model = glm::mat4(1);

				glm::mat4 rot = glm::mat4_cast(go.m_Transform.m_Rotation);
				model = model * rot;

				model = glm::translate(model, go.m_Transform.m_Position);

				shader.Bind();
				shader.SetUniformMatrix4f("uView", Renderer::GetInstance().GetMainCamera()->GetViewMatrix());
				shader.SetUniformMatrix4f("uModel", model);
				shader.SetUniformMatrix4f("uProjection", s_ApplicationProjectionMatrix);
				go.DrawMesh();
			}
		}

		OnRender();

		m_Window.UpdateWindow();

		// End frame
		m_InputManager.EndFrame();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}

GLFWwindow* Application::GetWindowHandle() const {
	return m_Window.WindowHandle();
}

Renderer& Application::GetRenderer() {
	return Renderer::GetInstance();
}

glm::vec2 Application::GetWindowSize() {
	return s_WindowSize;
}

glm::mat4 Application::GetProjectionMatrix() {
	return s_ApplicationProjectionMatrix;
}

}
