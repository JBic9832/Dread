#pragma once

namespace Dread {

class GameObject;

class Behavior {
public:
	virtual ~Behavior() = default;

	virtual void OnCreate() {};
	virtual void OnUpdate() {};
	
	void SetOwner(GameObject* obj) { gameObject = obj; }
protected:
	GameObject* gameObject = nullptr;

};

}
