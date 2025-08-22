#pragma once

#include <optional>
#include "Renderer/MeshRenderer.h"
#include "Transform.h"

namespace Dread {

class GameObject {
public:
	GameObject();

	void AttachMesh(MeshRenderer meshRenderer);
	void DrawMesh();

private:
	Transform m_Transform;
	std::optional<MeshRenderer> m_AttachedMesh; // optional
};

}
