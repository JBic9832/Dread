#include "Game.h"
#include <iostream>

Game::Game(Dread::EventSystem& eventSystem) 
	: Dread::Application { eventSystem } {
    std::cout << "Game Created\n";
}

Game::~Game() {
    std::cout << "Game Destroyed\n";
}

void Game::OnUpdate() {
}

void Game::OnRender() {
}

Dread::Application* CreateApplication(Dread::EventSystem& eventSystem) {
	return new Game(eventSystem);
}
