#include "Renderer.h"

#include "Core/Logger.h"

namespace Dread {

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
}


}
