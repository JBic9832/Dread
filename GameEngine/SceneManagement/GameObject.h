#pragma once

#include <optional>
#include "Renderer/MeshRenderer.h"
#include "Transform.h"

namespace Dread {

class GameObject {
public:
	GameObject();
	~GameObject() = default;

	void AttachMesh(MeshRenderer meshRenderer);
	void DrawMesh();

	Transform m_Transform;

private:
	std::optional<MeshRenderer> m_AttachedMesh; // optional
};

}
