#include "SceneManagement/Scripting/Behavior.h"
#include "SceneManagement/GameObject.h"
#include "Core/Time.h"

class SinMove : public Dread::Behavior{
public:
	glm::vec3 initialPos = glm::vec3(0.0f);
	void OnCreate() override {
		initialPos = gameObject->m_Transform.GetPosition();
	}
	void OnUpdate() override {
		float yOffset = sin(Dread::Time::currentTime * 5) + 1;
		glm::vec3 newPos = glm::vec3(initialPos.x, initialPos.y + yOffset, initialPos.z);
		gameObject->m_Transform.SetPosition(newPos);
	}
};
