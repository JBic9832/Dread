#include "Game.h"
#include "InputManager/InputManager.h"
#include "Core/Logger.h"
#include "Renderer/PrimitiveMeshes/Cube.h"
#include "Renderer/PrimitiveMeshes/Pyramid.h"
#include "Renderer/PrimitiveMeshes/Sphere.h"
#include "Core/Time.h"
#include "vendor/imgui/imgui.h"
#include "Sin.h"

Game::Game(Dread::EventSystem& eventSystem) 
	: Dread::Application { eventSystem }
    , mainCamera(this->GetWindowHandle()) {
	objects.emplace("cube", std::make_unique<Dread::GameObject>());
	objects.emplace("pyramid", std::make_unique<Dread::GameObject>());
	objects.emplace("sphere", std::make_unique<Dread::GameObject>());

	Dread::Cube cubeMesh;	
	Dread::MeshRenderer cmr(cubeMesh.m_Mesh);
	objects["cube"]->AttachMesh(cmr);
	objects["cube"]->AttachBehavior<SinMove>();

	Dread::Sphere sMesh;
	Dread::MeshRenderer smr(sMesh.m_Mesh);
	objects["sphere"]->AttachMesh(smr);
	objects["sphere"]->m_Transform.SetPosition(glm::vec3(1.0f, 1.0f, -2.0f));

	Dread::Pyramid pyrMesh;
	Dread::MeshRenderer pmr(pyrMesh.m_Mesh);
	objects["pyramid"]->AttachMesh(pmr);
	objects["pyramid"]->m_Transform.SetPosition(glm::vec3(-1.0f, 1.0f, -3.0f));
	objects["pyramid"]->AttachBehavior<SinMove>();

	Dread::ResourceManager::LoadShader(RESOURCES_PATH "basic_vert.glsl", RESOURCES_PATH "basic_frag.glsl", "basic");
	shader = Dread::ResourceManager::GetShader("basic");
	mainCamera.SetCameraPosition(glm::vec3(0.0, 1.0, 3.0));
}

Game::~Game() {}

void Game::OnUpdate() {
	mainCamera.Update(this->GetWindowHandle(), Dread::Time::deltaTime);
	for (auto& [key, go] : objects) {
		go->Update();
	}

}

void Game::OnRender() {
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 proj = glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);

	for (auto& [key, go] : objects) {
		model = glm::mat4(1.0f);
		model = glm::translate(model, go->m_Transform.GetPosition());

		shader.Bind();
		shader.SetUniformMatrix4f("uView", mainCamera.GetViewMatrix());
		shader.SetUniformMatrix4f("uModel", model);
		shader.SetUniformMatrix4f("uProjection", proj);
		go->DrawMesh();
	}
}

Dread::Application* CreateApplication(Dread::EventSystem& eventSystem) {
	return new Game(eventSystem);
}
