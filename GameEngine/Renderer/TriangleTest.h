#pragma once

#include <glad/glad.h>
#include "VertexArray.h"
#include "VertexBuffer.h"

namespace Dread {

class TriangleTest {
public:
	VertexArray m_Vao;
	const std::vector<Vertex> verts = {
		{{ 0.0f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
		{{ 0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
		{{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}
	};
	TriangleTest() {
		LoadTriangle();
	}
	
	void LoadTriangle() {
		VertexBuffer vbo;

		m_Vao.Bind();
		vbo.Bind();

		vbo.UploadVertexDataWithAttribs(verts);

		VertexArray::UnbindAll();
	}

	void DrawTriangle() {
		m_Vao.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};

}
