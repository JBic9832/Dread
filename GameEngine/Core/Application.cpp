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
	while (!m_Window.ShouldClose()) {
		OnUpdate();
		OnRender();
		m_Window.UpdateWindow();
	}
}

}
