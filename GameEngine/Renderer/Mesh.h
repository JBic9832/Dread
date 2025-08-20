#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"

namespace Dread {

struct Mesh {
	VertexArray vao;
	VertexBuffer vbo;
	unsigned int vertexCount;
};

}
