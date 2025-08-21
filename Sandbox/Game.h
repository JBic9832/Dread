#pragma once

#include "Core/Application.h"
#include "Event/EventSystem.h"
#include "Renderer/MeshRenderer.h"
#include "SceneManagement/GameObject.h"

class Game : public Dread::Application {
public:
	Game(Dread::EventSystem& eventSystem);
	~Game();

protected:
	void OnRender() override;
	void OnUpdate() override;

private:
	Dread::GameObject cube;

};
Dread::Application* CreateApplication();
