#pragma once

#include <glad/glad.h>
#include "VertexArray.h"

namespace Dread {

class TriangleTest {
public:
	VertexArray m_Vao;
	const std::vector<float> verts = {
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};
	TriangleTest() {
		LoadTriangle();
	}
	
	void LoadTriangle() {
		unsigned int vbo;

		glGenBuffers(1, &vbo);

		m_Vao.Bind();
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		VertexArray::UnbindAll();
	}

	void DrawTriangle() {
		m_Vao.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};

}
