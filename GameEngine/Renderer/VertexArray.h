#pragma once

#include <glad/glad.h>

namespace Dread {

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void Bind();
	static void UnbindAll();

private:
	unsigned int m_RendererId;
};

}
