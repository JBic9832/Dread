#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Dread {

class Transform {
public:
	Transform();

	void Translate(const glm::vec3& translate);
	glm::vec3 Forward() const;
	glm::vec3 Up() const;

	glm::vec3 m_Position;
	glm::quat m_Rotation;
	glm::vec3 m_Scale;

};

}
