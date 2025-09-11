#include "Time.h"

#include <GLFW/glfw3.h>


namespace Dread {

float Time::deltaTime = 0.0f;
float Time::lastTime = 0.0f;
float Time::currentTime = 0.0f;

void Time::Tick() {
	currentTime = static_cast<float>(glfwGetTime());
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}

}
