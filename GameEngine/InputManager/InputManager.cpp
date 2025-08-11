#include "InputManager.h"

namespace Dread {

InputManager::InputManager(EventSystem& eventSystem) : m_EventSystem { eventSystem } {
	m_EventSystem.Subscribe("KeyPressed", [this](const Event& e) {
		this->ProcessInput(e);
	});
}

}
