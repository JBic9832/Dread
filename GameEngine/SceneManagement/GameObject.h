#pragma once

#include <optional>
#include "Renderer/MeshRenderer.h"
#include "Transform.h"

namespace Dread {

class GameObject {
public:
	GameObject();

	void AttachMesh(const std::shared_ptr<Mesh> mesh);

private:
	Transform m_Transform;
	std::optional<std::shared_ptr<MeshRenderer>> m_AttachedMesh; // optional
};

}
