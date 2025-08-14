#pragma once

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>

namespace Dread {

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Color;
	glm::vec2 TexCoords;
	glm::vec3 Normal;
};

class VertexBuffer {
public:
	VertexBuffer();
	~VertexBuffer();

	void UploadVertexDataWithAttribs(const std::vector<Vertex>& data);
	void Bind() const;
	static void UnbindAll();

private:
	unsigned int m_RendererId;
};

}

