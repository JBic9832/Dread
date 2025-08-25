#include "Game.h"
#include "InputManager/InputManager.h"
#include "Core/Logger.h"
#include "Renderer/Primitives/Cube.h"
#include "Core/Time.h"

Game::Game(Dread::EventSystem& eventSystem) 
	: Dread::Application { eventSystem }
    , mainCamera(this->GetWindowHandle()) {
	Dread::Cube cubeMesh;	
	Dread::MeshRenderer mr(cubeMesh.m_Mesh);
	cube.AttachMesh(mr);

	Dread::ResourceManager::LoadShader(RESOURCES_PATH "basic_vert.glsl", RESOURCES_PATH "basic_frag.glsl", "basic");
	shader = Dread::ResourceManager::GetShader("basic");
	mainCamera.SetCameraPosition(glm::vec3(0.0, 1.0, 3.0));
}

Game::~Game() {
}

void Game::OnUpdate() {
	mainCamera.Update(this->GetWindowHandle(), Dread::Time::deltaTime);
}

void Game::OnRender() {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, cube.m_Transform.GetPosition());
	glm::mat4 proj = glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);

	shader.Bind();
	shader.SetUniformMatrix4f("uView", mainCamera.GetViewMatrix());
	shader.SetUniformMatrix4f("uModel", model);
	shader.SetUniformMatrix4f("uProjection", proj);
	cube.DrawMesh();

}

Dread::Application* CreateApplication(Dread::EventSystem& eventSystem) {
	return new Game(eventSystem);
}
