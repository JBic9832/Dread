#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

class Renderer {
public:
	Renderer();
	~Renderer(){};

	void DrawTriangle();

private:
	void initializeGlad();
	void loadTriangle();

private:
	const std::vector<float> verts = {
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};
	unsigned int vao;
};
