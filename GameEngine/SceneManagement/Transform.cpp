#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Dread {

Transform::Transform() {
	m_Position = glm::vec3(0.0f);
	m_Rotation = glm::quat(0.0f, glm::vec3(0.0f));
	m_Scale = glm::vec3(0.0f);
}

void Transform::Translate(const glm::vec3& translate) {
	m_Position += translate;
}

glm::vec3 Transform::Forward() const {
	return m_Rotation * glm::vec3(0.0f, 0.0f, -1.0f);
}

glm::vec3 Transform::Up() const {
	return m_Rotation * glm::vec3(0.0f, 1.0f, 0.0f);
}

}
