#pragma once

#include "Event/Event.h"
#include "Event/EventSystem.h"

#include <map>

namespace Dread {

class InputManager {
public:
	InputManager(EventSystem& eventSystem);

	// Was the key pressed
	static bool GetKeyDown(int key);
	// Is the key being held
	static bool GetKey(int key);

	void ProcessInput(const Event& e);

private:
	EventSystem& m_EventSystem;

private:
	static std::map<int, bool> s_Keys;
	static std::map<int, bool> s_Triggered;

};

}
