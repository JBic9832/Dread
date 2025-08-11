#pragma once

#include "Event/Event.h"
#include "Event/EventSystem.h"

#include <map>

namespace Dread {

class InputManager {
public:
	InputManager(EventSystem& eventSystem);

	// Was the key pressed
	bool GetKeyDown();
	// Is the key being held
	bool GetKey();

	void ProcessInput(const Event& e);

private:
	EventSystem& m_EventSystem;

private:
	static std::map<int, bool> s_Keys;

};

}
