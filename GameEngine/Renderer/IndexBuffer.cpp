#include "IndexBuffer.h"

namespace Dread {

IndexBuffer::IndexBuffer(const std::vector<unsigned int>& indices) {
	glGenBuffers(1, &m_RendererId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
}

}
