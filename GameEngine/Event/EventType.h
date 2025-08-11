#pragma once

#include "Event.h"

namespace Dread {

class KeyPressedEvent : public Event {
public:
	int _keyCode;
	KeyPressedEvent(int code) 
		: _keyCode(code) {}
	std::string GetName() const override { return "KeyPressed"; }
};

class KeyReleasedEvent: public Event {
public:
	int _keyCode;
	KeyReleasedEvent(int code) 
		: _keyCode(code) {}
	std::string GetName() const override { return "KeyReleased"; }
};

class WindowResizedEvent : public Event {
public:
	int _width, _height;
	WindowResizedEvent(int w, int h)
		: _width{ w }
		, _height { h } {}

	std::string GetName() const override { return "WindowResized"; }
};

}
