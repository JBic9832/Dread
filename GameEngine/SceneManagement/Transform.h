#pragma once

#include <glm/glm.hpp>

namespace Dread {

class Transform {
public:
	Transform();

	void SetPosition(const glm::vec3& newPos);
	void Translate(const glm::vec3& translate);
	glm::vec3 GetPosition() const;
	glm::vec3 GetScale() const;

private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

};

}
