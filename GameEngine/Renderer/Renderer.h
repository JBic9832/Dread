#pragma once

#include "SceneManagement/Camera.h"
#include "SceneManagement/GameObject.h"

#include <GLFW/glfw3.h>
#include <memory>
#include <vector>
#include <functional>

namespace Dread {

class Renderer {
public:
	Renderer(const Renderer&) = delete;
	void BeginScene();
	void EndScene();

	std::shared_ptr<Camera> GetMainCamera() const;

	static Renderer& GetInstance();

	static void RegisterGameObject(GameObject& go);
	void RegisterCamera(std::shared_ptr<Camera> camera);
	// Maybe a better data structure for this
	static std::vector<std::reference_wrapper<GameObject>> GameObjectContainer;

private:
	Renderer();
	~Renderer() {};

	void initializeGlad();

private:
	std::shared_ptr<Camera> m_MainCamera;
};

}
