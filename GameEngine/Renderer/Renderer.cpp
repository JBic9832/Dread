#include "Renderer.h"

#include "Core/Logger.h"

Renderer::Renderer() {
	initializeGlad();
	loadTriangle();
}

void Renderer::initializeGlad() {
	int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (!version) {
		DREAD_CORE_ERROR("FAILED TO INITIALIZE GLAD");
		return;
	}

	DREAD_CORE_TRACE("SUCCESS LOADING OPENGL BINDINGS");
}

void Renderer::loadTriangle() {
	unsigned int vbo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void Renderer::DrawTriangle() {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
