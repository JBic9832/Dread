#include "Game.h"
#include "InputManager/InputManager.h"
#include "Core/Logger.h"

Game::Game(Dread::EventSystem& eventSystem) 
	: Dread::Application { eventSystem } {
}

Game::~Game() {
}

void Game::OnUpdate() {
	if (Dread::InputManager::GetKey(GLFW_KEY_SPACE)) {
		DREAD_INFO("Key space is held!");
	}

	if (Dread::InputManager::GetKeyDown(GLFW_KEY_W)) {
		DREAD_INFO("Key W was pressed!");
	}

}

void Game::OnRender() {
}

Dread::Application* CreateApplication(Dread::EventSystem& eventSystem) {
	return new Game(eventSystem);
}
