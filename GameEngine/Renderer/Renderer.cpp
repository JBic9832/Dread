#include "Renderer.h"

#include "Core/Logger.h"
#include "SceneManagement/Camera.h"
#include "SceneManagement/GameObject.h"
#include <functional>
#include <memory>

namespace Dread {

std::vector<std::reference_wrapper<GameObject>> Renderer::GameObjectContainer;

Renderer::Renderer() {
	initializeGlad();
}

void Renderer::initializeGlad() {
	int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (!version) {
		DREAD_CORE_ERROR("FAILED TO INITIALIZE GLAD");
		return;
	}

	DREAD_CORE_TRACE("SUCCESS LOADING OPENGL BINDINGS");
	glEnable(GL_MULTISAMPLE);
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
