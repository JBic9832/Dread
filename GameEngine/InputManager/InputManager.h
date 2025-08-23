#pragma once

#include "Event/Event.h"
#include "Event/EventSystem.h"

#include <unordered_map>

namespace Dread {

struct KeyState {
	bool held = false;
	bool pressed = false;
	bool released = false;
};

class InputManager {
public:
	InputManager(EventSystem& eventSystem);

	// Was the key pressed
	static bool GetKeyDown(int key);
	// Is the key being held
	static bool GetKey(int key);
	static bool GetKeyUp(int key);

	void ProcessInput(const Event& e);
	void EndFrame();

private:
	EventSystem& m_EventSystem;

private:
	static std::unordered_map<int, KeyState> s_Keys;

};

}
