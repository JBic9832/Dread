#include "SceneManagement/Scripting/Behavior.h"
#include "SceneManagement/GameObject.h"
#include "Core/Time.h"
#include <random>

class SinMove : public Dread::Behavior{
public:
	glm::vec3 initialPos = glm::vec3(0.0f);
	std::random_device rd;
	std::mt19937 gen;
	int phaseShift;

	void OnCreate() override {
		initialPos = gameObject->m_Transform.GetPosition();
		gen = std::mt19937(rd());
		std::uniform_int_distribution<> d(0, 5);
		phaseShift = d(gen);
	}

	void OnUpdate() override {
		float yOffset = sin(phaseShift + Dread::Time::currentTime * 5) + 1;
		glm::vec3 newPos = glm::vec3(initialPos.x, initialPos.y + yOffset, initialPos.z);
		gameObject->m_Transform.SetPosition(newPos);
	}
};
