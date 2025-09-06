#pragma once

#include <optional>
#include "Renderer/MeshRenderer.h"
#include "Transform.h"
#include "SceneManagement/Scripting/Behavior.h"

namespace Dread {

class GameObject {
public:
	GameObject();
	~GameObject() = default;

	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;

	void AttachMesh(MeshRenderer meshRenderer);
	void DrawMesh();
	void Update();

	template<typename T, typename... Args>
	T* AttachBehavior(Args&&... args) {
		auto behavior = std::make_unique<T>(std::forward<Args>(args)...);
		T* ptr = behavior.get();
		ptr->SetOwner(this);
		m_Behaviors.push_back(std::move(behavior));
		ptr->OnCreate();
		return ptr;
	}

	Transform m_Transform;

private:
	std::vector<std::unique_ptr<Behavior>> m_Behaviors;
	std::optional<MeshRenderer> m_AttachedMesh; // optional
};

}
