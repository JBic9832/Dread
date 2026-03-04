#include "Renderer.h"

#include "Core/Logger.h"
#include "SceneManagement/Camera.h"
#include "SceneManagement/GameObject.h"
#include <functional>
#include <memory>

namespace Dread {

std::vector<std::reference_wrapper<GameObject>> Renderer::GameObjectContainer;
std::shared_ptr<Camera> Renderer::s_MainCamera{};

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
	s_MainCamera = camera;
}

std::shared_ptr<Camera> Renderer::GetMainCamera() {
	return s_MainCamera;
}

void Renderer::DrawScreenQuad() {
	static unsigned int quadVAO = 0;
	unsigned int quadVBO;
	if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

}
