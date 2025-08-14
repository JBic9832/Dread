#include "VertexArray.h"

namespace Dread {

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_RendererId);
}

VertexArray::~VertexArray() {}

void VertexArray::Bind() {
	glBindVertexArray(m_RendererId);
}

void VertexArray::UnbindAll() {
	glBindVertexArray(0);
}

}
