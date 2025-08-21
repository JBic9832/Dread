#include "GameObject.h"

namespace Dread {

GameObject::GameObject() {}

void GameObject::AttachMesh(const std::shared_ptr<Mesh> mesh) {

	std::shared_ptr<MeshRenderer> pMeshRenderer = std::make_shared<MeshRenderer>(mesh);

	m_AttachedMesh.emplace(pMeshRenderer);
}


}
