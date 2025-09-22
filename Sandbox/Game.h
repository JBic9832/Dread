#pragma once

#include "Core/Application.h"
#include "Event/EventSystem.h"
#include "Renderer/MeshRenderer.h"
#include "SceneManagement/GameObject.h"
#include "SceneManagement/Camera.h"
#include "Renderer/ResourceManager.h"
#include <memory>

class Game : public Dread::Application {
public:
	Game(Dread::EventSystem& eventSystem, unsigned int width, unsigned int height, Dread::ApplicationType appType);
	~Game();

protected:
	void OnRender() override;
	void OnUpdate() override;

private:
	std::unordered_map<std::string, std::unique_ptr<Dread::GameObject>> objects;
	Dread::Camera mainCamera;
	Dread::Shader shader;

};
Dread::Application* CreateApplication();
