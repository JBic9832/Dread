#include "GameObject.h"

namespace Dread {

GameObject::GameObject() {}

void GameObject::AttachMesh(MeshRenderer meshRenderer) {
	m_AttachedMesh = meshRenderer;
}

void GameObject::DrawMesh() {
	if (m_AttachedMesh) {
		m_AttachedMesh.value().DrawMesh();
	}
}


}
