#pragma once

#include "Mesh.h"
#include <memory>

namespace Dread {

class MeshRenderer {
public:
	MeshRenderer(std::shared_ptr<Mesh> mesh);

private:
	std::shared_ptr<Mesh> m_Mesh;
};

}
