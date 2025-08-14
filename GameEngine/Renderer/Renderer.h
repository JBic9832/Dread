#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "VertexArray.h"

namespace Dread {

class Renderer {
public:
	Renderer();
	~Renderer(){};

private:
	void initializeGlad();
};

}
