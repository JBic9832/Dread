#pragma once

#include "Core/Application.h"
#include "Event/EventSystem.h"
#include "Renderer/MeshRenderer.h"
#include "SceneManagement/GameObject.h"
#include "SceneManagement/Camera.h"
#include "Renderer/ResourceManager.h"

class Game : public Dread::Application {
public:
	Game(Dread::EventSystem& eventSystem);
	~Game();

protected:
	void OnRender() override;
	void OnUpdate() override;

private:
	std::unordered_map<std::string, Dread::GameObject> objects;
	Dread::Camera mainCamera;
	Dread::Shader shader;

};
Dread::Application* CreateApplication();
