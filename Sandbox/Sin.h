#include "SceneManagement/Scripting/Behavior.h"
#include "SceneManagement/GameObject.h"
#include "Core/Time.h"

class SinMove : public Dread::Behavior{
public:
	void OnCreate() override {
		gameObject->m_Transform.SetPosition(glm::vec3(-1.0f, 4.0f, -3.0f));
	}
	void OnUpdate() override {
		gameObject->m_Transform.SetPosition(glm::vec3(-1.0f, sin(Dread::Time::currentTime * 5), -3.0f));
	}
};
