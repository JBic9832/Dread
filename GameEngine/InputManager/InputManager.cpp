#include "InputManager.h"

#include "Event/EventType.h"
#include "Core/Logger.h"

namespace Dread {

std::unordered_map<int, KeyState> InputManager::s_Keys;

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
			auto& state = s_Keys[keyEvent->_keyCode];
			if (!state.held) {
				state.pressed = true;
			}
			state.held = true;
		}
	} else if (e.GetName() == "KeyReleased") {
		auto keyEvent = dynamic_cast<const KeyReleasedEvent*>(&e);

		if (keyEvent) {
			auto& state = s_Keys[keyEvent->_keyCode];
			state.held = false;
			state.released = true;
		}
	}
}

bool InputManager::GetKey(int key) {
	return s_Keys[key].held;
}

bool InputManager::GetKeyDown(int key) {
	return s_Keys[key].pressed;
}

bool InputManager::GetKeyUp(int key) {
	return s_Keys[key].released;
}

void InputManager::EndFrame() {
	for (auto& [key, state] : s_Keys) {
		state.pressed = false;
		state.released = false;
	}
}

}
