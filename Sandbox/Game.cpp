#include "Game.h"
#include "Renderer/PrimitiveMeshes/Cube.h"
#include "Renderer/PrimitiveMeshes/Pyramid.h"
#include "Renderer/PrimitiveMeshes/Sphere.h"
#include "Renderer/MeshRenderer.h"
#include "Core/Time.h"
#include "SceneManagement/Camera.h"
#include "Sin.h"
#include "CameraController.hpp"
#include "Renderer/ResourceManager.h"
#include <memory>

Game::Game(Dread::EventSystem& eventSystem, unsigned int width, unsigned int height, Dread::ApplicationType appType) 
	: Dread::Application(eventSystem, width, height, appType) { 
	objects.emplace("cube", std::make_unique<Dread::GameObject>());
	objects.emplace("pyramid", std::make_unique<Dread::GameObject>());
	objects.emplace("sphere", std::make_unique<Dread::GameObject>());

	Dread::Cube cubeMesh;	
	Dread::MeshRenderer cmr(cubeMesh.m_Mesh);
	objects["cube"]->AttachMesh(cmr);

	Dread::Sphere sMesh;
	Dread::MeshRenderer smr(sMesh.m_Mesh);
	objects["sphere"]->AttachMesh(smr);
	objects["sphere"]->m_Transform.m_Position = glm::vec3(1.0f, 1.0f, -2.0f);

	Dread::Pyramid pyrMesh;
	Dread::MeshRenderer pmr(pyrMesh.m_Mesh);
	objects["pyramid"]->AttachMesh(pmr);
	objects["pyramid"]->m_Transform.m_Position = glm::vec3(-1.0f, 1.0f, -3.0f);
	objects["pyramid"]->AttachBehavior<SinMove>();

	Dread::ResourceManager::LoadShader(RESOURCES_PATH "basic_vert.glsl", RESOURCES_PATH "basic_frag.glsl", "basic");
	shader = Dread::ResourceManager::GetShader("basic");

	mainCamera = std::make_shared<Dread::Camera>();
	mainCamera->SetCameraPosition(glm::vec3(0.0, 1.0, 3.0));
	mainCamera->AttachBehavior<CameraController>();

	GetRenderer().RegisterCamera(mainCamera);
}

Game::~Game() {}

void Game::OnUpdate() {
	mainCamera->UpdateCamera(this->GetWindowHandle(), Dread::Time::deltaTime);
	for (auto& [key, go] : objects) {
		go->Update();
	}
}

void Game::OnRender() {
}

// Use this to create your app
Dread::Application* CreateApplication(Dread::EventSystem& eventSystem) {
	return new Game(eventSystem, 1240, 720, Dread::DREAD_APP_TYPE_3D);
}
