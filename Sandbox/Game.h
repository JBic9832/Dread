#pragma once

#include "Core/Application.h"
#include "Event/EventSystem.h"

class Game : public Dread::Application {
public:
	Game(Dread::EventSystem& eventSystem);
	~Game();

protected:
	void OnRender() override;
	void OnUpdate() override;
};
Dread::Application* CreateApplication();
