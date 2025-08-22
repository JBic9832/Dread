#pragma once

#include "Mesh.h"
#include <memory>

namespace Dread {

class MeshRenderer {
public:
	MeshRenderer(std::shared_ptr<Mesh> mesh);

	std::shared_ptr<Mesh> GetMesh() const;
	void DrawMesh();

private:
	std::shared_ptr<Mesh> m_Mesh;
};

}
