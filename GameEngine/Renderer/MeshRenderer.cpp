#include "MeshRenderer.h"

namespace Dread {

MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh) {
	m_Mesh = mesh;
}

std::shared_ptr<Mesh> MeshRenderer::GetMesh() const {
	return m_Mesh;
}

void MeshRenderer::DrawMesh() {
	m_Mesh->vao.Bind();
	glDrawArrays(GL_TRIANGLES, 0, m_Mesh->vertexCount);
}

}
