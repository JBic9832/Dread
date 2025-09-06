#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Dread {

Transform::Transform() {
	m_Position = glm::vec3(0.0f);
	m_Rotation = glm::vec3(0.0f);
	m_Scale = glm::vec3(0.0f);
}

void Transform::SetPosition(const glm::vec3& newPos) {
	m_Position = newPos;
}

void Transform::Translate(const glm::vec3& translate) {
	m_Position += translate;

}

glm::vec3 Transform::GetPosition() const {
	return m_Position;
}

}
