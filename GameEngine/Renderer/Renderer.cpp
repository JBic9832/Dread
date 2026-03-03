#include "Renderer.h"

#include "SceneManagement/Camera.h"
#include "SceneManagement/GameObject.h"
#include <functional>
#include <memory>

namespace Dread {

std::vector<std::reference_wrapper<GameObject>> Renderer::GameObjectContainer;

Renderer::Renderer() {
	initializeGlad();
}

Renderer& Renderer::GetInstance() {
	static Renderer instance;
	return instance;
}

void Renderer::initializeGlad() {
}

void Renderer::RegisterGameObject(GameObject &go) {
	Renderer::GameObjectContainer.push_back(go);
}

void Renderer::RegisterCamera(std::shared_ptr<Camera> camera) {
	m_MainCamera = camera;
}

std::shared_ptr<Camera> Renderer::GetMainCamera() const {
	return m_MainCamera;
}

}
