#pragma once

#include "Renderer/Mesh.h"
#include <memory>

namespace Dread {

struct Sphere {
	Sphere() {
		m_Mesh = std::make_shared<Mesh>();

		std::vector<Vertex> vertices;

		const float PI = 3.14159265359f;
		const int sectorCount = 32;  // longitude slices
		const int stackCount  = 32;  // latitude slices
		float radius = 0.5f;

		for (int i = 0; i < stackCount; ++i) {
			float phi1 = PI * i / stackCount;
			float phi2 = PI * (i + 1) / stackCount;

			for (int j = 0; j < sectorCount; ++j) {
				float theta1 = 2 * PI * j / sectorCount;
				float theta2 = 2 * PI * (j + 1) / sectorCount;

				// Four corner positions of the current quad
				glm::vec3 p1(
						radius * cos(theta1) * sin(phi1),
						radius * cos(phi1),
						radius * sin(theta1) * sin(phi1)
						);
				glm::vec3 p2(
						radius * cos(theta2) * sin(phi1),
						radius * cos(phi1),
						radius * sin(theta2) * sin(phi1)
						);
				glm::vec3 p3(
						radius * cos(theta2) * sin(phi2),
						radius * cos(phi2),
						radius * sin(theta2) * sin(phi2)
						);
				glm::vec3 p4(
						radius * cos(theta1) * sin(phi2),
						radius * cos(phi2),
						radius * sin(theta1) * sin(phi2)
						);

				// Normals = positions normalized (sphere is centered at origin)
				glm::vec3 n1 = glm::normalize(p1);
				glm::vec3 n2 = glm::normalize(p2);
				glm::vec3 n3 = glm::normalize(p3);
				glm::vec3 n4 = glm::normalize(p4);

				// Texture coords (theta → u, phi → v)
				glm::vec2 uv1((float)j / sectorCount,     (float)i / stackCount);
				glm::vec2 uv2((float)(j+1) / sectorCount, (float)i / stackCount);
				glm::vec2 uv3((float)(j+1) / sectorCount, (float)(i+1) / stackCount);
				glm::vec2 uv4((float)j / sectorCount,     (float)(i+1) / stackCount);

				// Triangle 1
				vertices.push_back({p1, {1,0,0}, uv1, n1});
				vertices.push_back({p2, {0,1,0}, uv2, n2});
				vertices.push_back({p3, {0,0,1}, uv3, n3});

				// Triangle 2
				vertices.push_back({p1, {1,0,0}, uv1, n1});
				vertices.push_back({p3, {0,0,1}, uv3, n3});
				vertices.push_back({p4, {1,1,0}, uv4, n4});
			}
		}

		m_Mesh->vao.Bind();
		m_Mesh->vbo.Bind();
		m_Mesh->vbo.UploadVertexDataWithAttribs(vertices);
		m_Mesh->vao.UnbindAll();
		m_Mesh->vertexCount = vertices.size();
	}

	std::shared_ptr<Mesh> m_Mesh;


};

}
