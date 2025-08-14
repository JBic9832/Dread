#include "InputManager.h"

#include "Event/EventType.h"
#include "Core/Logger.h"

namespace Dread {

std::map<int, bool> InputManager::s_Keys;
std::map<int, bool> InputManager::s_Triggered;

InputManager::InputManager(EventSystem& eventSystem) : m_EventSystem { eventSystem } {
	m_EventSystem.Subscribe("KeyPressed", [this](const Event& e) {
		this->ProcessInput(e);
	});

	m_EventSystem.Subscribe("KeyReleased", [this](const Event& e) {
		this->ProcessInput(e);
	});
}

void InputManager::ProcessInput(const Event& e) {
	// Cast the event to a key pressed or released event
	if (e.GetName() == "KeyPressed") {
		auto keyEvent = dynamic_cast<const KeyPressedEvent*>(&e);

		if (keyEvent) {
			s_Keys[keyEvent->_keyCode] = true;
		}
	} else if (e.GetName() == "KeyReleased") {
		auto keyEvent = dynamic_cast<const KeyReleasedEvent*>(&e);

		if (keyEvent) {
			s_Triggered[keyEvent->_keyCode] = false;
			s_Keys[keyEvent->_keyCode] = false;
		}
	}
}

bool InputManager::GetKey(int key) {
	return s_Keys[key];
}

bool InputManager::GetKeyDown(int key) {
	// Check if the key is held
	if(!s_Triggered[key] && s_Keys[key]) {
		s_Triggered[key] = true;
		return true;
	} else {
		return false;
	}
}

}
