#include "Application.h"
#include <iostream>
#include "Logger.h"
#include "Event/EventType.h"

namespace Dread {

Application::Application(EventSystem& eventSystem) : m_EventSystem { eventSystem }, m_Window(1260, 720, "Hello, World!", eventSystem) {
	m_EventSystem.Subscribe("KeyPressed", [this](const Event& e) {
		this->ReceiveEvent(e);
	});
	m_EventSystem.Subscribe("KeyReleased", [this](const Event& e) {
		this->ReceiveEvent(e);
	});
	std::cout << "Application created." << std::endl;
}

Application::~Application() {
	std::cout << "Closing out application." << std::endl;
}

void Application::Run() {
	while (!m_Window.ShouldClose()) {
		OnUpdate();
		OnRender();
		m_Renderer.DrawTriangle();
		m_Window.UpdateWindow();
	}
}

void Application::ReceiveEvent(const Event& e) {
	if (e.GetName() == "KeyPressed") {
		auto keyEvent = dynamic_cast<const KeyPressedEvent*>(&e);
		// dynamic_cast returns a nullptr if the type is incorrect
		if (keyEvent) {
			DREAD_CORE_INFO("GOT EVENT: {0}, WITH KEY: {1}.", keyEvent->GetName(), keyEvent->_keyCode);
		}
	} else if(e.GetName() == "KeyReleased") {
		auto keyEvent = dynamic_cast<const KeyReleasedEvent*>(&e);
		if (keyEvent) {
			DREAD_CORE_INFO("GOT EVENT: {0}, WITH KEY: {1}", keyEvent->GetName(), keyEvent->_keyCode);
		}
	} else {
		DREAD_CORE_WARN("UNHANDLED EVENT TYPE {0}", e.GetName());
	}
}

}
