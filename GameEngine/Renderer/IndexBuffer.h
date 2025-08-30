#pragma once

#include <glad/glad.h>

#include <vector>

namespace Dread {

class IndexBuffer {
public:
	IndexBuffer(const std::vector<unsigned int>& indices);

	void Bind() const;

private:
	unsigned int m_RendererId;


};

}
