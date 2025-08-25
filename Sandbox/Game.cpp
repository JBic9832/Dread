#include "Game.h"
#include "InputManager/InputManager.h"
#include "Core/Logger.h"
#include "Renderer/Primitives/Cube.h"
#include "Renderer/Primitives/Pyramid.h"
#include "Renderer/Primitives/Sphere.h"
#include "Core/Time.h"

Game::Game(Dread::EventSystem& eventSystem) 
	: Dread::Application { eventSystem }
    , mainCamera(this->GetWindowHandle()) {
	Dread::Cube cubeMesh;	
	Dread::MeshRenderer cmr(cubeMesh.m_Mesh);
	cube.AttachMesh(cmr);

	Dread::Pyramid pyrMesh;
	Dread::MeshRenderer pmr(pyrMesh.m_Mesh);
	pyramid.AttachMesh(pmr);
	pyramid.m_Transform.SetPosition(glm::vec3(-1.0f, 4.0f, -3.0f));

	Dread::Sphere sMesh;
	Dread::MeshRenderer smr(sMesh.m_Mesh);
	sphere.AttachMesh(smr);
	sphere.m_Transform.SetPosition(glm::vec3(1.0f, 1.0f, -2.0f));

	Dread::ResourceManager::LoadShader(RESOURCES_PATH "basic_vert.glsl", RESOURCES_PATH "basic_frag.glsl", "basic");
	shader = Dread::ResourceManager::GetShader("basic");
	mainCamera.SetCameraPosition(glm::vec3(0.0, 1.0, 3.0));
}

Game::~Game() {}

void Game::OnUpdate() {
	mainCamera.Update(this->GetWindowHandle(), Dread::Time::deltaTime);
	pyramid.m_Transform.SetPosition(glm::vec3(-1.0f, sin(glfwGetTime() * 5), -3.0f));
}

void Game::OnRender() {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, cube.m_Transform.GetPosition());
	glm::mat4 proj = glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);

	// TODO
	// This type of code should be handled by the renderer.
	// It is fine for now as test code but move this away from here.
	shader.Bind();
	shader.SetUniformMatrix4f("uView", mainCamera.GetViewMatrix());
	shader.SetUniformMatrix4f("uModel", model);
	shader.SetUniformMatrix4f("uProjection", proj);
	cube.DrawMesh();

	model = glm::mat4(1.0f);
	model = glm::translate(model, pyramid.m_Transform.GetPosition());

	shader.Bind();
	shader.SetUniformMatrix4f("uView", mainCamera.GetViewMatrix());
	shader.SetUniformMatrix4f("uModel", model);
	shader.SetUniformMatrix4f("uProjection", proj);
	pyramid.DrawMesh();
	
	model = glm::mat4(1.0f);
	model = glm::translate(model, sphere.m_Transform.GetPosition());

	shader.Bind();
	shader.SetUniformMatrix4f("uView", mainCamera.GetViewMatrix());
	shader.SetUniformMatrix4f("uModel", model);
	shader.SetUniformMatrix4f("uProjection", proj);
	sphere.DrawMesh();
}

Dread::Application* CreateApplication(Dread::EventSystem& eventSystem) {
	return new Game(eventSystem);
}
