#pragma once

#include "Event/EventSystem.h"
#include "Window.h"
#include "Renderer/Renderer.h"

namespace Dread {

class Application {
public: 
	Application(EventSystem& eventSystem);
	virtual ~Application();

	void Run();
	void ReceiveEvent(const Event& e);

protected:
	virtual void OnRender() = 0;
	virtual void OnUpdate() = 0;
	EventSystem& m_EventSystem;

private:
	bool m_Running = true;
	Window m_Window;
	Renderer m_Renderer;

};

}
