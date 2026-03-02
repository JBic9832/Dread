#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <vector>
#include "SceneManagement/Camera.h"
#include "SceneManagement/GameObject.h"
#include <functional>

namespace Dread {

class Renderer {
public:
	Renderer();
	~Renderer() {};

	void BeginScene();
	void EndScene();

	std::shared_ptr<Camera> GetMainCamera() const;

	static void RegisterGameObject(GameObject& go);
	void RegisterCamera(std::shared_ptr<Camera> camera);
	// Maybe a better data structure for this
	static std::vector<std::reference_wrapper<GameObject>> GameObjectContainer;

private:
	void initializeGlad();

private:
	std::shared_ptr<Camera> m_MainCamera;
};

}
